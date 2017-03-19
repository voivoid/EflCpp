#include "EflCpp/resources.h"

#include "EflCpp/assert.h"
#include "EflCpp/exception.h"

#include <boost/filesystem/path.hpp>
#include <boost/scope_exit.hpp>

#include <map>

#include <app.h>

#if TIZEN_SDK_VERSION >= 240
#include <app_resource_manager.h>
#endif

namespace EflCpp
{

namespace
{

#if TIZEN_SDK_VERSION >= 240
using ResourceTypeMap = std::map<ResourceType, app_resource_e>;
const ResourceTypeMap resourceTypeMap{{ResourceType::Image, APP_RESOURCE_TYPE_IMAGE},
                                      {ResourceType::Layout, APP_RESOURCE_TYPE_LAYOUT},
                                      {ResourceType::Sound, APP_RESOURCE_TYPE_SOUND},
                                      {ResourceType::Binary, APP_RESOURCE_TYPE_BIN}};
}

boost::filesystem::path getAppResourcePath(const char* resFilename, ResourceType resourceType)
{
    EFLCPP_ASSERT(resFilename);

    const auto resourceTypeIt = resourceTypeMap.find(resourceType);
    EFLCPP_ASSERT(resourceTypeIt != resourceTypeMap.cend());

    char* resPath = nullptr;
    int result = app_resource_manager_get(resourceTypeIt->second, resFilename, &resPath);
    if (result != APP_RESOURCE_ERROR_NONE)
    {
        throw EflException("Failed to get resource %1% because of %2%", resFilename, result);
    }

    BOOST_SCOPE_EXIT(&resPath)
    {
        free(resPath);
    }
    BOOST_SCOPE_EXIT_END

    return {resPath};
}
#else
boost::filesystem::path getAppResourcePath(const char* /*resFilename*/, ResourceType /*resourceType*/)
{
    // TODO
    return "";
}
}

#endif

} // namespace EflCpp
