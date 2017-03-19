#include "EflCpp/elm_obj_item.h"

#include "EflCpp/assert.h"
#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

ElmObj::Item::Item(Elm_Object_Item* item)
    : _item(item)
{
    EFLCPP_ASSERT(_item);
}

ElmObj::Item::Item(Elm_Object_Item& item)
    : Item(&item)
{
}

void ElmObj::Item::setData(void* data, const SetDataMode mode)
{
    switch (mode)
    {
        case SetDataMode::DoNotOverwrite:
            EFLCPP_ASSERT(!getData());
            break;

        case SetDataMode::Overwrite:
            // do nothing
            break;
    }

    elm_object_item_data_set(getHandle(), data);
}

void* ElmObj::Item::getData() const
{
    return elm_object_item_data_get(getHandle());
}

void ElmObj::Item::resetData()
{
    setData(nullptr);
}

Elm_Object_Item* ElmObj::Item::getHandle() const
{
    EFLCPP_ASSERT(_item);
    return _item;
}
Elm_Object_Item* ElmObj::Item::getHandle()
{
    EFLCPP_ASSERT(_item);
    return _item;
}

ElmObj::Item::Item(Item&& item) noexcept
{
    _item = item._item;
    item._item = nullptr;
}

} // namespace EflCpp
