#pragma once

#include "EflCpp/button.h"

namespace EflCpp
{

class HoverSel : public Button
{
public:
    EFLCPP_DECL_EFL_WIDGET(HoverSel)
    ~HoverSel();

protected:
    HoverSel(ElmObj& parent, const char* objId = HoverSelDefaultId);

private:
    static constexpr const char* HoverSelDefaultId = "HOVERSEL";
};

} // namespace EflCpp
