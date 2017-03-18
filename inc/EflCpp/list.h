#pragma once

#include "EflCpp/layout.h"

namespace EflCpp
{

class List : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(List)
    ~List();

protected:
    List(ElmObj& parent, const char* objId = ListDefaultId);

private:
    static constexpr const char* ListDefaultId = "LIST";
};

} // namespace EflCpp
