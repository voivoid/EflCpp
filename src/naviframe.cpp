#include "EflCpp/naviframe.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

NaviFrame::NaviFrame(ElmObj& parent, const char* objId)
    : Layout(objId, &parent, &elm_naviframe_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

NaviFrame::~NaviFrame()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
