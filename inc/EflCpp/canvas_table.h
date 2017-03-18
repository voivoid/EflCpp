#pragma once

#include "EflCpp/canvas_object.h"

namespace EflCpp
{
class CanvasTable : public Canvas::Object
{
public:
    EFLCPP_DECL_EFL_WIDGET(CanvasTable)

    void pack(EvasObj& obj, unsigned short col, unsigned short row, unsigned short colspan, unsigned short rowspan);

protected:
    CanvasTable(Canvas& canvas, const char* objId = CanvasTableDefaultId);

private:
    static constexpr const char* CanvasTableDefaultId = "CANVAS_TABLE";
};

} // namespace EflCpp
