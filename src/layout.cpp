#include "EflCpp/layout.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

void Layout::relayout()
{
    elm_layout_sizing_eval(getHandle());
}

} // namespace EflCpp
