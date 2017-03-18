#include "EflCpp/popup.h"

#include "EflCpp/assert.h"
#include "EflCpp/bimap.h"
#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

namespace
{

static const auto OrientationBimap = makeUnorderedBimap<Popup::Orientation, Elm_Popup_Orient>({
    {Popup::Orientation::Center, ELM_POPUP_ORIENT_CENTER},
    {Popup::Orientation::Top, ELM_POPUP_ORIENT_TOP},
    {Popup::Orientation::Left, ELM_POPUP_ORIENT_LEFT},
    {Popup::Orientation::Right, ELM_POPUP_ORIENT_RIGHT},
    {Popup::Orientation::Bottom, ELM_POPUP_ORIENT_BOTTOM},
    {Popup::Orientation::TopLeft, ELM_POPUP_ORIENT_TOP_LEFT},
    {Popup::Orientation::TopRight, ELM_POPUP_ORIENT_TOP_RIGHT},
    {Popup::Orientation::BottomLeft, ELM_POPUP_ORIENT_BOTTOM_LEFT},
    {Popup::Orientation::BottomRight, ELM_POPUP_ORIENT_BOTTOM_RIGHT},
});
static const auto WrapBiMap = makeUnorderedBimap<Popup::Wrap, Elm_Wrap_Type>({
    {Popup::Wrap::None, ELM_WRAP_NONE}, {Popup::Wrap::Char, ELM_WRAP_CHAR}, {Popup::Wrap::Word, ELM_WRAP_WORD}, {Popup::Wrap::Mixed, ELM_WRAP_MIXED},
});
}

Popup::Popup(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_popup_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Popup::~Popup()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Popup::setTimeout(const double seconds)
{
    elm_popup_timeout_set(getHandle(), seconds);
}

void Popup::setAlignmentPoint(const EvasObj::AlignmentPoint point)
{
    elm_popup_align_set(getHandle(), point.x, point.y);
}

std::string Popup::getTitle() const
{
    return elm_object_part_text_get(getHandle(), "title,text");
}

void Popup::setTitle(const char* const text)
{
    elm_object_part_text_set(getHandle(), "title,text", text);
}

void Popup::setOrientation(const Orientation orientation)
{
    elm_popup_orient_set(getHandle(), getBimapValueByKey(OrientationBimap, orientation));
}

Popup::Orientation Popup::getOrientation() const
{
    return getBimapKeyByValue(OrientationBimap, elm_popup_orient_get(getHandle()));
}

void Popup::setWrap(const Wrap wrap)
{
    elm_popup_content_text_wrap_type_set(getHandle(), getBimapValueByKey(WrapBiMap, wrap));
}

Popup::Wrap Popup::getWrap() const
{
    return getBimapKeyByValue(WrapBiMap, elm_popup_content_text_wrap_type_get(getHandle()));
}

} // namespace EflCpp
