#pragma once

#include "canvas_object.h"

namespace EflCpp
{
class CanvasRect : public Canvas::Object
{
public:
    EFLCPP_DECL_EFL_WIDGET(CanvasRect)

protected:
    CanvasRect(Canvas& canvas, const char* objId = CanvasRectDefaultId);

private:
    static constexpr const char* CanvasRectDefaultId = "CANVAS_RECT";
};

} // namespace EflCpp
