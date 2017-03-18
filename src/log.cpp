#include "EflCpp/log.h"

#include <boost/log/common.hpp>

namespace EflCpp
{

namespace Details
{

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(BoostLogger, boost::log::sources::severity_logger_mt<LogLevel>)

Logger::~Logger()
{
    auto& logger = BoostLogger::get();
    BOOST_LOG_SEV(logger, _level) << _ss.rdbuf();
}
}

} // namespace EflCpp
