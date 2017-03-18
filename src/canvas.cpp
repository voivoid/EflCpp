#include "EflCpp/canvas.h"

#include "EflCpp/assert.h"
#include "EflCpp/elementary_inc.h"
#include "EflCpp/evas_obj.h"

namespace EflCpp
{

Canvas::Canvas(const CoordSize size)
    : _ecoreEvas(ecore_evas_new(nullptr, 0, 0, size.width, size.height, nullptr))
    , _evas(ecore_evas_get(_ecoreEvas))
{
    EFLCPP_ASSERT(_evas);
}

Canvas::Canvas(EvasObj& obj)
    : _ecoreEvas(nullptr)
    , _evas(evas_object_evas_get(EvasObj::Access::getHandle(obj)))
{
    EFLCPP_ASSERT(_evas);
}

Canvas::~Canvas()
{
    if (_ecoreEvas)
    {
        ecore_evas_free(_ecoreEvas);
    }
}

const Evas* Canvas::getHandle() const
{
    return _evas;
}

Evas* Canvas::getHandle()
{
    return _evas;
}

} // namespace EflCpp
