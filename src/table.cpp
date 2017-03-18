#include "EflCpp/table.h"

#include "EflCpp/assert.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
Table::Table(ElmObj& parent, const char* const objId)
    : ElmObj(objId, &parent, &elm_table_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Table::~Table()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Table::pack(EvasObj& object, const int col, const int row, const int colspan, const int rowspan)
{
    elm_table_pack(getHandle(), EvasObj::getHandle(object), col, row, colspan, rowspan);
}

void Table::unpack(EvasObj& object)
{
    elm_table_unpack(getHandle(), EvasObj::getHandle(object));
}

void Table::setHomogeneous(const bool mode)
{
    elm_table_homogeneous_set(getHandle(), mode);
}

void Table::setPadding(const CoordUnit horizontal, const CoordUnit vertical)
{
    elm_table_padding_set(getHandle(), horizontal, vertical);
}

void Table::clear(const bool delObjects)
{
    elm_table_clear(getHandle(), delObjects);
}

Table::PackInfo Table::getPackInfo(EvasObj& object)
{
    int col = 0;
    int row = 0;
    int colSpan = 0;
    int rowSpan = 0;
    elm_table_pack_get(EvasObj::getHandle(object), &col, &row, &colSpan, &rowSpan);

    EFLCPP_ASSERT(col >= 0);
    EFLCPP_ASSERT(row >= 0);
    EFLCPP_ASSERT(colSpan > 0);
    EFLCPP_ASSERT(rowSpan > 0);

    return {static_cast<size_t>(col), static_cast<size_t>(row), static_cast<size_t>(colSpan), static_cast<size_t>(rowSpan)};
}

} // namespace EflCpp
