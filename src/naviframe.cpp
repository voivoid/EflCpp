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

EvasObj* NaviFrame::popItem()
{
    Evas_Object* obj = elm_naviframe_item_pop(getHandle());
    if(!obj)
    {
        return nullptr;
    }

    return EvasObj::getPtr(*obj);
}

void NaviFrame::popTo(const Item& item)
{
    elm_naviframe_item_pop_to(item.getHandle());
}

void NaviFrame::promote(const Item& item)
{
    elm_naviframe_item_promote(item.getHandle());
}

void NaviFrame::promote(EvasObj& content)
{
    elm_naviframe_item_simple_promote(getHandle(), EvasObj::getHandle(content));
}

void NaviFrame::enablePreserveOnPop(const bool preserve)
{
    elm_naviframe_content_preserve_on_pop_set(getHandle(), preserve);
}

bool NaviFrame::isPreservedOnPop() const
{
    return elm_naviframe_content_preserve_on_pop_get(getHandle());
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

boost::optional<NaviFrame::Item> NaviFrame::getBootomItem() const
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

void NaviFrame::Item::enableTitle(const bool enable, const bool transition)
{
    elm_naviframe_item_title_enabled_set(getHandle(), enable, transition);
}

bool NaviFrame::Item::isTitleEnabled() const
{
    return elm_naviframe_item_title_enabled_get(getHandle());
}

Evas_Object* NaviFrame::getButtonHandle(EvasObj* const button)
{
    return button ? getHandle(*button) : nullptr;
}

void NaviFrame::enableAutoCreatePrevButton(bool enable)
{
    elm_naviframe_event_enabled_set(getHandle(), enable);
}

bool NaviFrame::isAutoCreatingPrevButton() const
{
    return elm_naviframe_event_enabled_get(getHandle());
}

void NaviFrame::enablePushPopEvent(bool enable)
{
    elm_naviframe_event_enabled_set(getHandle(), enable);
}

bool NaviFrame::isPushPopEventEnabled() const
{
    return elm_naviframe_event_enabled_get(getHandle());
}

} // namespace EflCpp
