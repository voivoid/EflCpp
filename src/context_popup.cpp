#include "EflCpp/context_popup.h"

#include "EflCpp/assert.h"
#include "EflCpp/eina_list.h"
#include "EflCpp/elementary_inc.h"
#include "EflCpp/elm_obj_item.h"
#include "EflCpp/log.h"
#include "EflCpp/safe_callback.h"

namespace EflCpp
{

namespace
{
void CtxPopupButtonCallback(void* const data, Evas_Object* const obj, void* const /*eventInfo*/)
{
    EFLCPP_ASSERT(data);
    const auto& handler = *reinterpret_cast<ContextPopup::Handler*>(data);

    LOG_CURRENT_SCOPE(EvasObj::getRef(*obj).getObjId(), "CLICKED");
    handler();
}
} // namespace anonymous

ContextPopup::ContextPopup(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_ctxpopup_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

ContextPopup::~ContextPopup()
{
    EFLCPP_LOG_OBJECT_METHOD;
    clear();
}

void ContextPopup::appendItem(UniqueWidgetPtr<Icon>&& icon, const char* const text, Handler handler)
{
    EFLCPP_ASSERT(handler);
    EFLCPP_ASSERT(icon || text);

    auto* handlerPtr = new Handler(std::move(handler));
    auto iconHandle = icon ? EvasObj::getHandle(releaseWidgetPtr(std::move(icon))) : nullptr;
    auto* itemPtr = elm_ctxpopup_item_append(getHandle(), text, iconHandle, EFLCPP_WRAP_INTO_SAFE_CALLBACK(CtxPopupButtonCallback), handlerPtr);
    _items.push_back(itemPtr);

    elm_object_item_data_set(itemPtr, handlerPtr);
}

void ContextPopup::appendItem(UniqueWidgetPtr<Icon>&& icon, Handler handler)
{
    appendItem(std::move(icon), nullptr, std::move(handler));
}

void ContextPopup::appendItem(const char* const text, Handler handler)
{
    appendItem(nullptr, text, std::move(handler));
}

void ContextPopup::setHorizontal(const bool horizontal)
{
    elm_ctxpopup_horizontal_set(getHandle(), horizontal);
}

void ContextPopup::dismiss()
{
    elm_ctxpopup_dismiss(getHandle());
}

void ContextPopup::clear()
{
    const auto& items = getItems();
    for (const auto& item : items.getItems())
    {
        void* data = item.getData();
        EFLCPP_ASSERT(data);

        delete reinterpret_cast<Handler*>(data);
    }
    _items.clear();

    elm_ctxpopup_clear(getHandle());
}

WidgetList ContextPopup::getItems() const
{
    return {_items};
}

} // namespace EflCpp
