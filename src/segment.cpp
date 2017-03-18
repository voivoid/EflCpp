#include "EflCpp/segment.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Segment::Segment(ElmObj& parent, const char* objId)
    : Layout(objId, &parent, &elm_segment_control_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Segment::~Segment()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
