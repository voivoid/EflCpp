#pragma once

#include "EflCpp/elm_obj.h"

namespace EflCpp
{
class Window;
class Container : public ElmObj
{
public:
    void setPartContent(EvasObj& w, const char* part);
    void setContent(EvasObj& w);

    EvasObj* unsetContent();

protected:
    using ElmObj::ElmObj;
};

} // namespace EflCpp
