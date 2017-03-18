#include "EflCpp/scroller.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Scroller::Scroller(ElmObj& parent, const char* objId)
    : Layout(objId, &parent, &elm_scroller_add)
    , Scrollable(*getHandle())
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Scroller::~Scroller()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
