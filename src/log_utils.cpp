#include "EflCpp/log_utils.h"

#ifdef EFLCPP_TIZEN
#include "EflCpp/platform/dlog_sink.h"
#endif

namespace EflCpp
{

#ifdef EFLCPP_TIZEN
boost::shared_ptr<boost::log::sinks::sink> makeDlogSink(const char* const appName)
{
    auto logBackend = boost::make_shared<DlogBackend>(std::move(appName));
    return boost::make_shared<DlogSink>(std::move(logBackend));
}
#endif

} // namespace EflCpp
