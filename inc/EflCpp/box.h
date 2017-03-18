#pragma once

#include "EflCpp/elm_obj.h"
#include "EflCpp/geo.h"

namespace EflCpp
{
class Box : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(Box)
    ~Box();

    enum class Mode
    {
        Horizontal,
        Vertical
    };

    void packStart(EvasObj& widget);
    void packEnd(EvasObj& widget);

    void packBefore(EvasObj& widget, EvasObj& before);
    void packAfter(EvasObj& widget, EvasObj& after);

    void unpack(EvasObj& widget);
    void unpackAll();
    void clear();

    void setHomogeneous(bool homogeneous = true);
    void setAlign(double horizontal, double vertical);
    void setPadding(CoordUnit horizontal, CoordUnit vertical);

    void recalculate();

protected:
    Box(ElmObj& parent, Mode mode, const char* objId = BoxDefaultId);

private:
    static constexpr const char* BoxDefaultId = "BOX";
};
using BoxPtr = WidgetPtr<Box>;

} // namespace EflCpp
