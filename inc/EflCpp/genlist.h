#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class GenList : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(GenList)
    ~GenList();

protected:
    GenList(ElmObj& parent, const char* objId = GenListDefaultId);

private:
    static constexpr const char* GenListDefaultId = "GENLIST";
};
using GenListPtr = WidgetPtr<Layout>;

} // namespace EflCpp
