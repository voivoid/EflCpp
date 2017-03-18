#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/events/base_events.h"
#include "EflCpp/geo.h"

#include <string>

namespace EflCpp
{
class EvasObj;

enum class EvasEvent
{
#ifdef EFLCPP_TIZEN
    BackButtonPressed,
#endif
    Resize,
    Move,
    MouseDown,
    MouseUp,
    KeyDown,
    KeyUp,
    FocusOut,
    FocusIn,
    Hide,
    Show,
    Del
};

namespace Details
{
using EvasEventsBase = BaseEventsHandler<Evas_Object, EvasEvent, void, EvasObj&, void*>;
}

class EvasEvents : private Details::EvasEventsBase
{
public:
    struct MouseData
    {
        CoordPoint currentPos;
    };

    struct KeyData
    {
        std::string key;
        void* rawEvent;
    };

    using Handler = std::function<void(EvasObj&)>;
    void setEventHandler(Evas_Object& obj, EvasEvent event, Handler handler);

    using MouseHandler = std::function<void(EvasObj&, const MouseData&)>;
    void setMouseEventHandler(Evas_Object& obj, EvasEvent event, MouseHandler handler);

    using KeyHandler = std::function<void(EvasObj&, const KeyData&)>;
    void setKeyEventHandler(Evas_Object& obj, EvasEvent event, KeyHandler handler);

private:
    void registerNativeCallback(Evas_Object& obj, const EvasEvent& event, const OpaqueSignal& signal) override;
    void unregisterNativeCallback(Evas_Object&, const EvasEvent&) override;
};

} // namespace EflCpp
