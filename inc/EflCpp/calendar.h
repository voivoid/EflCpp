#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class Calendar : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Calendar)

protected:
    Calendar(ElmObj& parent, const char* objId = CalendarDefaultId);
    ~Calendar();

private:
    static constexpr const char* CalendarDefaultId = "CALENDAR";
};
using CalendarPtr = WidgetPtr<Calendar>;

} // namespace EflCpp
