#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/elm_obj.h"

#include <memory>
#include <vector>

namespace EflCpp
{

class ElmObjItem
{
public:
    ElmObjItem(Elm_Object_Item& item);

    enum class SetDataMode
    {
        Overwrite,
        DoNotOverwrite
    };
    void setData(void* data, SetDataMode mode = SetDataMode::DoNotOverwrite);
    void* getData() const;
    void resetData();

    Elm_Object_Item* getHandle() const;
    Elm_Object_Item* getHandle();

private:
    Elm_Object_Item* _item;
    const WidgetPtr<const EvasObj> _obj;
};

class WidgetList
{
public:
    WidgetList(const std::vector<Elm_Object_Item*>& items);

    std::vector<ElmObjItem>& getItems();
    const std::vector<ElmObjItem>& getItems() const;

private:
    std::vector<ElmObjItem> _items;
    const WidgetPtr<const EvasObj> _obj;
};

} // namespace EflCpp
