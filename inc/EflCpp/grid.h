#pragma once

#include "EflCpp/elm_obj.h"
#include "EflCpp/geo.h"

namespace EflCpp
{
class Grid : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(Grid)
    ~Grid();

    void clear();
    void pack(EvasObj& obj, const CoordRect& rect);
    void unpack(EvasObj& obj);

    CoordRect packGet(EvasObj& obj);
    void packSet(EvasObj& obj, const CoordRect& rect);

    void setVirtualSize(CoordSize size);

protected:
    Grid(ElmObj& parent, const char* objId = GridDefaultId);

private:
    static constexpr const char* GridDefaultId = "GRID";
};
using GridPtr = WidgetPtr<Grid>;

} // namespace EflCpp
