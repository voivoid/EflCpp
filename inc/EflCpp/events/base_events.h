#pragma once

#include <functional>
#include <memory>

namespace EflCpp
{
template <typename Source, typename Event, typename Ret, typename... Args>
class BaseEventsHandler
{
public:
    BaseEventsHandler();
    virtual ~BaseEventsHandler();

    using Handler = std::function<Ret(Args...)>;

    using OpaqueSignal = void*;
    static void emitEvent(const OpaqueSignal& signal, Args...);

protected:
    void setEventHandler(Source& source, const Event& event, Handler handler);
    virtual void registerNativeCallback(Source& source, const Event& event, const OpaqueSignal& signal) = 0;
    virtual void unregisterNativeCallback(Source&, const Event&) = 0;

private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace EflCpp
