#include "EflCpp/assert.h"

#include "EflCpp/log.h"

namespace EflCpp
{
namespace Details
{

void logAssertMsg(const char* const expr, const char* const file, const size_t line, const char* const func)
{
    EFLCPP_LOG_FATAL << "Assertion failed in " << file << ":" << line << " " << func << " "
                     << "\"" << expr << "\"";
}

} // namespace Details
} // namespace EflCpp
