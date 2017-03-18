#include "EflCpp/canvas_box.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
CanvasBox::CanvasBox(Canvas& canvas, const char* const objId)
    : Canvas::Object(canvas, evas_object_box_add, objId)
{
}

void CanvasBox::prepend(EvasObj& obj)
{
    evas_object_box_prepend(getHandle(), EvasObj::getHandle(obj));
}

void CanvasBox::append(EvasObj& obj)
{
    evas_object_box_append(getHandle(), EvasObj::getHandle(obj));
}

} // namespace EflCpp
