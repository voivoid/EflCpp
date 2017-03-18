#pragma once

#include "EflCpp/elementary_fwd.h"

#include <functional>
#include <memory>

namespace EflCpp
{

class Timer
{
public:
    using Handler = std::function<void()>;

    Timer(double intervalInSeconds, Handler handler, bool useMainLoopTime = true);

    void start();
    void stop();

    void freeze();
    void thaw();

    bool isStarted() const;

    static void runOnce(double intervalInSeconds, Handler handler);

private:
    struct Deleter
    {
        void operator()(Ecore_Timer*) const;
    };

private:
    std::unique_ptr<Ecore_Timer, Deleter> _timer;

    const double _intervalInSeconds;
    const Handler _handler;
    const bool _useMainLoopTime;
};

} // namespace EflCpp
