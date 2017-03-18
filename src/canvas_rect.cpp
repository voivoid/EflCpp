#include "EflCpp/canvas_rect.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
CanvasRect::CanvasRect(Canvas& canvas, const char* const objId)
    : Canvas::Object(canvas, &evas_object_rectangle_add, objId)
{
}

} // namespace EflCpp
