#pragma once

#include "EflCpp/layout.h"
#include "EflCpp/scrollable.h"

namespace EflCpp
{

class Scroller : public Layout, public Scrollable
{
public:
    EFLCPP_DECL_EFL_WIDGET(Scroller);
    ~Scroller();

protected:
    Scroller(ElmObj& parent, const char* objId = ScrollerDefaultId);

private:
    static constexpr const char* ScrollerDefaultId = "SCROLLER";
};
using ScrollerPtr = WidgetPtr<Scroller>;

} // namespace EflCpp
