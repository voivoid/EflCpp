#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/events/base_events.h"
#include "EflCpp/geo.h"

#include <functional>
#include <utility>

namespace EflCpp
{

enum class GestureEventType
{
    Taps,
    LongTaps,
    DoubleTaps,
    TripleTaps,
    Momentum,
    Lines,
    Flicks,
    Zoom,
    Rotate
};

enum class GestureEventState
{
    Undefined,
    Start,
    Move,
    End,
    Abort
};

using GestureEvent = std::pair<GestureEventType, GestureEventState>;

namespace Details
{
using GestureEventsBase = BaseEventsHandler<Evas_Object, GestureEvent, void, void*>;
}

class GestureEvents : private Details::GestureEventsBase
{
public:
    struct ZoomData
    {
        const CoordPoint point;
        const CoordUnit radius;
        const double zoom;
    };

    struct TapsData
    {
        CoordPoint point;
        unsigned int numFingers;
        unsigned int timestamp;
    };

    struct MomentumData
    {
        CoordPoint start;
        CoordPoint end;

        unsigned int tx;
        unsigned int ty;

        CoordPoint momentum;
        unsigned int numFingers;
    };

    template <typename Data>
    using EventHandler = std::function<void(const Data&)>;

    template <typename Data>
    void setEventHandler(Evas_Object& obj, GestureEvent event, EventHandler<Data> handler);

private:
    void registerNativeCallback(Evas_Object& obj, const GestureEvent& event, const OpaqueSignal& signal) override;
    void unregisterNativeCallback(Evas_Object&, const GestureEvent&) override;
};

} // namespace EflCpp
