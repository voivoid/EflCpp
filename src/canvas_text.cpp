#include "EflCpp/canvas_text.h"

#include "EflCpp/assert.h"
#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
CanvasText::CanvasText(Canvas& canvas, const char* const objId)
    : Canvas::Object(canvas, &evas_object_text_add, objId)
{
}

void CanvasText::setText(const char* const text)
{
    EFLCPP_ASSERT(text);
    evas_object_text_text_set(getHandle(), text);
}

void CanvasText::setFont(const char* const font, const size_t size)
{
    EFLCPP_ASSERT(font);
    evas_object_text_font_set(getHandle(), font, size);
}

} // namespace EflCpp
