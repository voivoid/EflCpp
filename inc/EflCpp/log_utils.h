#pragma once

#ifdef EFLCPP_TIZEN
#include <boost/log/sinks.hpp>
#endif

namespace EflCpp
{

#ifdef EFLCPP_TIZEN
boost::shared_ptr<boost::log::sinks::sink> makeDlogSink(const char* appName);
#endif

} // namespace EflCpp
