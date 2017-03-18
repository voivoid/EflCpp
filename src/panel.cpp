#include "EflCpp/panel.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Panel::Panel(ElmObj& parent, const char* objId)
    : Layout(objId, &parent, &elm_panel_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Panel::~Panel()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
