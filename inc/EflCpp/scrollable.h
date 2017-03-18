#pragma once

#include "EflCpp/elementary_fwd.h"

#include <utility>

namespace EflCpp
{

class Scrollable
{
public:
    Scrollable(Evas_Object& obj);

    enum class MovementBlock
    {
        None,
        Horizontal,
        Vertical,
        Both
    };
    void setBlock(MovementBlock);
    MovementBlock getBlock() const;

    enum class BarVisibility
    {
        Auto,
        On,
        Off
    };
    void setBarVisibility(BarVisibility hPolicy, BarVisibility vPolicy);
    std::pair<BarVisibility, BarVisibility> getBarVisibility() const;

private:
    Evas_Object& _obj;
};

} // namespace EflCpp
