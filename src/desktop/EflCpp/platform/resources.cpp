#include "EflCpp/resources.h"

#include "EflCpp/assert.h"
#include "EflCpp/files.h"
#include "EflCpp/log.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace EflCpp
{

boost::filesystem::path getAppResourcePath(const char* const resFilename, const ResourceType /*type*/)
{
    EFLCPP_ASSERT(resFilename);
    EFLCPP_LOG_TRACE << "Getting res file:" << resFilename;
    const auto path = Files::getResDir() / resFilename;
    EFLCPP_LOG_TRACE << " at path: " << path.string();

    EFLCPP_ASSERT(boost::filesystem::exists(path));

    return path;
}

} // namespace EflCpp
