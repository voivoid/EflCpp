#pragma once

#include "EflCpp/elm_obj.h"
#include "EflCpp/geo.h"

namespace EflCpp
{
class Table : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(Table)
    ~Table();

    void unpack(EvasObj& object);
    void pack(EvasObj& object, int col, int row, int colspan, int rowspan);
    void setHomogeneous(bool homogeneous = true);

    struct PackInfo
    {
        size_t col;
        size_t row;
        size_t colSpan;
        size_t rowSpan;
    };
    PackInfo getPackInfo(EvasObj& object);

    void setPadding(CoordUnit horizontal, CoordUnit vertical);

    void clear(bool delObjects = true);

protected:
    Table(ElmObj& parent, const char* objId = TableDefaultId);

private:
    static constexpr const char* TableDefaultId = "TABLE";
};
using TablePtr = WidgetPtr<Table>;

} // namespace EflCpp
