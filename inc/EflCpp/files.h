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

namespace Files
{

boost::filesystem::path getResDir();
boost::filesystem::path getDataDir();
boost::filesystem::path getEdjeDir();

} // namespace Files
} // namespace EflCpp
