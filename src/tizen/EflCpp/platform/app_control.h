#pragma once

#include "EflCpp/application.h"
#include "EflCpp/elementary_fwd.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <boost/optional.hpp>

namespace EflCpp
{

class AppControl
{
    friend class Application::EventHandler;

public:
    using ReplyHandler = std::function<void(const boost::optional<AppControl>&)>;
    AppControl(ReplyHandler handler, bool selfDestruct = false);
    ~AppControl();

    enum class Operation
    {
        Default,
        View,
        Pick
    };
    void setOperation(Operation operation);
    Operation getOperation() const;

    void setMime(const char* mime);
    std::string getMime() const;

    void setAppId(const char* appId);
    std::string getAppId() const;

    void setExtraData(const char* key, const char* data);
    std::vector<std::string> getExtraData(const char* key) const;

    void setURI(const char* uri);
    std::string getURI() const;

    void sendLaunchRequest();
    static void replyCallback(app_control_h, app_control_h reply, int appControlResult, void* userData);

private:
    AppControl(app_control_h control);

    void setParam(int (&f)(app_control_h, const char*), const char* param, const char* fName);
    std::string getParam(int (&f)(app_control_h, char**), const char* fName) const;

private:
    const std::shared_ptr<app_control_s> _service; // shared_ptr is used here only because of type-erased deleter
    boost::optional<ReplyHandler> _handler;
    const bool _selfDestruct = false;
};

} // namespace EflCpp
