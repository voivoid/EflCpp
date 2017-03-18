#include "EflCpp/events/smart_events.h"

#include "EflCpp/assert.h"
#include "EflCpp/elm_obj.h"
#include "EflCpp/events/log_events.h"
#include "EflCpp/log.h"
#include "EflCpp/log.h"
#include "EflCpp/safe_callback.h"

#include <boost/polymorphic_cast.hpp>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
namespace
{
void callback(void* const signal, Evas_Object* const obj, void* const eventInfo)
{
    EFLCPP_ASSERT(signal);
    EFLCPP_ASSERT(obj);

    EvasObj& source = EvasObj::getRef(*obj);
    ElmObj* widget = boost::polymorphic_downcast<ElmObj*>(&source);
    Details::SmartEventsBase::emitEvent(signal, *widget, eventInfo);
}
}

void SmartEvents::registerNativeCallback(Evas_Object& obj, const std::string& event, const OpaqueSignal& signal)
{
    EFLCPP_ASSERT(!event.empty());
    EFLCPP_ASSERT(signal);

    evas_object_smart_callback_add(&obj, event.c_str(), EFLCPP_WRAP_INTO_SAFE_CALLBACK(callback), signal);
}

void SmartEvents::unregisterNativeCallback(Evas_Object&, const std::string&)
{
    throw std::runtime_error("NOT IMPLEMENTED");
}

void SmartEvents::setEventHandler(Evas_Object& obj, const std::string& event, Handler handler)
{
    auto smartHandler = [event, handler = std::move(handler)](ElmObj & obj, void* info)
    {
        LOG_CURRENT_SCOPE(obj.getObjId(), event);
        handler(obj, info);
    };

    Details::SmartEventsBase::setEventHandler(obj, event, std::move(smartHandler));
}

} // namespace EflCpp
