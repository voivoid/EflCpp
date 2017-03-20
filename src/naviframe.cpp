#include "EflCpp/naviframe.h"

#include "EflCpp/assert.h"
#include "EflCpp/eina_list.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

NaviFrame::NaviFrame(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_naviframe_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

NaviFrame::~NaviFrame()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

NaviFrame::Item NaviFrame::pushItem(EvasObj& content, const char* const label, EvasObj* const prevButton, EvasObj* const nextButton, const char* const style)
{
    auto* itemPtr = elm_naviframe_item_push(getHandle(), label, getButtonHandle(prevButton), getButtonHandle(nextButton), EvasObj::getHandle(content), style);
    EFLCPP_ASSERT(itemPtr);
    return {*itemPtr};
}

NaviFrame::Item NaviFrame::pushItem(EvasObj& content)
{
    auto* itemPtr = elm_naviframe_item_simple_push(getHandle(), EvasObj::getHandle(content));
    EFLCPP_ASSERT(itemPtr);
    return {*itemPtr};
}

NaviFrame::Item NaviFrame::insertAfter(
    const Item& after, EvasObj& content, const char* const label, EvasObj* const prevButton, EvasObj* const nextButton, const char* const style)
{
    auto* itemPtr =
        elm_naviframe_item_insert_after(getHandle(), after.getHandle(), label, getButtonHandle(prevButton), getButtonHandle(nextButton), EvasObj::getHandle(content), style);
    EFLCPP_ASSERT(itemPtr);

    return {*itemPtr};
}

NaviFrame::Item NaviFrame::insertBefore(
    const Item& before, EvasObj& content, const char* const label, EvasObj* const prevButton, EvasObj* const nextButton, const char* const style)
{
    auto* itemPtr =
        elm_naviframe_item_insert_before(getHandle(), before.getHandle(), label, getButtonHandle(prevButton), getButtonHandle(nextButton), EvasObj::getHandle(content), style);
    EFLCPP_ASSERT(itemPtr);

    return {*itemPtr};
}

void NaviFrame::popItem()
{
    elm_naviframe_item_pop(getHandle());
}

void NaviFrame::popTo(const Item& item)
{
    elm_naviframe_item_pop_to(item.getHandle());
}

void NaviFrame::promote(const Item& item)
{
    elm_naviframe_item_promote(item.getHandle());
}

boost::optional<NaviFrame::Item> NaviFrame::getTopItem() const
{
    auto* itemPtr = elm_naviframe_top_item_get(getHandle());
    if (!itemPtr)
    {
        return {};
    }

    return {Item{*itemPtr}};
}

boost::optional<NaviFrame::Item> NaviFrame::getBootmItem() const
{
    auto* itemPtr = elm_naviframe_bottom_item_get(getHandle());
    if (!itemPtr)
    {
        return {};
    }

    return {Item{*itemPtr}};
}

std::vector<NaviFrame::Item> NaviFrame::getItems() const
{
    auto* itemsList = elm_naviframe_items_get(getHandle());
    return createVectorFromEinaList<Item, Elm_Object_Item*>(itemsList);
}

void NaviFrame::Item::setStyle(const char* const style)
{
    elm_naviframe_item_style_set(getHandle(), style);
}

const char* NaviFrame::Item::getStyle() const
{
    return elm_naviframe_item_style_get(getHandle());
}

Evas_Object* NaviFrame::getButtonHandle(EvasObj* const button)
{
    return button ? getHandle(*button) : nullptr;
}

} // namespace EflCpp
