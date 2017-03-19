#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/elm_obj.h"

#include <memory>
#include <vector>

namespace EflCpp
{

#define EFLCPP_USE_DEFAULT_OBJITEM_METHODS \
    using ElmObj::Item::setData;           \
    using ElmObj::Item::getData;           \
    using ElmObj::Item::resetData;         \
    using ElmObj::Item::Item;              \
    using ElmObj::Item::getHandle;

class ElmObj::Item
{
public:
    enum class SetDataMode
    {
        Overwrite,
        DoNotOverwrite
    };

    Item(Elm_Object_Item* item);
    Item(Elm_Object_Item& item);
    Item(Item&& item) noexcept;
    Item& operator=(Item&& item) = delete;
    DISABLE_COPY_SEMANTICS(Item);

    void setData(void* data, SetDataMode mode = SetDataMode::DoNotOverwrite);
    void* getData() const;
    void resetData();

    Elm_Object_Item* getHandle() const;
    Elm_Object_Item* getHandle();

private:
    Elm_Object_Item* _item;
};

} // namespace EflCpp
