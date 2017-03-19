#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{
class Button : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Button)
    ~Button();

    static constexpr const char* StylePopup = "popup";
    static constexpr const char* StyleContacts = "contacts";

protected:
    Button(ElmObj& parent, const char* objId = ButtonDefaultId);

    using DerivedClassFactory = Evas_Object* (*)(Evas_Object*);
    Button(ElmObj& parent, DerivedClassFactory factory, const char* objId);

private:
    static constexpr const char* ButtonDefaultId = "BUTTON";
};
using ButtonPtr = WidgetPtr<Button>;

} // namespace EflCpp
