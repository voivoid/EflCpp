#include "EflCpp/label.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

Label::Label(ElmObj& parent, const char* objId)
    : Layout(objId, &parent, &elm_label_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Label::~Label()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
