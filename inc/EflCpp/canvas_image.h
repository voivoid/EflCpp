#pragma once

#include "EflCpp/canvas_object.h"

namespace EflCpp
{
class CanvasImage : public Canvas::Object
{
public:
    EFLCPP_DECL_EFL_WIDGET(CanvasImage)

    enum class FilledMode
    {
        NonFilled,
        Filled
    };

protected:
    CanvasImage(Canvas& canvas, FilledMode filledMode, const char* objId = CanvasImageDefaultId);

private:
    static constexpr const char* CanvasImageDefaultId = "CANVAS_IMAGE";
};

} // namespace EflCpp
