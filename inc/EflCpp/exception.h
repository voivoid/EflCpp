#pragma once

#include <exception>

#include <boost/format.hpp>

namespace EflCpp
{

class EflException : public std::exception
{
public:
    template <typename... Args>
    EflException(const char* const msg, const Args&... args)
        : _what(makeMsg(msg, args...))
    {
    }

    EflException()
    {
    }

    const char* what() const noexcept override
    {
        return _what.c_str();
    }

private:
    template <typename... Args>
    std::string makeMsg(const char* const msg, const Args&... args)
    {
        auto fmt = boost::format(msg);
        formatMsg(fmt, args...);
        return fmt.str();
    }

    void formatMsg(boost::format&)
    {
    }

    template <typename Arg>
    void formatMsg(boost::format& fmt, const Arg& arg)
    {
        fmt % arg;
    }

    template <typename Arg, typename... Args>
    void formatMsg(boost::format& fmt, const Arg& arg, const Args&... args)
    {
        formatMsg(fmt, arg);
        formatMsg(fmt, args...);
    }

private:
    const std::string _what;
};

} // namespace EflCpp
