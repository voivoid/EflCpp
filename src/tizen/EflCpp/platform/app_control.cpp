#include "EflCpp/platform/app_control.h"

#include "EflCpp/assert.h"
#include "EflCpp/bimap.h"
#include "EflCpp/exception.h"

#include <boost/scope_exit.hpp>

#include <app_control.h>
#include <tizen_error.h>

namespace EflCpp
{

namespace
{
#if defined(EFLCPP_SET_APPCTRL_PARAM) || defined(EFLCPP_GET_APPCTRL_PARAM)
#error Macro is already defined
#else
#define EFLCPP_SET_APPCTRL_PARAM(f, val) setParam(f, val, #f)
#define EFLCPP_GET_APPCTRL_PARAM(f) getParam(f, #f)
#endif

void checkAppCtrlResult(const char* const failedFunc, const int errCode)
{
    if (errCode != APP_CONTROL_ERROR_NONE)
    {
        // TODO: show error msg by using get_error_message(errCode);
        throw EflException("%1% failed with error code %2%", failedFunc, errCode);
    }
}

static const auto appCtrlOpsBimap = makeUnorderedBimap<AppControl::Operation, std::string>(
    {{AppControl::Operation::Default, APP_CONTROL_OPERATION_DEFAULT}, {AppControl::Operation::View, APP_CONTROL_OPERATION_VIEW}, {AppControl::Operation::Pick, APP_CONTROL_OPERATION_PICK}});

void freeAppControl(const bool isOwner, app_control_h ctrl)
{
    if (!isOwner)
    {
        return;
    }

    app_control_destroy(ctrl);
}

app_control_h createAppControl()
{
    app_control_h service = nullptr;
    int res = app_control_create(&service);
    checkAppCtrlResult("app_control_create", res);

    return service;
}

} // namepsace anonymous

AppControl::AppControl(ReplyHandler handler, bool selfDestruct)
    : _service(createAppControl(), std::bind(&freeAppControl, true, std::placeholders::_1))
    , _handler{std::move(handler)}
    , _selfDestruct(selfDestruct)
{
    EFLCPP_ASSERT(_service);
    EFLCPP_ASSERT(_handler);
}

AppControl::AppControl(app_control_h control)
    : _service(control, std::bind(&freeAppControl, false, std::placeholders::_1))
{
}

AppControl::~AppControl()
{
}

void AppControl::setOperation(const Operation operation)
{
    const auto opStr = getBimapValueByKey(appCtrlOpsBimap, operation).c_str();
    EFLCPP_SET_APPCTRL_PARAM(app_control_set_operation, opStr);
}

AppControl::Operation AppControl::getOperation() const
{
    const auto operation = EFLCPP_GET_APPCTRL_PARAM(app_control_get_operation);
    return getBimapKeyByValue(appCtrlOpsBimap, operation);
}

void AppControl::setMime(const char* const mime)
{
    EFLCPP_ASSERT(mime);
    EFLCPP_SET_APPCTRL_PARAM(app_control_set_mime, mime);
}

std::string AppControl::getMime() const
{
    return EFLCPP_GET_APPCTRL_PARAM(app_control_get_mime);
}

void AppControl::setAppId(const char* const appId)
{
    EFLCPP_ASSERT(appId);
    EFLCPP_SET_APPCTRL_PARAM(app_control_set_app_id, appId);
}

std::string AppControl::getAppId() const
{
    return EFLCPP_GET_APPCTRL_PARAM(app_control_get_app_id);
}

void AppControl::setExtraData(const char* const key, const char* const data)
{
    EFLCPP_ASSERT(key);
    EFLCPP_ASSERT(data);

    int res = app_control_add_extra_data(_service.get(), key, data);
    checkAppCtrlResult("app_control_add_extra_data", res);
}

std::vector<std::string> AppControl::getExtraData(const char* key) const
{
    EFLCPP_ASSERT(key);

    std::vector<std::string> result;

    bool isArray = false;
    int res = app_control_is_extra_data_array(_service.get(), key, &isArray);
    checkAppCtrlResult("app_control_is_extra_data_array", res);

    if (!isArray)
    {
        char* outputData = nullptr;
        res = app_control_get_extra_data(_service.get(), key, &outputData);
        checkAppCtrlResult("app_control_get_extra_data", res);

        BOOST_SCOPE_EXIT(&outputData)
        {
            free(outputData);
        }
        BOOST_SCOPE_EXIT_END;

        result.push_back(outputData);
    }
    else
    {
        int outputArrayLength = 0;
        char** outputArray = nullptr;
        res = app_control_get_extra_data_array(_service.get(), key, &outputArray, &outputArrayLength);
        checkAppCtrlResult("app_control_get_extra_data_array", res);

        BOOST_SCOPE_EXIT(&outputArray, &outputArrayLength)
        {
            for (int i = 0; i < outputArrayLength; ++i)
            {
                free(outputArray[i]);
            }
            free(outputArray);
        }
        BOOST_SCOPE_EXIT_END;

        result.reserve(outputArrayLength);
        for (int i = 0; i < outputArrayLength; ++i)
        {
            result.push_back(outputArray[i]);
        }
    }

    return result;
}

void AppControl::setURI(const char* uri)
{
    EFLCPP_ASSERT(uri);
    EFLCPP_SET_APPCTRL_PARAM(app_control_set_uri, uri);
}

std::string AppControl::getURI() const
{
    return EFLCPP_GET_APPCTRL_PARAM(app_control_get_uri);
}

void AppControl::sendLaunchRequest()
{
    EFLCPP_ASSERT(_handler);

    int res = app_control_send_launch_request(_service.get(), reinterpret_cast<app_control_reply_cb>(&replyCallback), this);
    checkAppCtrlResult("app_control_send_launch_request", res);
}

void AppControl::replyCallback(app_control_h, app_control_h reply, int appCtrlResult, void* userData)
{
    // appCtrlResult has a 'int' type to hide 'app_control_result_e' type since there is no way to forward declare this enum in header
    // Check that ABI is not broken:
    static_assert(sizeof(app_control_result_e) == sizeof(int), "unexpected");

    EFLCPP_ASSERT(userData);

    AppControl& appCtrl = *reinterpret_cast<AppControl*>(userData);
    EFLCPP_ASSERT(appCtrl._handler);
    auto& handler = *appCtrl._handler;
    EFLCPP_ASSERT(handler);

    if (appCtrlResult != APP_CONTROL_RESULT_SUCCEEDED)
    {
        handler({});
    }
    else
    {
        handler(AppControl(reply));
    }

    if (appCtrl._selfDestruct)
    {
        delete &appCtrl;
    }
}

void AppControl::setParam(int (&f)(app_control_h, const char*), const char* param, const char* fName)
{
    EFLCPP_ASSERT(param);
    int res = f(_service.get(), param);
    checkAppCtrlResult(fName, res);
}

std::string AppControl::getParam(int (&f)(app_control_h, char**), const char* fName) const
{
    char* param = nullptr;

    int res = f(_service.get(), &param);
    checkAppCtrlResult(fName, res);

    BOOST_SCOPE_EXIT(&param)
    {
        free(param);
    }
    BOOST_SCOPE_EXIT_END;

    return param;
}

} // namespace EflCpp
