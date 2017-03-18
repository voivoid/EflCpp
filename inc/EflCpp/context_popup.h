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

    static constexpr const char* EventDismissed = "dismissed";

protected:
    ContextPopup(ElmObj& parent, const char* objId = ContextPopupDefaultId);

private:
    WidgetList getItems() const;

private:
    static constexpr const char* ContextPopupDefaultId = "CONTEXTPOPUP";

    std::vector<Elm_Object_Item*> _items;
};
using ContextPopupPtr = WidgetPtr<ContextPopup>;

} // namespace EflCpp
