#pragma once

#include "EflCpp/canvas.h"
#include "EflCpp/evas_obj.h"

namespace EflCpp
{

class Canvas::Object : public EvasObj
{
public:
    void setClipping(EvasObj& obj);

protected:
    using Factory = Evas_Object* (*)(Evas*);
    Object(Canvas& canvas, Factory factory, const char* objId);

private:
    static Evas_Object* createCanvasObject(Canvas& canvas, Factory factory);
};

} // namespace EflCpp
