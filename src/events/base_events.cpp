#include "EflCpp/events/base_events.h"

#include "EflCpp/assert.h"
#include "EflCpp/elm_obj.h"
#include "EflCpp/events/evas_events.h"
#include "EflCpp/events/gesture_events.h"

#include <boost/signals2.hpp>

#include <map>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

template <typename Source, typename Event, typename Ret, typename... Args>
class BaseEventsHandler<Source, Event, Ret, Args...>::Impl
{
public:
    using Signal = boost::signals2::signal<Ret(Args...)>;
    using SignalPtr = std::unique_ptr<Signal>;
    using EventMap = std::map<Event, SignalPtr>;

    EventMap& getMap()
    {
        return _eventsMap;
    }

private:
    EventMap _eventsMap;
};

template <typename Source, typename Event, typename Ret, typename... Args>
BaseEventsHandler<Source, Event, Ret, Args...>::BaseEventsHandler()
    : _impl(std::make_unique<Impl>())
{
}

template <typename Source, typename Event, typename Ret, typename... Args>
BaseEventsHandler<Source, Event, Ret, Args...>::~BaseEventsHandler()
{
}

template <typename Source, typename Event, typename Ret, typename... Args>
void BaseEventsHandler<Source, Event, Ret, Args...>::setEventHandler(Source& source, const Event& event, Handler handler)
{
    auto& eventsMap = _impl->getMap();
    auto iter = eventsMap.find(event);
    if (iter == eventsMap.cend())
    {
        auto res = eventsMap.emplace(std::move(event), std::make_unique<typename Impl::Signal>());
        iter = res.first;
    }

    auto& signal = *iter->second;
    const bool needRegistration = signal.empty();
    signal.connect(std::move(handler));
    // auto* connPtr = new boost::signals2::connection(std::move(connection));

    if (needRegistration)
    {
        registerNativeCallback(source, iter->first, &signal);
    }
}

template <typename Source, typename Event, typename Ret, typename... Args>
void BaseEventsHandler<Source, Event, Ret, Args...>::emitEvent(const OpaqueSignal& signalArg, Args... args)
{
    EFLCPP_ASSERT(signalArg);

    using Signal = typename BaseEventsHandler<Source, Event, Ret, Args...>::Impl::Signal;
    const auto& signal = *reinterpret_cast<Signal*>(signalArg);

    signal(args...);
}

template class BaseEventsHandler<Evas_Object, EvasEvent, void, EvasObj&, void*>;
template class BaseEventsHandler<Evas_Object, std::string, void, ElmObj&, void*>;
template class BaseEventsHandler<Evas_Object, GestureEvent, void, void*>;

} // namespace EflCpp
