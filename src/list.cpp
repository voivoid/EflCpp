#include "EflCpp/list.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

List::List(ElmObj& parent, const char* objId)
    : Layout(objId, &parent, &elm_list_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

List::~List()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
