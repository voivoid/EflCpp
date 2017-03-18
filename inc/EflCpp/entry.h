#pragma once

#include "EflCpp/elm_obj.h"
#include "EflCpp/scrollable.h"

namespace EflCpp
{
class Entry : public ElmObj, public Scrollable
{
public:
    EFLCPP_DECL_EFL_WIDGET(Entry)
    ~Entry();

    void setSingleLine(bool enable = true);
    void setScrollable(bool scrollable = true);
    void setPasswordMode(bool enable = true);
    void setEditableMode(bool editable = true);

    enum class Wrap
    {
        None,
        Char,
        Word,
        Mixed
    };
    void setWrap(Wrap wrap);
    Wrap getWrap() const;

    void showInputPanel(bool show = true);

    void allowPrediction(bool allow = true);

    enum class AutoCapitalMode
    {
        None,
        Word,
        Sentence,
        AllChars
    };
    void setAutoCapitalMode(AutoCapitalMode mode);
    AutoCapitalMode getAutoCapitalMode() const;

    void setReturnKeyAutoEnable(bool mode = true);
    void disableReturnKey(bool disable = true);

    enum class ReturnKey
    {
        Next,
        Done,
        Login
    };
    void setReturnKeyType(ReturnKey key);
    ReturnKey getReturnKeyType() const;

    void setGuideText(const char* text);

    static constexpr const char* EventChanged = "changed";
    static constexpr const char* EventActivated = "activated";

protected:
    Entry(ElmObj& parent, const char* objId = EntryDefaultId);

private:
    static constexpr const char* EntryDefaultId = "ENTRY";
};
using EntryPtr = WidgetPtr<Entry>;

} // namespace EflCpp
