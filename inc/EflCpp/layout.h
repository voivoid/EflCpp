#pragma once

#include "EflCpp/container.h"

namespace EflCpp
{
class Layout : public Container
{
public:
    void relayout();

protected:
    using Container::Container;
};

} // namespace EflCpp
