#include "EflCpp/genlist.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

GenList::GenList(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_genlist_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

GenList::~GenList()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

} // namespace EflCpp
