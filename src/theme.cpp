#include "EflCpp/theme.h"

#include "EflCpp/assert.h"
#include "EflCpp/files.h"
#include "EflCpp/log.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "EflCpp/elementary_inc.h"

namespace
{
std::string getEdjeFile(const char* const edjeFileName)
{
    auto edjePath = EflCpp::Files::getEdjeDir() / edjeFileName;
    if (!boost::filesystem::exists(edjePath))
    {
        EFLCPP_LOG_FATAL << "Edje file doesn't exist: " << edjePath;
        EFLCPP_ASSERT(false);
    }

    return edjePath.string();
}
}

namespace EflCpp
{
void themeExtensionAdd(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);

    const auto path = getEdjeFile(edjeFileName);
    EFLCPP_LOG_TRACE << "Adding theme extension from " << path;
    elm_theme_extension_add(nullptr, path.c_str());
}

void themeExtensionDel(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);
    const auto path = getEdjeFile(edjeFileName);
    EFLCPP_LOG_TRACE << "Deleting theme extension from " << path;
    elm_theme_extension_del(nullptr, path.c_str());
}

void themeOverlayAdd(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);
    const auto path = getEdjeFile(edjeFileName);
    EFLCPP_LOG_TRACE << "Adding theme overlay from " << path;
    elm_theme_overlay_add(nullptr, path.c_str());
}

void themeOverlayDel(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);
    const auto path = getEdjeFile(edjeFileName);
    EFLCPP_LOG_TRACE << "Deleting theme overlay from " << path;
    elm_theme_overlay_del(nullptr, path.c_str());
}

} // namespace EflCpp
