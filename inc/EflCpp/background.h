#pragma once

#include "EflCpp/geo.h"
#include "EflCpp/layout.h"

namespace EflCpp
{
class Background : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Background)
    ~Background();

    void setBgColor(Color color);
    Color getBgColor() const;

    static constexpr const char* ConcentOverlay = "overlay";

protected:
    Background(ElmObj& parent, const char* objId = BackgroundDefaultId);

private:
    static constexpr const char* BackgroundDefaultId = "BACKGROUND";
};
using BackgroundPtr = WidgetPtr<Background>;

} // namespace EflCpp
