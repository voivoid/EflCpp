#include "EflCpp/files.h"

#include <boost/filesystem/path.hpp>

#include <app.h>

namespace
{
const char* const EdjeDirectory = "edje";
}

namespace EflCpp
{
namespace Files
{

boost::filesystem::path getResDir()
{
    return app_get_resource_path();
}

boost::filesystem::path getDataDir()
{
    return app_get_data_path();
}

boost::filesystem::path getEdjeDir()
{
    return getResDir() / EdjeDirectory;
}

} // namespace Files
} // namespace EflCpp
