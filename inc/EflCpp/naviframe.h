#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/elm_obj_item.h"
#include "EflCpp/layout.h"

#include <vector>

#include <boost/optional.hpp>

namespace EflCpp
{

class NaviFrame : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(NaviFrame);
    ~NaviFrame();

    class Item : private ElmObj::Item
    {
    public:
        EFLCPP_USE_DEFAULT_OBJITEM_METHODS

        void setStyle(const char* style);
        const char* getStyle() const;
    };

    Item pushItem(EvasObj& content, const char* label, EvasObj* prevButton = nullptr, EvasObj* nextButton = nullptr, const char* style = nullptr);
    Item pushItem(EvasObj& content);
    Item insertAfter(const Item& after, EvasObj& content, const char* label, EvasObj* prevButton = nullptr, EvasObj* nextButton = nullptr, const char* style = nullptr);
    Item insertBefore(const Item& before, EvasObj& content, const char* label, EvasObj* prevButton = nullptr, EvasObj* nextButton = nullptr, const char* style = nullptr);

    void popItem();
    void popTo(const Item& item);

    void promote(const Item& item);

    boost::optional<Item> getTopItem() const;
    boost::optional<Item> getBootmItem() const;

    std::vector<Item> getItems() const;

protected:
    NaviFrame(ElmObj& parent, const char* objId = NaviFrameDefaultId);

private:
    static Evas_Object* getButtonHandle(EvasObj* button);

private:
    static constexpr const char* NaviFrameDefaultId = "NAVIFRAME";
};
using NaviFramePtr = WidgetPtr<NaviFrame>;

} // namespace EflCpp
