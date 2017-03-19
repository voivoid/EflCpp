#pragma once

#include "EflCpp/popup.h"

#include <functional>
#include <string>
#include <vector>

namespace EflCpp
{

struct DialogButton
{
    using Handler = std::function<void()>;
    DialogButton(const char* const text, Handler handler, const bool isVisible = true)
        : text(text)
        , handler(std::move(handler))
        , isVisible(isVisible)
    {
    }

    const char* const text;
    const Handler handler;
    const bool isVisible;
};

class Window;
PopupPtr makeDialog(
    Window& parent, const char* title, const char* text, std::vector<DialogButton> buttons, DialogButton::Handler onCloseHandler, const char* objId = "DIALOG");
PopupPtr makeDialog(Window& parent, const char* title, ElmObj& content, DialogButton::Handler onCloseHandler, const char* objId = "DIALOG");

} // namespace EflCpp
