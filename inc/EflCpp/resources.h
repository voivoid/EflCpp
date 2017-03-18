#pragma once

namespace boost
{
namespace filesystem
{
class path;
}
}

namespace EflCpp
{

enum class ResourceType
{
    Image,
    Layout,
    Sound,
    Binary
};
boost::filesystem::path getAppResourcePath(const char* resFilename, ResourceType type);

boost::filesystem::path getAppImagePath(const char* resFilename);

} // namespace EflCpp
