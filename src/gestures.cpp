#include "EflCpp/gestures.h"

#include "EflCpp/assert.h"
#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Gestures::Gestures(ElmObj& parent, const char* objId)
    : Gestures(parent, parent, objId)
{
}

Gestures::Gestures(ElmObj& parent, ElmObj& object, const char* objId)
    : ElmObj(objId, &parent, &elm_gesture_layer_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
    attach(object);
}

Gestures::~Gestures()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Gestures::attach(EvasObj& object)
{
    auto result = elm_gesture_layer_attach(getHandle(), EvasObj::getHandle(object));
    EFLCPP_ASSERT(result == EINA_TRUE);
}

template <typename Data>
void Gestures::setEventHandler(GestureEvent event, GestureEvents::EventHandler<Data> handler)
{
    return _gestureEvents.setEventHandler(*getHandle(), std::move(event), std::move(handler));
}

template void Gestures::setEventHandler<GestureEvents::ZoomData>(GestureEvent, GestureEvents::EventHandler<GestureEvents::ZoomData>);
template void Gestures::setEventHandler<GestureEvents::TapsData>(GestureEvent, GestureEvents::EventHandler<GestureEvents::TapsData>);
template void Gestures::setEventHandler<GestureEvents::MomentumData>(GestureEvent, GestureEvents::EventHandler<GestureEvents::MomentumData>);

} // namespace EflCpp
