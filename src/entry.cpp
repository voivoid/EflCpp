#include "EflCpp/entry.h"

#include "EflCpp/assert.h"
#include "EflCpp/bimap.h"
#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

namespace
{

static const auto AutoCapitalModeBimap =
    makeUnorderedBimap<Entry::AutoCapitalMode, Elm_Autocapital_Type>({{Entry::AutoCapitalMode::None, ELM_AUTOCAPITAL_TYPE_NONE},
                                                                      {Entry::AutoCapitalMode::Word, ELM_AUTOCAPITAL_TYPE_WORD},
                                                                      {Entry::AutoCapitalMode::Sentence, ELM_AUTOCAPITAL_TYPE_SENTENCE},
                                                                      {Entry::AutoCapitalMode::AllChars, ELM_AUTOCAPITAL_TYPE_ALLCHARACTER}});

static const auto ReturnKeyTypeBimap = makeUnorderedBimap<Entry::ReturnKey, Elm_Input_Panel_Return_Key_Type>({{Entry::ReturnKey::Done, ELM_INPUT_PANEL_RETURN_KEY_TYPE_DONE},
                                                                                                              {Entry::ReturnKey::Login, ELM_INPUT_PANEL_RETURN_KEY_TYPE_LOGIN},
                                                                                                              {Entry::ReturnKey::Next, ELM_INPUT_PANEL_RETURN_KEY_TYPE_NEXT}});

static const auto WrapBiMap = makeUnorderedBimap<Entry::Wrap, Elm_Wrap_Type>({
    {Entry::Wrap::None, ELM_WRAP_NONE}, {Entry::Wrap::Char, ELM_WRAP_CHAR}, {Entry::Wrap::Word, ELM_WRAP_WORD}, {Entry::Wrap::Mixed, ELM_WRAP_MIXED},
});
}

Entry::Entry(ElmObj& parent, const char* const objId)
    : ElmObj(objId, &parent, &elm_entry_add)
    , Scrollable(*getHandle())
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Entry::~Entry()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void Entry::setScrollable(const bool scrollable)
{
    elm_entry_scrollable_set(getHandle(), scrollable);
}

void Entry::allowPrediction(const bool allow)
{
    elm_entry_prediction_allow_set(getHandle(), allow);
}

void Entry::setAutoCapitalMode(const AutoCapitalMode mode)
{
    elm_entry_autocapital_type_set(getHandle(), getBimapValueByKey(AutoCapitalModeBimap, mode));
}

Entry::AutoCapitalMode Entry::getAutoCapitalMode() const
{
    return getBimapKeyByValue(AutoCapitalModeBimap, elm_entry_autocapital_type_get(getHandle()));
}

void Entry::setPasswordMode(const bool enable)
{
    elm_entry_password_set(getHandle(), enable);
}

void Entry::setSingleLine(const bool enable)
{
    elm_entry_single_line_set(getHandle(), enable);
}

void Entry::setGuideText(const char* const text)
{
    elm_object_part_text_set(getHandle(), "elm.guide", text);
}

void Entry::setReturnKeyAutoEnable(const bool mode)
{
    elm_entry_input_panel_return_key_autoenabled_set(getHandle(), mode);
}

void Entry::disableReturnKey(const bool disable)
{
    elm_entry_input_panel_return_key_disabled_set(getHandle(), disable);
}

void Entry::setReturnKeyType(const ReturnKey key)
{
    elm_entry_input_panel_return_key_type_set(getHandle(), getBimapValueByKey(ReturnKeyTypeBimap, key));
}

Entry::ReturnKey Entry::getReturnKeyType() const
{
    return getBimapKeyByValue(ReturnKeyTypeBimap, elm_entry_input_panel_return_key_type_get(getHandle()));
}

void Entry::showInputPanel(const bool show)
{
    const auto f = show ? elm_entry_input_panel_show : elm_entry_input_panel_hide;
    f(getHandle());
}

void Entry::setEditableMode(const bool editable)
{
    elm_entry_editable_set(getHandle(), editable);
}

void Entry::setWrap(const Wrap wrap)
{
    elm_entry_line_wrap_set(getHandle(), getBimapValueByKey(WrapBiMap, wrap));
}

Entry::Wrap Entry::getWrap() const
{
    return getBimapKeyByValue(WrapBiMap, elm_entry_line_wrap_get(getHandle()));
}

} // namespace EflCpp
