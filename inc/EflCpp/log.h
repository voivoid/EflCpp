#pragma once

#include <sstream>

namespace EflCpp
{

enum class LogLevel
{
    Verbose,
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

namespace Details
{

class Logger
{
public:
    Logger(LogLevel level)
        : _level(level)
    {
    }

    ~Logger();

    template <typename T>
    Logger& operator<<(const T& val)
    {
        _ss << val;
        return *this;
    }

private:
    const LogLevel _level;
    std::stringstream _ss;
};

} // namespace Details

#define EFLCPP_LOG(level) EflCpp::Details::Logger(level)

#define EFLCPP_LOG_TRACE EFLCPP_LOG(EflCpp::LogLevel::Verbose)
#define EFLCPP_LOG_DEBUG EFLCPP_LOG(EflCpp::LogLevel::Debug)
#define EFLCPP_LOG_INFO EFLCPP_LOG(EflCpp::LogLevel::Info)
#define EFLCPP_LOG_WARN EFLCPP_LOG(EflCpp::LogLevel::Warning)
#define EFLCPP_LOG_ERROR EFLCPP_LOG(EflCpp::LogLevel::Error)
#define EFLCPP_LOG_FATAL EFLCPP_LOG(EflCpp::LogLevel::Fatal)

namespace Details
{

template <typename T>
struct ScopeLogger
{

    ScopeLogger(const char* objId, const T& event)
        : _objId(objId)
        , _event(event)
    {
        EFLCPP_LOG_TRACE << _objId << " - " << _event;
    }

    ~ScopeLogger()
    {
        EFLCPP_LOG_TRACE << _objId << " - " << _event << " done";
    }

    const char* _objId;
    const T& _event;
};

} // namespace Details

template <typename T>
Details::ScopeLogger<T> makeScopeLogger(const char* objId, const T& event)
{
    return Details::ScopeLogger<T>(objId, event);
}

#define LOG_CURRENT_SCOPE(objId, event) const auto _eflcpScopeLogger = makeScopeLogger(objId, event);

} // namespace EflCpp
