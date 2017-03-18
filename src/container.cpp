#include "EflCpp/container.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

void Container::setPartContent(EvasObj& w, const char* const part)
{
    elm_object_part_content_unset(getHandle(), part);
    elm_object_part_content_set(getHandle(), part, EvasObj::getHandle(w));
}

void Container::setContent(EvasObj& w)
{
    elm_object_content_unset(getHandle());
    elm_object_content_set(getHandle(), EvasObj::getHandle(w));
}

EvasObj* Container::unsetContent()
{
    auto* const oldContent = elm_object_content_unset(getHandle());
    return oldContent ? EvasObj::getPtr(*oldContent) : nullptr;
}

} // namespace EflCpp
