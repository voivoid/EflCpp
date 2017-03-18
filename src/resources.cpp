#include "EflCpp/resources.h"

#include <boost/filesystem/path.hpp>

namespace EflCpp
{

boost::filesystem::path getAppImagePath(const char* const resFilename)
{
    return getAppResourcePath(resFilename, ResourceType::Image);
}

} // namespace EflCpp
