#pragma once

#include "EflCpp/elm_obj.h"

namespace EflCpp
{
class ProgressBar : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(ProgressBar)
    ~ProgressBar();

    void setPulse(bool pulse = true);
    bool getPulse() const;
    void pulse(bool pulse = true);

protected:
    ProgressBar(ElmObj& parent, const char* objId = ProgressBarDefaultId);

private:
    static constexpr const char* ProgressBarDefaultId = "PROGRESS";
};
using ProgressBarPtr = WidgetPtr<ProgressBar>;

} // namespace EflCpp
