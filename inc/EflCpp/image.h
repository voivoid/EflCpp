/*
 * Copyright (c) New Cloud Technologies, Ltd., 2013-2016
 *
 * You can not use the contents of the file in any way without
 * New Cloud Technologies, Ltd. written permission.
 *
 * To obtain such a permit, you should contact New Cloud Technologies, Ltd.
 * at http://ncloudtech.com/contact.html
 *
 */
#pragma once

#include "EflCpp/elm_obj.h"
#include "EflCpp/geo.h"

namespace boost
{
namespace filesystem
{
class path;
}
}

namespace EflCpp
{
class Image : public ElmObj
{
public:
    EFLCPP_DECL_EFL_WIDGET(Image)
    ~Image();

    void setFile(const boost::filesystem::path& path);
    CoordSize getImageSize() const;

    void setFixedAspect(bool fixed = true);
    void setFillOutside(bool enable = true);

    enum class Orientation
    {
        Default,
        Rotate90,
        Rotate180,
        Rotate270,
        FlipVertical,
        FlipHorizontal,
        FlipTranspose,
        FlipTransverse
    };
    void setOrient(Orientation orientation);
    Orientation getOrient() const;

protected:
    Image(ElmObj& parent, const char* objId = ImageDefaultId);

    using DerivedClassFactory = Evas_Object* (*)(Evas_Object*);
    Image(ElmObj& parent, DerivedClassFactory factory, const char* objId);

private:
    static constexpr const char* ImageDefaultId = "IMAGE";
};
using ImagePtr = WidgetPtr<Image>;

} // namespace EflCpp
