#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class NaviFrame : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(NaviFrame);
    ~NaviFrame();

protected:
    NaviFrame(ElmObj& parent, const char* objId = NaviFrameDefaultId);

private:
    static constexpr const char* NaviFrameDefaultId = "NAVIFRAME";
};

} // namespace EflCpp
