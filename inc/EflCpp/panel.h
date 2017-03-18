#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class Panel : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Panel)
    ~Panel();

protected:
    Panel(ElmObj& parent, const char* objId = PanelDefaultId);

private:
    static constexpr const char* PanelDefaultId = "PANEL";
};

} // namespace EflCpp
