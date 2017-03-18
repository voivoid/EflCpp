#include "EflCpp/conformant.h"

#include "EflCpp/window.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Conformant::Conformant(Window& parent, const char* const objId)
    : Layout(objId, &parent, &elm_conformant_add)
{
    EFLCPP_LOG_OBJECT_METHOD;

    elm_win_conformant_set(ElmObj::getHandle(parent), EINA_TRUE);
}

Conformant::~Conformant()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
