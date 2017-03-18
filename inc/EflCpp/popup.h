#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{
class Popup : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Popup)
    ~Popup();

    std::string getTitle() const;
    void setTitle(const char* title);

    void setTimeout(double seconds);

    enum class Orientation
    {
        Center,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    void setOrientation(Orientation orientation);
    Orientation getOrientation() const;

    enum class Wrap
    {
        None,
        Char,
        Word,
        Mixed
    };
    void setWrap(const Wrap mode);
    Wrap getWrap() const;

    void setAlignmentPoint(AlignmentPoint);

    static constexpr const char* EventBlockClicked = "block,clicked";
    static constexpr const char* EventTimeout = "timeout";

protected:
    Popup(ElmObj& parent, const char* objId = ProgressBarDefaultId);

private:
    static constexpr const char* ProgressBarDefaultId = "POPUP";
};
using PopupPtr = WidgetPtr<Popup>;

} // namespace EflCpp
