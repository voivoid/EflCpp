#include "EflCpp/progress_bar.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
ProgressBar::ProgressBar(ElmObj& parent, const char* const objId)
    : ElmObj(objId, &parent, &elm_progressbar_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

ProgressBar::~ProgressBar()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void ProgressBar::setPulse(const bool pulse)
{
    elm_progressbar_pulse_set(getHandle(), pulse);
}

bool ProgressBar::getPulse() const
{
    return elm_progressbar_pulse_get(getHandle());
}

void ProgressBar::pulse(const bool pulse)
{
    elm_progressbar_pulse(getHandle(), pulse);
}
} // namespace EflCpp
