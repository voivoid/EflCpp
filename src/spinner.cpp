#include "EflCpp/spinner.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Spinner::Spinner(ElmObj& parent, const char* objId)
    : Layout(objId, &parent, &elm_spinner_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Spinner::~Spinner()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
