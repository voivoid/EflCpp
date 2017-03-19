#include "EflCpp/events/evas_events.h"
#include "EflCpp/assert.h"
#include "EflCpp/evas_obj.h"
#include "EflCpp/log.h"
#include "EflCpp/safe_callback.h"

#include <boost/scope_exit.hpp>

#include <map>

#include "EflCpp/elementary_inc.h"

#ifdef EFLCPP_TIZEN
#include <efl_extension.h>
#endif

namespace EflCpp
{
namespace
{

const char* getEvasEventName(const EvasEvent event)
{
    switch (event)
    {
#ifdef EFLCPP_TIZEN
        case EvasEvent::MenuButton:
            return "MenuButton";
        case EvasEvent::BackButton:
            return "BackButton";
#endif
        case EvasEvent::Resize:
            return "Resize";
        case EvasEvent::Move:
            return "Move";
        case EvasEvent::MouseDown:
            return "MouseDown";
        case EvasEvent::MouseUp:
            return "MouseUp";
        case EvasEvent::KeyDown:
            return "Keydown";
        case EvasEvent::KeyUp:
            return "Keyup";
        case EvasEvent::FocusIn:
            return "FocusIn";
        case EvasEvent::FocusOut:
            return "FocusOut";
        case EvasEvent::Hide:
            return "Hide";
        case EvasEvent::Show:
            return "Show";
        case EvasEvent::Del:
            return "Del";
    }

    EFLCPP_FAIL_WITH_MESSAGE("Unknown evas event");
}

template <typename T>
EvasEvents::MouseData adaptMouseClickInfo(void* const mouseEventInfo)
{
    const auto& info = *reinterpret_cast<T*>(mouseEventInfo);

    EvasEvents::MouseData data = {{info.canvas.x, info.canvas.y}};

    return data;
}

template <typename T>
EvasEvents::KeyData adaptKeyInfo(void* const keyEventInfo)
{
    const auto& info = *reinterpret_cast<T*>(keyEventInfo);

    EvasEvents::KeyData data = {info.keyname, keyEventInfo};

    return data;
}

EvasEvents::MouseData adaptMouseEventInfo(void* const mouseEvent, const EvasEvent event)
{
    EFLCPP_ASSERT(event == EvasEvent::MouseDown || event == EvasEvent::MouseUp);
    switch (event)
    {
        case EvasEvent::MouseDown:
            return adaptMouseClickInfo<Evas_Event_Mouse_Down>(mouseEvent);

        case EvasEvent::MouseUp:
            return adaptMouseClickInfo<Evas_Event_Mouse_Up>(mouseEvent);

        default:
            EFLCPP_FAIL_WITH_MESSAGE("Unknown mouse event");
    }
}

EvasEvents::KeyData adaptKeyEventInfo(void* const keyEvent, const EvasEvent event)
{
    EFLCPP_ASSERT(event == EvasEvent::KeyDown || event == EvasEvent::KeyUp);
    switch (event)
    {
        case EvasEvent::KeyDown:
            return adaptKeyInfo<Evas_Event_Key_Down>(keyEvent);

        case EvasEvent::KeyUp:
            return adaptKeyInfo<Evas_Event_Key_Up>(keyEvent);

        default:
            EFLCPP_FAIL_WITH_MESSAGE("Unknown key event");
    }
}

const auto evasEvents = std::map<EvasEvent, Evas_Callback_Type>{{EvasEvent::Resize, EVAS_CALLBACK_RESIZE},
                                                                {EvasEvent::MouseDown, EVAS_CALLBACK_MOUSE_DOWN},
                                                                {EvasEvent::MouseUp, EVAS_CALLBACK_MOUSE_UP},
                                                                {EvasEvent::KeyDown, EVAS_CALLBACK_KEY_DOWN},
                                                                {EvasEvent::KeyUp, EVAS_CALLBACK_KEY_UP},
                                                                {EvasEvent::Move, EVAS_CALLBACK_MOVE},
                                                                {EvasEvent::FocusOut, EVAS_CALLBACK_FOCUS_OUT},
                                                                {EvasEvent::FocusIn, EVAS_CALLBACK_FOCUS_IN},
                                                                {EvasEvent::Hide, EVAS_CALLBACK_HIDE},
                                                                {EvasEvent::Show, EVAS_CALLBACK_SHOW},
                                                                {EvasEvent::Del, EVAS_CALLBACK_DEL}};

#ifdef EFLCPP_TIZEN
const auto eextEvents = std::map<EvasEvent, Eext_Callback_Type>{{EvasEvent::MenuButton, EEXT_CALLBACK_MORE},
                                                                {EvasEvent::BackButton, EEXT_CALLBACK_BACK}};

void eextCallback(void* const signal, Evas_Object* const obj, void* const event_info)
{
    EFLCPP_ASSERT(signal);
    EFLCPP_ASSERT(obj);

    EvasObj& source = EvasObj::getRef(*obj);
    source.incRefCount();
    BOOST_SCOPE_EXIT(&source) {
        source.decRefCount();
    } BOOST_SCOPE_EXIT_END
    Details::EvasEventsBase::emitEvent(signal, source, event_info);
}
#endif

void evasCallback(void* const signal, Evas* const /*e*/, Evas_Object* const obj, void* const event_info)
{
    EFLCPP_ASSERT(signal);
    EFLCPP_ASSERT(obj);

    EvasObj& source = EvasObj::getRef(*obj);
    Details::EvasEventsBase::emitEvent(signal, source, event_info);
}
} // namespace anonymous

void EvasEvents::registerNativeCallback(Evas_Object& obj, const EvasEvent& event, const OpaqueSignal& signal)
{
    EFLCPP_ASSERT(signal);

    auto evasIter = evasEvents.find(event);
    if (evasIter != evasEvents.cend())
    {
        evas_object_event_callback_add(&obj, evasIter->second, EFLCPP_WRAP_INTO_SAFE_CALLBACK(evasCallback), signal);
        return;
    }

#ifdef EFLCPP_TIZEN
    auto eextIter = eextEvents.find(event);
    if (eextIter != eextEvents.cend())
    {
        eext_object_event_callback_add(&obj, eextIter->second, EFLCPP_WRAP_INTO_SAFE_CALLBACK(eextCallback), signal);
        return;
    }
#endif

    EFLCPP_FAIL_WITH_MESSAGE("unknown evas event");
}

void EvasEvents::unregisterNativeCallback(Evas_Object&, const EvasEvent&)
{
    throw std::runtime_error("NOT IMPLEMENTED");
}

void EvasEvents::setEventHandler(Evas_Object& obj, EvasEvent event, Handler handler)
{
    auto evasHandler = [event, handler = std::move(handler)](EvasObj & obj, void* /*eventInfo*/)
    {
        LOG_CURRENT_SCOPE(obj.getObjId(), getEvasEventName(event));
        handler(obj);
    };

    Details::EvasEventsBase::setEventHandler(obj, event, std::move(evasHandler));
}

void EvasEvents::setMouseEventHandler(Evas_Object& obj, EvasEvent event, MouseHandler handler)
{
    auto evasHandler = [handler = std::move(handler), event](EvasObj & obj, void* eventInfo)
    {
        LOG_CURRENT_SCOPE(obj.getObjId(), getEvasEventName(event));
        handler(obj, adaptMouseEventInfo(eventInfo, event));
    };

    Details::EvasEventsBase::setEventHandler(obj, event, std::move(evasHandler));
}

void EvasEvents::setKeyEventHandler(Evas_Object& obj, EvasEvent event, KeyHandler handler)
{
    auto evasHandler = [handler = std::move(handler), event](EvasObj & obj, void* eventInfo)
    {
        LOG_CURRENT_SCOPE(obj.getObjId(), getEvasEventName(event));
        handler(obj, adaptKeyEventInfo(eventInfo, event));
    };

    Details::EvasEventsBase::setEventHandler(obj, event, std::move(evasHandler));
}
} // namespace EflCpp
