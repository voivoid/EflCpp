#include "EflCpp/grid.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Grid::Grid(ElmObj& parent, const char* const objId)
    : ElmObj(objId, &parent, &elm_grid_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Grid::~Grid()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Grid::clear()
{
    elm_grid_clear(getHandle(), EINA_FALSE);
}

void Grid::pack(EvasObj& obj, const CoordRect& rect)
{
    elm_grid_pack(getHandle(), EvasObj::getHandle(obj), rect.left, rect.top, rect.width(), rect.height());
}

void Grid::unpack(EvasObj& obj)
{
    elm_grid_unpack(getHandle(), EvasObj::getHandle(obj));
}

CoordRect Grid::packGet(EvasObj& obj)
{
    CoordUnit x = 0;
    CoordUnit y = 0;
    CoordUnit width = 0;
    CoordUnit height = 0;
    elm_grid_pack_get(EvasObj::getHandle(obj), &x, &y, &width, &height);

    return {x, y, x + width, y + height};
}

void Grid::setVirtualSize(const CoordSize size)
{
    elm_grid_size_set(getHandle(), size.width, size.height);
}

void Grid::packSet(EvasObj& obj, const CoordRect& rect)
{
    elm_grid_pack_set(EvasObj::getHandle(obj), rect.left, rect.top, rect.width(), rect.height());
}

} // namespace EflCpp
