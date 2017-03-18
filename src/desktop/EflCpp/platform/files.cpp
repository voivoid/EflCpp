#include "EflCpp/files.h"

#include <boost/filesystem/path.hpp>

namespace
{
const char* const TizenDirectory = ".tizen";
const char* const ResDirectory = "res";
const char* const DataDirectory = "data";
const char* const EdjeDirectory = "edje";
} // namespace anonymous

namespace EflCpp
{
namespace Files
{

boost::filesystem::path getTizenDir()
{
    return boost::filesystem::path(getenv("HOME")) / TizenDirectory;
}

boost::filesystem::path getResDir()
{
    return getTizenDir() / ResDirectory;
}

boost::filesystem::path getDataDir()
{
    return getTizenDir() / DataDirectory;
}

boost::filesystem::path getEdjeDir()
{
    return getTizenDir() / EdjeDirectory;
}

} // namespace Files
} // namespace EflCpp
