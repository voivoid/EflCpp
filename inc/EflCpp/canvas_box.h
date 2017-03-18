#pragma once

#include "EflCpp/canvas_object.h"

namespace EflCpp
{
class CanvasBox : public Canvas::Object
{
public:
    EFLCPP_DECL_EFL_WIDGET(CanvasBox)

    void prepend(EvasObj& obj);
    void append(EvasObj& obj);

protected:
    CanvasBox(Canvas& canvas, const char* objId = CanvasBoxDefaultId);

private:
    static constexpr const char* CanvasBoxDefaultId = "CANVAS_BOX";
};

} // namespace EflCpp
