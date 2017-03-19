#pragma once

#include "EflCpp/elm_obj_item.h"
#include "EflCpp/icon.h"
#include "EflCpp/layout.h"

#include <vector>

namespace EflCpp
{
class ContextPopup : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(ContextPopup)
    ~ContextPopup();

    using Handler = std::function<void()>;
    void appendItem(UniqueWidgetPtr<Icon>&& icon, Handler handler);
    void appendItem(const char* text, Handler handler);
    void appendItem(UniqueWidgetPtr<Icon>&& icon, const char* text, Handler handler);

    void setHorizontal(bool horizontal = true);

    void clear();
    void dismiss();

    class Item : private ElmObj::Item
    {
    public:
        EFLCPP_USE_DEFAULT_OBJITEM_METHODS
    };
    const std::vector<Item>& getItems() const;

    static constexpr const char* EventDismissed = "dismissed";

protected:
    ContextPopup(ElmObj& parent, const char* objId = ContextPopupDefaultId);

private:
    static constexpr const char* ContextPopupDefaultId = "CONTEXTPOPUP";

    std::vector<Item> _items;
};
using ContextPopupPtr = WidgetPtr<ContextPopup>;

} // namespace EflCpp
