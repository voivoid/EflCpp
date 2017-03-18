#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <boost/variant.hpp>

namespace boost
{
namespace filesystem
{
class path;
}
}

namespace EflCpp
{

namespace FileSelector
{

using PathOpt = boost::optional<boost::filesystem::path>;
using PathsOpt = boost::optional<std::vector<boost::filesystem::path>>;
using SingleFileHandler = std::function<void(const PathOpt&)>;
using MultipleFileHandler = std::function<void(const PathsOpt&)>;

struct MimeFilter
{
    const std::vector<std::string> mimes;
    const std::string name;
};

struct ExtFilter
{
    const std::vector<std::string> extensions;
    const std::string name;
};

using Filter = boost::optional<boost::variant<MimeFilter, ExtFilter>>;

void launch(const boost::filesystem::path& root, SingleFileHandler handler, const Filter& filter = {}, bool dirsOnly = false);
void launch(const boost::filesystem::path& root, MultipleFileHandler handler, const Filter& filter = {}, bool dirsOnly = false);

} // namespace FileSelector
} // namespace EflCpp
