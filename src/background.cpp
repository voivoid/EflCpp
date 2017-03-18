#include "EflCpp/background.h"

#include "EflCpp/assert.h"
#include "EflCpp/log.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Background::~Background()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Background::Background(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_bg_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Background::setBgColor(const Color color)
{
    EFLCPP_LOG_OBJECT_METHOD;

    EFLCPP_ASSERT(color.r >= 0 && color.r <= 255);
    EFLCPP_ASSERT(color.g >= 0 && color.g <= 255);
    EFLCPP_ASSERT(color.b >= 0 && color.b <= 255);
    elm_bg_color_set(getHandle(), color.r, color.g, color.b);
}

Color Background::getBgColor() const
{
    EFLCPP_LOG_OBJECT_METHOD;

    int r = 0;
    int g = 0;
    int b = 0;
    elm_bg_color_get(getHandle(), &r, &g, &b);

    EFLCPP_ASSERT(r >= 0 && r <= 255);
    EFLCPP_ASSERT(g >= 0 && g <= 255);
    EFLCPP_ASSERT(b >= 0 && b <= 255);

    return {r, g, b, 0};
}

} // namespace EflCpp
