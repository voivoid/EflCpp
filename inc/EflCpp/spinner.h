#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class Spinner : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(Spinner)
    ~Spinner();

protected:
    Spinner(ElmObj& parent, const char* objId = SpinnerDefaultId);

private:
    static constexpr const char* SpinnerDefaultId = "SPINNER";
};

} // namespace EflCpp
