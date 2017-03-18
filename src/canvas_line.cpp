#include "EflCpp/canvas_line.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
CanvasLine::CanvasLine(Canvas& canvas, const char* const objId)
    : Canvas::Object(canvas, &evas_object_line_add, objId)
{
}

CanvasLine::CanvasLine(Canvas& canvas, CoordRect rect, const char* const objId)
    : CanvasLine(canvas, objId)
{
    setCoords({rect.left, rect.top}, {rect.right, rect.bottom});
}

void CanvasLine::setCoords(const CoordPoint from, const CoordPoint to)
{
    evas_object_line_xy_set(getHandle(), from.x, from.y, to.x, to.y);
}

CoordPoint CanvasLine::getStartPoint() const
{
    CoordUnit x;
    CoordUnit y;
    evas_object_line_xy_get(getHandle(), &x, &y, nullptr, nullptr);

    return {x, y};
}

} // namespace EflCpp
