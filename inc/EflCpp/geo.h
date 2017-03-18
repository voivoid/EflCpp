#pragma once

#include "EflCpp/elementary_fwd.h"

namespace EflCpp
{
namespace Details
{

template <typename T>
struct Size2D
{
    constexpr Size2D(T width, T height)
        : width(width)
        , height(height)
    {
    }
    const T width;
    const T height;
};

template <typename T>
struct Point2D
{
    constexpr Point2D(T x, T y)
        : x(x)
        , y(y)
    {
    }
    const T x;
    const T y;
};

template <typename T>
struct Rect2D
{
    constexpr Rect2D(T left, T top, T right, T bottom)
        : left(left)
        , top(top)
        , right(right)
        , bottom(bottom)
    {
    }
    const T left;
    const T top;
    const T right;
    const T bottom;

    constexpr T width() const
    {
        return right - left;
    }
    constexpr T height() const
    {
        return bottom - top;
    }
};

template <typename T>
struct ColorRGBA
{
    constexpr ColorRGBA(T r, T g, T b, T a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }
    const T r;
    const T g;
    const T b;
    const T a;
};

} // namespace Details

using CoordUnit = Evas_Coord;
using CoordSize = Details::Size2D<CoordUnit>;
using CoordPoint = Details::Point2D<CoordUnit>;
using CoordRect = Details::Rect2D<CoordUnit>;
using Color = Details::ColorRGBA<int>;

} // namespace EflCpp
