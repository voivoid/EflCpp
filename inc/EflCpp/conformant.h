#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{
class Window;
class Conformant : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Conformant)
    ~Conformant();

protected:
    Conformant(Window& parent, const char* objId = ConformantDefaultId);

private:
    static constexpr const char* ConformantDefaultId = "CONFORMANT";
};
using ConformantPtr = WidgetPtr<Conformant>;

} // namespace EflCpp
