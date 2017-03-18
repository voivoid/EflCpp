#include "EflCpp/icon.h"

#include "EflCpp/assert.h"
#include "EflCpp/resources.h"

#include <boost/filesystem/path.hpp>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Icon::Icon(ElmObj& parent, const char* const file, const char* const objId)
    : Image(parent, &elm_icon_add, objId)
{
    EFLCPP_LOG_OBJECT_METHOD;

    if (file)
    {
        setFile(EflCpp::getAppImagePath(file));
    }
}

Icon::~Icon()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Icon::setStandard(const char* const name)
{
    auto result = elm_icon_standard_set(getHandle(), name);
    EFLCPP_ASSERT(result);
}

} // namespace EflCpp
