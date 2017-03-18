#pragma once

#include "EflCpp/elm_obj.h"
#include "EflCpp/events/gesture_events.h"

namespace EflCpp
{

class Gestures : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(Gestures)
    ~Gestures();

    void attach(EvasObj& object);

    template <typename Data>
    void setEventHandler(GestureEvent event, GestureEvents::EventHandler<Data> handler);

    template <typename Handler>
    void setEventHandler(GestureEventType event, Handler handlerStart, Handler handlerMove, Handler handlerEnd, Handler handlerAbort)
    {
        setEventHandler({event, GestureEventState::Start}, std::move(handlerStart));
        setEventHandler({event, GestureEventState::Move}, std::move(handlerMove));
        setEventHandler({event, GestureEventState::End}, std::move(handlerEnd));
        setEventHandler({event, GestureEventState::Abort}, std::move(handlerAbort));
    }

protected:
    Gestures(ElmObj& parent, const char* objId = GesturesDefaultId);
    Gestures(ElmObj& parent, ElmObj& object, const char* objId = GesturesDefaultId);

private:
    static constexpr const char* GesturesDefaultId = "GESTURES";

    GestureEvents _gestureEvents;
};

} // namespace EflCpp
