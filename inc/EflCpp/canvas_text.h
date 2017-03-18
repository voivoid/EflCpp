#pragma once

#include "EflCpp/canvas_object.h"

namespace EflCpp
{
class CanvasText : public Canvas::Object
{
public:
    EFLCPP_DECL_EFL_WIDGET(CanvasText)

    void setText(const char* text);
    void setFont(const char* font, size_t size);

protected:
    CanvasText(Canvas& canvas, const char* objId = CanvasTextDefaultId);

private:
    static constexpr const char* CanvasTextDefaultId = "CANVAS_TEXT";
};

} // namespace EflCpp
