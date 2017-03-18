#include "EflCpp/image.h"

#include "EflCpp/assert.h"
#include "EflCpp/bimap.h"

#include <boost/filesystem.hpp>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

namespace
{

static const auto OrientationBimap = makeUnorderedBimap<Image::Orientation, Elm_Image_Orient>({
    {Image::Orientation::Default, ELM_IMAGE_ORIENT_NONE},
    {Image::Orientation::Rotate90, ELM_IMAGE_ROTATE_90},
    {Image::Orientation::Rotate180, ELM_IMAGE_ROTATE_180},
    {Image::Orientation::Rotate270, ELM_IMAGE_ROTATE_270},
    {Image::Orientation::FlipHorizontal, ELM_IMAGE_FLIP_HORIZONTAL},
    {Image::Orientation::FlipVertical, ELM_IMAGE_FLIP_VERTICAL},
    {Image::Orientation::FlipTranspose, ELM_IMAGE_FLIP_TRANSPOSE},
    {Image::Orientation::FlipTransverse, ELM_IMAGE_FLIP_TRANSVERSE},
});
}

Image::Image(ElmObj& parent, const char* const objId)
    : ElmObj(objId, &parent, &elm_image_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Image::~Image()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

Image::Image(ElmObj& parent, const DerivedClassFactory factory, const char* const objId)
    : ElmObj(objId, &parent, factory)
{
}

CoordSize Image::getImageSize() const
{
    int width, height;
    elm_image_object_size_get(getHandle(), &width, &height);
    EFLCPP_ASSERT(width);
    EFLCPP_ASSERT(height);

    return {width, height};
}

void Image::setFile(const boost::filesystem::path& path)
{
    if (!boost::filesystem::exists(path))
    {
        EFLCPP_FAIL_WITH_MESSAGE(std::string("Failed to load image: ") + path.string());
    }

    auto res = elm_image_file_set(getHandle(), path.string().c_str(), nullptr);
    EFLCPP_ASSERT(res);
}

void Image::setOrient(const Orientation orientation)
{
    elm_image_orient_set(getHandle(), getBimapValueByKey(OrientationBimap, orientation));
}

Image::Orientation Image::getOrient() const
{
    return getBimapKeyByValue(OrientationBimap, elm_image_orient_get(getHandle()));
}

void Image::setFixedAspect(const bool fixed)
{
    elm_image_aspect_fixed_set(getHandle(), fixed);
}

void Image::setFillOutside(const bool enable)
{
    elm_image_fill_outside_set(getHandle(), enable);
}

} // namespace EflCpp
