#include "EflCpp/dialog.h"

#include "EflCpp/assert.h"
#include "EflCpp/button.h"
#include "EflCpp/table.h"
#include "EflCpp/window.h"

#include <boost/range/adaptor/indexed.hpp>

#include <array>

namespace EflCpp
{

namespace
{
PopupPtr makeDialog(Window& parent, const char* const title, DialogButton::Handler onCloseHandler, const char* const objId)
{
    auto popup = Popup::create(parent, objId);
    popup->setTitle(title);

#ifdef EFLCPP_TIZEN
    popup->setEventHandler(EvasEvent::BackButtonPressed, [onClose = std::move(onCloseHandler)](EvasObj&) { onClose(); });
#else
    popup->setSmartEventHandler(Popup::EventBlockClicked, [onClose = std::move(onCloseHandler)](ElmObj&, void*) { onClose(); });
#endif

    return popup;
}
}

PopupPtr makeDialog(Window& parent, const char* const title, const char* const text, std::vector<DialogButton> buttonsInfos, DialogButton::Handler onCloseHandler, const char* const objId)
{
    EFLCPP_ASSERT(buttonsInfos.size() <= 3);

    auto popup = makeDialog(parent, title, std::move(onCloseHandler), objId);
    popup->setText(text);

    static constexpr std::array<const char*, 3> buttonPartNames = {{"button1", "button2", "button3"}};

    for (const auto& indexedButtonInfo : buttonsInfos | boost::adaptors::indexed(0))
    {
        const size_t partNameIndex = indexedButtonInfo.index();
        const auto& buttonInfo = indexedButtonInfo.value();
        if (!buttonInfo.isVisible)
        {
            continue;
        }

        EFLCPP_ASSERT(partNameIndex < buttonPartNames.size());
        const auto* partName = buttonPartNames[partNameIndex];

        auto btn = Button::createUnique(*popup, partName);
        btn->setText(buttonInfo.text);
#ifdef EFLCPP_TIZEN
        btn->setStyle(Button::StylePopup);
#endif
        btn->setSmartEventHandler(Button::EventClicked, [handler = std::move(buttonInfo.handler)](ElmObj&, void*) { handler(); });

        popup->setPartContent(releaseWidgetPtr(std::move(btn)), partName);
    }

    return popup;
}

PopupPtr makeDialog(Window& parent, const char* title, ElmObj& content, DialogButton::Handler onCloseHandler, const char* objId)
{
    auto popup = makeDialog(parent, title, std::move(onCloseHandler), objId);
    popup->setContent(content);
    return popup;
}

} // namespace EflCpp
