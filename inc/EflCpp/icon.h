#pragma once

#include "EflCpp/image.h"

namespace EflCpp
{
class Icon : public Image
{
public:
    EFLCPP_DECL_EFL_WIDGET(Icon)
    ~Icon();

    void setStandard(const char* name);

protected:
    Icon(ElmObj& parent, const char* file = nullptr, const char* objId = IconDefaultId);

private:
    static constexpr const char* IconDefaultId = "ICON";
};
using IconPtr = WidgetPtr<Icon>;

} // namespace EflCpp
