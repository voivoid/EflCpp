#pragma once

#include "EflCpp/canvas_object.h"
#include "EflCpp/geo.h"

namespace EflCpp
{
class CanvasLine : public Canvas::Object
{
public:
    EFLCPP_DECL_EFL_WIDGET(CanvasLine)

    void setCoords(CoordPoint from, CoordPoint to);
    CoordPoint getStartPoint() const;

protected:
    CanvasLine(Canvas& canvas, const char* objId = CanvasLineDefaultId);
    CanvasLine(Canvas& canvas, CoordRect rect, const char* objId = CanvasLineDefaultId);

private:
    static constexpr const char* CanvasLineDefaultId = "CANVAS_LINE";
};

} // namespace EflCpp
