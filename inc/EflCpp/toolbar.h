#pragma once

#include "EflCpp/elm_obj.h"

namespace EflCpp
{

class Toolbar : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(Toolbar)
    ~Toolbar();

protected:
    Toolbar(ElmObj& parent, const char* objId = ToolbarDefaultId);

private:
    static constexpr const char* ToolbarDefaultId = "TOOLBAR";
};

} // namespace EflCpp
