#include "EflCpp/canvas_polygon.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
CanvasPolygon::CanvasPolygon(Canvas& canvas, const char* const objId)
    : Canvas::Object(canvas, &evas_object_polygon_add, objId)
{
}

void CanvasPolygon::clear()
{
    evas_object_polygon_points_clear(getHandle());
}

void CanvasPolygon::addPoint(const CoordPoint point)
{
    evas_object_polygon_point_add(getHandle(), point.x, point.y);
}

} // namespace EflCpp
