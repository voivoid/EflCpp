#include "EflCpp/button.h"

#include "EflCpp/log.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
Button::Button(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_button_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Button::Button(ElmObj& parent, DerivedClassFactory factory, const char* objId)
    : Layout(objId, &parent, factory)
{
}

Button::~Button()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
