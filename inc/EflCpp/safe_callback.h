#pragma once

#include "EflCpp/log.h"

#include <exception>

namespace EflCpp
{
namespace Details
{

template <typename Sig, Sig F>
struct SafeCallbackWrapper;

template <typename Ret, typename... Args, Ret (*F)(Args...)>
struct SafeCallbackWrapper<Ret (*)(Args...), F>
{
    static Ret call(Args... args)
    {
        try
        {
            return F((args)...);
        }
        catch (const std::exception& ex)
        {
            EFLCPP_LOG_FATAL << "Unhandled exception in callback: " << ex.what();
            std::terminate();
        }
        catch (...)
        {
            EFLCPP_LOG_FATAL << "Unhandled exception in callback: unknown exception";
            std::terminate();
        }
    }
};

} // namespace Details
} // namespace EflCpp

#define EFLCPP_WRAP_INTO_SAFE_CALLBACK(callback) &EflCpp::Details::SafeCallbackWrapper<decltype(&callback), &callback>::call
