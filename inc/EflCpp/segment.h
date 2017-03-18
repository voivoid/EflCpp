#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class Segment : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Segment)
    ~Segment();

protected:
    Segment(ElmObj& parent, const char* objId = SegmentDefaultId);

private:
    static constexpr const char* SegmentDefaultId = "SEGMENT";
};

} // namespace EflCpp
