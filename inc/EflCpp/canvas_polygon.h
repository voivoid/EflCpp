#pragma once

#include "EflCpp/canvas_object.h"

namespace EflCpp
{
class CanvasPolygon : public Canvas::Object
{
public:
    EFLCPP_DECL_EFL_WIDGET(CanvasPolygon)

    void clear();
    void addPoint(CoordPoint point);

protected:
    CanvasPolygon(Canvas& canvas, const char* objId = CanvasPolygonDefaultId);

private:
    static constexpr const char* CanvasPolygonDefaultId = "CANVAS_POLYGON";
};

} // namespace EflCpp
