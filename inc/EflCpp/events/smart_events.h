#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/events/base_events.h"

#include <string>

namespace EflCpp
{
class ElmObj;

namespace Details
{
using SmartEventsBase = BaseEventsHandler<Evas_Object, std::string, void, ElmObj&, void*>;
}

class SmartEvents : private Details::SmartEventsBase
{
public:
    using Handler = std::function<void(ElmObj&, void*)>;
    void setEventHandler(Evas_Object& obj, const std::string& event, Handler handler);

private:
    void registerNativeCallback(Evas_Object& obj, const std::string& event, const OpaqueSignal& signal) override;
    void unregisterNativeCallback(Evas_Object&, const std::string&) override;
};

} // namespace EflCpp
