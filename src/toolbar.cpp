#include "EflCpp/toolbar.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Toolbar::Toolbar(ElmObj& parent, const char* objId)
    : ElmObj(objId, &parent, &elm_toolbar_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Toolbar::~Toolbar()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
