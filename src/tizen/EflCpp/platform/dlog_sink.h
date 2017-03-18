#pragma once

#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/sinks/unlocked_frontend.hpp>

#include <string>

namespace EflCpp
{

class DlogBackend : public boost::log::sinks::basic_formatted_sink_backend<char, boost::log::sinks::concurrent_feeding>
{
public:
    DlogBackend(std::string appName);

    void consume(boost::log::record_view const& rec, const string_type& formattedRecord);

private:
    const std::string _appName;
};

using DlogSink = boost::log::sinks::unlocked_sink<DlogBackend>;

} // namespace EflCpp
