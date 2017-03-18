#include "EflCpp/canvas_object.h"

#include "EflCpp/elementary_inc.h"
#include "EflCpp/exception.h"

namespace EflCpp
{

Canvas::Object::Object(Canvas& canvas, Factory factory, const char* const objId)
    : EvasObj(createCanvasObject(canvas, factory), objId)
{
}

Evas_Object* Canvas::Object::createCanvasObject(Canvas& canvas, Factory factory)
{
    Evas_Object* obj = factory(canvas.getHandle());
    if (!obj)
    {
        throw EflException("failed to create canvas object");
    }

    return obj;
}

void Canvas::Object::setClipping(EvasObj& obj)
{
    evas_object_clip_set(getHandle(), EvasObj::getHandle(obj));
}

} // namespace EflCpp
