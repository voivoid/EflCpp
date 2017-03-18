#include "EflCpp/window.h"

#include "EflCpp/bimap.h"
#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

namespace
{
static const auto WindowTypeBiMap = makeUnorderedBimap<Window::Type, Elm_Win_Type>({{Window::Type::Basic, ELM_WIN_BASIC}, {Window::Type::Splash, ELM_WIN_SPLASH}});
}

Window::Window(ElmObj* parent, const char* const name, Type type, const char* const objId)
    : ElmObj(objId, parent, &elm_win_add, name, getBimapValueByKey(WindowTypeBiMap, type))
    , _background(Background::create(*this))
    , _conformant(Conformant::create(*this))
{
    EFLCPP_LOG_OBJECT_METHOD;

    setTitle(name);

    _background->setHintWeightPoint({HintExpand, HintExpand});
    _conformant->setHintWeightPoint({HintExpand, HintExpand});

    addResizeObject(*_background);
    addResizeObject(*_conformant);

    _background->show();
    _conformant->show();
}

Window::~Window()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Window::setTitle(const char* const title)
{
    elm_win_title_set(getHandle(), title);
}

void Window::setContent(ElmObj& widget)
{
    getConformant().setContent(widget);
}

void Window::setAutodel(const bool autodel)
{
    elm_win_autodel_set(getHandle(), autodel);
}

void Window::addResizeObject(ElmObj& widget)
{
    elm_win_resize_object_add(getHandle(), ElmObj::getHandle(widget));
}

Background& Window::getBackground()
{
    return *_background;
}

Conformant& Window::getConformant()
{
    return *_conformant;
}

} // namespace EflCpp
