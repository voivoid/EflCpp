#include "EflCpp/platform/dlog_sink.h"

#include "EflCpp/assert.h"
#include "EflCpp/log.h"

#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/attributes/value_extraction.hpp>

#include <dlog.h>

namespace EflCpp
{
namespace
{

log_priority getLogPriority(LogLevel level)
{
    switch (level)
    {
        case LogLevel::Fatal:
            return DLOG_FATAL;
        case LogLevel::Error:
            return DLOG_ERROR;
        case LogLevel::Warning:
            return DLOG_WARN;
        case LogLevel::Info:
            return DLOG_INFO;
        case LogLevel::Debug:
            return DLOG_DEBUG;
        case LogLevel::Verbose:
            return DLOG_VERBOSE;
    }

    EFLCPP_FAIL_WITH_MESSAGE("Unknown log level type");
}

} // namespace anonymous

DlogBackend::DlogBackend(std::string appName)
    : _appName(std::move(appName))
{
}

void DlogBackend::consume(const boost::log::record_view& record, const string_type& formattedRecord)
{
    const auto severity = record.attribute_values()[boost::log::aux::default_attribute_names::severity()].extract<LogLevel>();
    EFLCPP_ASSERT(severity);
    dlog_print(getLogPriority(severity.get()), _appName.c_str(), formattedRecord.c_str());
}

} // namespace EflCpp
