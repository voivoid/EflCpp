#include "EflCpp/timer.h"

#include "EflCpp/assert.h"
#include "EflCpp/elementary_inc.h"
#include "EflCpp/log.h"
#include "EflCpp/safe_callback.h"

namespace EflCpp
{

namespace
{
void runHandler(void* const data, bool deleteHandler = false)
{
    EFLCPP_ASSERT(data);
    auto* handler = reinterpret_cast<Timer::Handler*>(data);

    EFLCPP_LOG_TRACE << "Calling timer callback";
    (*handler)();
    EFLCPP_LOG_TRACE << "Calling timer callback done";

    if (deleteHandler)
    {
        delete handler;
    }
}

Eina_Bool callback(void* const data)
{
    runHandler(data);
    return ECORE_CALLBACK_RENEW;
}

Eina_Bool runOnceCallback(void* const data)
{
    runHandler(data, true);
    return ECORE_CALLBACK_CANCEL;
}
}

void Timer::Deleter::operator()(Ecore_Timer* const timer) const
{
    ecore_timer_del(timer);
}

Timer::Timer(const double intervalInSeconds, Handler handler, bool useMainLoopTime)
    : _intervalInSeconds(intervalInSeconds)
    , _handler(std::move(handler))
    , _useMainLoopTime(useMainLoopTime)
{
}

void Timer::start()
{
    auto* addTimer = _useMainLoopTime ? &ecore_timer_loop_add : &ecore_timer_add;
    _timer.reset(addTimer(_intervalInSeconds, EFLCPP_WRAP_INTO_SAFE_CALLBACK(callback), &_handler));
}

void Timer::stop()
{
    _timer.reset();
}

void Timer::freeze()
{
    if (isStarted())
    {
        ecore_timer_freeze(_timer.get());
    }
}

void Timer::thaw()
{
    if (isStarted())
    {
        ecore_timer_thaw(_timer.get());
    }
}

bool Timer::isStarted() const
{
    return _timer.get();
}

void Timer::runOnce(double intervalInSeconds, Handler handler)
{
    ecore_timer_loop_add(intervalInSeconds, EFLCPP_WRAP_INTO_SAFE_CALLBACK(runOnceCallback), new Handler(std::move(handler)));
}

} // namespace EflCpp
