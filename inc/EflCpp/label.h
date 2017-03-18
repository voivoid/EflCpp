#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class Label : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Label)
    ~Label();

protected:
    Label(ElmObj& parent, const char* objId = LabelDefaultId);

private:
    static constexpr const char* LabelDefaultId = "LABEL";
};

} // namespace EflCpp
