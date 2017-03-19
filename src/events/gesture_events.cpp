#include "EflCpp/events/gesture_events.h"

#include "EflCpp/assert.h"
#include "EflCpp/safe_callback.h"

#include <map>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

namespace
{
template <typename Data>
Data adaptEventInfo(void* const eventInfo, const GestureEvent event);

template <>
GestureEvents::ZoomData adaptEventInfo(void* const eventInfo, const GestureEvent event)
{
    EFLCPP_ASSERT(event.first == GestureEventType::Zoom);
    EFLCPP_ASSERT(eventInfo);

    const auto& info = *reinterpret_cast<Elm_Gesture_Zoom_Info*>(eventInfo);

    GestureEvents::ZoomData zoomData{CoordPoint(info.x, info.y), info.radius, info.zoom};

    return zoomData;
}

template <>
GestureEvents::TapsData adaptEventInfo(void* const eventInfo, const GestureEvent event)
{
    EFLCPP_ASSERT(event.first == GestureEventType::Taps || event.first == GestureEventType::LongTaps || event.first == GestureEventType::DoubleTaps ||
                  event.first == GestureEventType::TripleTaps);
    EFLCPP_ASSERT(eventInfo);

    const auto& info = *reinterpret_cast<Elm_Gesture_Taps_Info*>(eventInfo);

    GestureEvents::TapsData tapsData{CoordPoint(info.x, info.y), info.n, info.timestamp};

    return tapsData;
}

template <>
GestureEvents::MomentumData adaptEventInfo(void* const eventInfo, const GestureEvent event)
{
    EFLCPP_ASSERT(event.first == GestureEventType::Momentum);
    EFLCPP_ASSERT(eventInfo);

    const auto& info = *reinterpret_cast<Elm_Gesture_Momentum_Info*>(eventInfo);

    GestureEvents::MomentumData momentumData{{info.x1, info.y1}, {info.x2, info.y2}, info.tx, info.ty, {info.mx, info.my}, info.n};

    return momentumData;
}

const auto GestureEventTypes = std::map<GestureEventType, Elm_Gesture_Type>{{GestureEventType::Taps, ELM_GESTURE_N_TAPS},
                                                                            {GestureEventType::LongTaps, ELM_GESTURE_N_LONG_TAPS},
                                                                            {GestureEventType::DoubleTaps, ELM_GESTURE_N_DOUBLE_TAPS},
                                                                            {GestureEventType::TripleTaps, ELM_GESTURE_N_TRIPLE_TAPS},
                                                                            {GestureEventType::Momentum, ELM_GESTURE_MOMENTUM},
                                                                            {GestureEventType::Lines, ELM_GESTURE_N_LINES},
                                                                            {GestureEventType::Flicks, ELM_GESTURE_N_FLICKS},
                                                                            {GestureEventType::Zoom, ELM_GESTURE_ZOOM},
                                                                            {GestureEventType::Rotate, ELM_GESTURE_ROTATE}};
const auto GestureEventStates = std::map<GestureEventState, Elm_Gesture_State>{{GestureEventState::Undefined, ELM_GESTURE_STATE_UNDEFINED},
                                                                               {GestureEventState::Start, ELM_GESTURE_STATE_START},
                                                                               {GestureEventState::Move, ELM_GESTURE_STATE_MOVE},
                                                                               {GestureEventState::End, ELM_GESTURE_STATE_END},
                                                                               {GestureEventState::Abort, ELM_GESTURE_STATE_ABORT}};

Evas_Event_Flags gestureCallback(void* const signal, void* const eventInfo)
{
    EFLCPP_ASSERT(signal);
    EFLCPP_ASSERT(eventInfo);

    Details::GestureEventsBase::emitEvent(signal, eventInfo);

    return EVAS_EVENT_FLAG_NONE;
}

} // namespace anonymous

template <typename Data>
void GestureEvents::setEventHandler(Evas_Object& obj, const GestureEvent event, GestureEvents::EventHandler<Data> eventHandler)
{
    auto gestureHandler = [handler = std::move(eventHandler), event](void* eventInfo)
    {
        handler(adaptEventInfo<Data>(eventInfo, event));
    };

    return Details::GestureEventsBase::setEventHandler(obj, std::move(event), std::move(gestureHandler));
}

void GestureEvents::registerNativeCallback(Evas_Object& obj, const GestureEvent& event, const OpaqueSignal& signal)
{
    const auto iterType = GestureEventTypes.find(event.first);
    if (iterType == GestureEventTypes.cend())
    {
        EFLCPP_FAIL_WITH_MESSAGE("Unknown gesture event type");
    }

    const auto iterState = GestureEventStates.find(event.second);
    if (iterState == GestureEventStates.cend())
    {
        EFLCPP_FAIL_WITH_MESSAGE("Unknown gesture event state");
    }

    elm_gesture_layer_cb_set(&obj, iterType->second, iterState->second, EFLCPP_WRAP_INTO_SAFE_CALLBACK(gestureCallback), signal);
}

void GestureEvents::unregisterNativeCallback(Evas_Object&, const GestureEvent&)
{
    throw std::runtime_error("NOT IMPLEMENTED");
}

template void GestureEvents::setEventHandler<GestureEvents::ZoomData>(Evas_Object&, GestureEvent, EventHandler<GestureEvents::ZoomData>);
template void GestureEvents::setEventHandler<GestureEvents::TapsData>(Evas_Object&, GestureEvent, EventHandler<GestureEvents::TapsData>);
template void GestureEvents::setEventHandler<GestureEvents::MomentumData>(Evas_Object&, GestureEvent, EventHandler<GestureEvents::MomentumData>);

} // namespace EflCpp
