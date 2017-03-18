#include "EflCpp/canvas_image.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

CanvasImage::CanvasImage(Canvas& canvas, FilledMode filledMode, const char* const objId)
    : Canvas::Object(canvas, filledMode == FilledMode::Filled ? evas_object_image_filled_add : &evas_object_image_add, objId)
{
}

} // namespace EflCpp
