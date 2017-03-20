#include "EflCpp/calendar.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Calendar::Calendar(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_calendar_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Calendar::~Calendar()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
