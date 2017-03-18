#include "EflCpp/elm_obj_item.h"

#include "EflCpp/assert.h"
#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

ElmObjItem::ElmObjItem(Elm_Object_Item& item)
    : _item(&item)
{
    EFLCPP_ASSERT(_item)
}

void ElmObjItem::setData(void* data, const SetDataMode mode)
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

void* ElmObjItem::getData() const
{
    return elm_object_item_data_get(getHandle());
}

void ElmObjItem::resetData()
{
    setData(nullptr);
}

Elm_Object_Item* ElmObjItem::getHandle() const
{
    EFLCPP_ASSERT(_item);
    return _item;
}
Elm_Object_Item* ElmObjItem::getHandle()
{
    EFLCPP_ASSERT(_item);
    return _item;
}

WidgetList::WidgetList(const std::vector<Elm_Object_Item*>& items)
{
    _items.reserve(items.size());
    for (const auto& item : items)
    {
        _items.push_back(ElmObjItem(*item));
    }
}

std::vector<ElmObjItem>& WidgetList::getItems()
{
    return _items;
}

const std::vector<ElmObjItem>& WidgetList::getItems() const
{
    return _items;
}

} // namespace EflCpp
