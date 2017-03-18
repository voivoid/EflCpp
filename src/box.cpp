#include "EflCpp/box.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Box::Box(ElmObj& parent, const Mode mode, const char* const objId)
    : ElmObj(objId, &parent, &elm_box_add)
{
    EFLCPP_LOG_OBJECT_METHOD;

    if (mode == Mode::Horizontal)
    {
        elm_box_horizontal_set(getHandle(), EINA_TRUE);
    }
}

Box::~Box()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Box::packStart(EvasObj& widget)
{
    elm_box_pack_start(getHandle(), ElmObj::getHandle(widget));
}

void Box::packEnd(EvasObj& widget)
{
    elm_box_pack_end(getHandle(), ElmObj::getHandle(widget));
}

void Box::packBefore(EvasObj& widget, EvasObj& before)
{
    elm_box_pack_before(getHandle(), ElmObj::getHandle(widget), ElmObj::getHandle(before));
}

void Box::packAfter(EvasObj& widget, EvasObj& after)
{
    elm_box_pack_after(getHandle(), ElmObj::getHandle(widget), ElmObj::getHandle(after));
}

void Box::setHomogeneous(const bool homogeneous)
{
    elm_box_homogeneous_set(getHandle(), homogeneous);
}

void Box::recalculate()
{
    elm_box_recalculate(getHandle());
}

void Box::clear()
{
    elm_box_clear(getHandle());
}

void Box::unpack(EvasObj& widget)
{
    elm_box_unpack(getHandle(), ElmObj::getHandle(widget));
}

void Box::unpackAll()
{
    elm_box_unpack_all(getHandle());
}

void Box::setAlign(const double horizontal, const double vertical)
{
    elm_box_align_set(getHandle(), horizontal, vertical);
}

void Box::setPadding(const CoordUnit horizontal, const CoordUnit vertical)
{
    elm_box_padding_set(getHandle(), horizontal, vertical);
}

} // namespace EflCpp
