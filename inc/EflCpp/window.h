#pragma once

#include "EflCpp/background.h"
#include "EflCpp/conformant.h"
#include "EflCpp/elm_obj.h"

namespace EflCpp
{

class Window : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(Window)
    ~Window();

    enum class Type
    {
        Basic,
        Splash
    };

    enum class IndicatorMode
    {
        Show,
        Hide
    };

    enum class IndicatorOpacity
    {
        TransparentBackground,
        Opaque,
        Transcluent,
        Transparent
    };

    void setTitle(const char* title);
    void setContent(ElmObj& widget);
    void setAutodel(bool autodel = true);

protected:
    Window(ElmObj* parent, const char* name, Type type = Type::Basic, const char* objId = WindowDefaultId);

    Background& getBackground();
    Conformant& getConformant();

private:
    void addResizeObject(ElmObj& widget);

private:
    static constexpr const char* WindowDefaultId = "WINDOW";

    WidgetPtr<Background> _background;
    WidgetPtr<Conformant> _conformant;
};

using WindowPtr = WidgetPtr<Window>;

} // namespace EflCpp
