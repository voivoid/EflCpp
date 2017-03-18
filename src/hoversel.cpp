#include "EflCpp/hoversel.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

HoverSel::HoverSel(ElmObj& parent, const char* const objId)
    : Button(parent, &elm_hoversel_add, objId)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

HoverSel::~HoverSel()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
