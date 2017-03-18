#include "EflCpp/elm_obj.h"

#include "EflCpp/assert.h"
#include "EflCpp/window.h"

#include <boost/polymorphic_cast.hpp>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

ElmObj::~ElmObj()
{
    assertWidgetIsValid();
}

void ElmObj::assertWidgetIsValid() const
{
    EFLCPP_ASSERT(elm_object_widget_check(getHandle()));
}

void ElmObj::setStyle(const char* const style)
{
    assertWidgetIsValid();
    elm_object_style_set(getHandle(), style);
}

const char* ElmObj::getStyle() const
{
    assertWidgetIsValid();
    return elm_object_style_get(getHandle());
}

std::string ElmObj::getText() const
{
    assertWidgetIsValid();
    return elm_object_text_get(getHandle());
}

void ElmObj::setText(const char* const text)
{
    assertWidgetIsValid();
    elm_object_text_set(getHandle(), text);
}

void ElmObj::disable(const bool disabled)
{
    assertWidgetIsValid();
    elm_object_disabled_set(getHandle(), disabled);
}

bool ElmObj::isDisabled() const
{
    assertWidgetIsValid();
    return elm_object_disabled_get(getHandle());
}

void ElmObj::allowFocus(const bool allow)
{
    assertWidgetIsValid();
    elm_object_focus_allow_set(getHandle(), allow);
}

void ElmObj::setFocus(const bool focus)
{
    assertWidgetIsValid();
    elm_object_focus_set(getHandle(), focus);
}

Window& ElmObj::getWindow() const
{
    auto* const obj = elm_object_top_widget_get(getHandle());
    EFLCPP_ASSERT(obj);

    EvasObj* evasobj = getPtr(*obj);
    EFLCPP_ASSERT(evasobj);

    return *boost::polymorphic_downcast<Window*>(evasobj);
}

} // namespace EflCpp
