#include "EflCpp/canvas_table.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
CanvasTable::CanvasTable(Canvas& canvas, const char* const objId)
    : Canvas::Object(canvas, evas_object_table_add, objId)
{
}

void CanvasTable::pack(EvasObj& obj, const unsigned short col, const unsigned short row, const unsigned short colspan, const unsigned short rowspan)
{
    evas_object_table_pack(getHandle(), EvasObj::getHandle(obj), col, row, colspan, rowspan);
}

} // namespace EflCpp
