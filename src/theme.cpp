#include "EflCpp/theme.h"

#include "EflCpp/assert.h"
#include "EflCpp/files.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "EflCpp/elementary_inc.h"

namespace
{
std::string getEdjeFile(const char* const edjeFileName)
{
    auto edjePath = EflCpp::Files::getEdjeDir() / edjeFileName;
    EFLCPP_ASSERT(boost::filesystem::exists(edjePath));

    return edjePath.string();
}
}

namespace EflCpp
{
void themeExtensionAdd(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);
    elm_theme_extension_add(nullptr, getEdjeFile(edjeFileName).c_str());
}

void themeExtensionDel(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);
    elm_theme_extension_del(nullptr, getEdjeFile(edjeFileName).c_str());
}

void themeOverlayAdd(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);
    elm_theme_overlay_add(nullptr, getEdjeFile(edjeFileName).c_str());
}

void themeOverlayDel(const char* const edjeFileName)
{
    EFLCPP_ASSERT(edjeFileName);
    elm_theme_overlay_del(nullptr, getEdjeFile(edjeFileName).c_str());
}

} // namespace EflCpp
