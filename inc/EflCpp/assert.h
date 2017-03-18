#pragma once

#include <boost/current_function.hpp>
#include <cstdlib>
#include <exception>

namespace EflCpp
{
namespace Details
{

void logAssertMsg(const char* expr, const char* file, size_t line, const char* func);

} // namespace Details
} // namespace EflCpp

#define EFLCPP_ASSERT_IMPL(expr, file, line, func)              \
    if (!(expr))                                                \
    {                                                           \
        EflCpp::Details::logAssertMsg(#expr, file, line, func); \
        std::terminate();                                       \
    }

#define EFLCPP_ASSERT(expr) EFLCPP_ASSERT_IMPL(expr, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION)

#define EFLCPP_FAIL_WITH_MESSAGE(msg) EFLCPP_ASSERT(false)
