#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/geo.h"

namespace EflCpp
{

class EvasObj;
class Canvas
{
public:
    Canvas(CoordSize size);
    Canvas(EvasObj&);

    ~Canvas();

    class Object;

private:
    const Evas* getHandle() const;
    Evas* getHandle();

private:
    Ecore_Evas* const _ecoreEvas;
    Evas* const _evas;
};

} // namespace EflCpp
