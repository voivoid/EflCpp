#include "EflCpp/evas_obj.h"

#include "EflCpp/assert.h"
#include "EflCpp/bimap.h"
#include "EflCpp/log.h"

#include <limits>

#include "EflCpp/elementary_inc.h"

namespace
{
const char* EvasObjRefKey = "eflcpp_evasobj_ref";

size_t CreatedObjects = 0;
size_t DeletedObjects = 0;

static const auto DisplayModeBimap =
    EflCpp::makeUnorderedBimap<EflCpp::EvasObj::DisplayMode, Evas_Display_Mode>({{EflCpp::EvasObj::DisplayMode::Default, EVAS_DISPLAY_MODE_NONE},
                                                                                 {EflCpp::EvasObj::DisplayMode::Compress, EVAS_DISPLAY_MODE_COMPRESS},
                                                                                 {EflCpp::EvasObj::DisplayMode::Expand, EVAS_DISPLAY_MODE_EXPAND},
                                                                                 {EflCpp::EvasObj::DisplayMode::DontChange, EVAS_DISPLAY_MODE_DONT_CHANGE}});

static const auto AspectControlBimap =
    EflCpp::makeUnorderedBimap<EflCpp::EvasObj::AspectControl, Evas_Aspect_Control>({{EflCpp::EvasObj::AspectControl::Default, EVAS_ASPECT_CONTROL_NONE},
                                                                                     {EflCpp::EvasObj::AspectControl::Neither, EVAS_ASPECT_CONTROL_NEITHER},
                                                                                     {EflCpp::EvasObj::AspectControl::Horizontal, EVAS_ASPECT_CONTROL_HORIZONTAL},
                                                                                     {EflCpp::EvasObj::AspectControl::Vertical, EVAS_ASPECT_CONTROL_VERTICAL},
                                                                                     {EflCpp::EvasObj::AspectControl::Both, EVAS_ASPECT_CONTROL_BOTH}});

void evasDelCallback(void* const evasObj, Evas* const, Evas_Object* const, void* const)
{
    EFLCPP_ASSERT(evasObj);
    auto obj = reinterpret_cast<EflCpp::EvasObj*>(evasObj);
    delete obj;
}
}

namespace EflCpp
{
EvasObj::EvasObj(Evas_Object* const obj, const char* const objId)
    : _obj(obj)
    , _objId(nullptr)
{
    EFLCPP_ASSERT(_obj);
    EFLCPP_ASSERT(objId);

    _objId = strdup(objId);

    incRefCount();
    setData(EvasObjRefKey, this);
    evas_object_event_callback_add(_obj, EVAS_CALLBACK_DEL, &evasDelCallback, this);

    ++CreatedObjects;
}

EvasObj::~EvasObj()
{
    ++DeletedObjects;
}

Evas_Object* EvasObj::getHandle()
{
    return _obj;
}

const Evas_Object* EvasObj::getHandle() const
{
    return _obj;
}

const Evas_Object* EvasObj::getHandle(const EvasObj& o)
{
    return o.getHandle();
}

Evas_Object* EvasObj::getHandle(EvasObj& o)
{
    return o.getHandle();
}

const Evas_Object* EvasObj::Access::getHandle(const EvasObj& o)
{
    return EvasObj::getHandle(o);
}

Evas_Object* EvasObj::Access::getHandle(EvasObj& o)
{
    return EvasObj::getHandle(o);
}

EvasObj& EvasObj::getRef(Evas_Object& obj)
{
    void* data = evas_object_data_get(&obj, EvasObjRefKey);
    EFLCPP_ASSERT(data);

    EvasObj& evasObj = *reinterpret_cast<EvasObj*>(data);
    EFLCPP_ASSERT(EvasObj::getHandle(evasObj) == &obj);

    return evasObj;
}

EvasObj* EvasObj::getPtr(Evas_Object& obj)
{
    return &getRef(obj);
}

void EvasObj::show()
{
    evas_object_show(getHandle());
}

void EvasObj::hide()
{
    evas_object_hide(getHandle());
}

bool EvasObj::isVisible() const
{
    return evas_object_visible_get(getHandle());
}

CoordRect EvasObj::getGeometry() const
{
    Evas_Coord x = 0;
    Evas_Coord y = 0;
    Evas_Coord width = 0;
    Evas_Coord height = 0;

    evas_object_geometry_get(getHandle(), &x, &y, &width, &height);
    return {x, y, x + width, y + height};
}

CoordSize EvasObj::getSize() const
{
    Evas_Coord width = 0;
    Evas_Coord height = 0;

    evas_object_geometry_get(getHandle(), nullptr, nullptr, &width, &height);
    return {width, height};
}

void EvasObj::move(const CoordPoint point)
{
    evas_object_move(getHandle(), point.x, point.y);
}

void EvasObj::resize(const CoordSize size)
{
    evas_object_resize(getHandle(), size.width, size.height);
}

void EvasObj::setColor(const Color& color)
{
    EFLCPP_ASSERT(color.r >= 0 && color.r <= 255);
    EFLCPP_ASSERT(color.g >= 0 && color.g <= 255);
    EFLCPP_ASSERT(color.b >= 0 && color.b <= 255);
    EFLCPP_ASSERT(color.a >= 0 && color.a <= 255);
    evas_object_color_set(getHandle(), color.r, color.g, color.b, color.a);
}

Color EvasObj::getColor() const
{
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 0;
    evas_object_color_get(getHandle(), &r, &g, &b, &a);
    EFLCPP_ASSERT(r >= 0 && r <= 255);
    EFLCPP_ASSERT(g >= 0 && g <= 255);
    EFLCPP_ASSERT(b >= 0 && b <= 255);
    EFLCPP_ASSERT(a >= 0 && a <= 255);

    return {r, g, b, a};
}

void EvasObj::lower()
{
    evas_object_lower(getHandle());
}

void EvasObj::raise()
{
    evas_object_raise(getHandle());
}

void EvasObj::setLayer(const short layer)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    EFLCPP_ASSERT(layer < EVAS_LAYER_MAX);
    EFLCPP_ASSERT(layer > EVAS_LAYER_MIN);
#pragma GCC diagnostic pop

    evas_object_layer_set(getHandle(), layer);
}

short EvasObj::getLayer() const
{
    return evas_object_layer_get(getHandle());
}

void EvasObj::setHintAlignmentPoint(const AlignmentPoint point)
{
    evas_object_size_hint_align_set(getHandle(), point.x, point.y);
}

void EvasObj::setHintWeightPoint(const WeightPoint point)
{
    evas_object_size_hint_weight_set(getHandle(), point.x, point.y);
}

void EvasObj::setHintPaddingRect(const CoordRect& rect)
{
    evas_object_size_hint_padding_set(getHandle(), rect.left, rect.right, rect.top, rect.bottom);
}

void EvasObj::setHintMinSize(const CoordSize size)
{
    evas_object_size_hint_min_set(getHandle(), size.width, size.height);
}

void EvasObj::setHintMaxSize(const CoordSize size)
{
    evas_object_size_hint_max_set(getHandle(), size.width, size.height);
}

void EvasObj::setHintFixedSize(const CoordSize size)
{
    setHintMinSize(size);
    setHintMaxSize(size);
}

void EvasObj::setHintDisplayMode(const DisplayMode mode)
{
    evas_object_size_hint_display_mode_set(getHandle(), getBimapValueByKey(DisplayModeBimap, mode));
}

void EvasObj::setHintAspectControl(const AspectControl mode, const CoordSize ratio)
{
    evas_object_size_hint_aspect_set(getHandle(), getBimapValueByKey(AspectControlBimap, mode), ratio.width, ratio.height);
}

void EvasObj::setRepeatEvents(const bool enable)
{
    evas_object_repeat_events_set(getHandle(), enable);
}

void EvasObj::setPropagateEvents(const bool enable)
{
    evas_object_propagate_events_set(getHandle(), enable);
}

void EvasObj::setIgnoreEvents(const bool ignore)
{
    evas_object_pass_events_set(getHandle(), ignore);
}

void EvasObj::setData(const char* const key, const void* const data)
{
    EFLCPP_ASSERT(key);
    EFLCPP_ASSERT(data);
    evas_object_data_set(getHandle(), key, data);
}

void* EvasObj::getData(const char* const key) const
{
    EFLCPP_ASSERT(key);
    return evas_object_data_get(getHandle(), key);
}

int EvasObj::getRefCount() const
{
    return evas_object_ref_get(getHandle());
}

void EvasObj::incRefCount()
{
    evas_object_ref(getHandle());
}

void EvasObj::decRefCount()
{
    evas_object_unref(getHandle());
}

void EvasObj::setFocus(const bool focus)
{
    evas_object_focus_set(getHandle(), focus);
}

bool EvasObj::operator==(const EvasObj& obj) const
{
    return getHandle() == obj.getHandle();
}

void EvasObj::delObject(EvasObj* const obj)
{
    EFLCPP_ASSERT(obj);
    evas_object_del(obj->getHandle());
}

void EvasObj::delObject()
{
    EvasObj::delObject(this);
}

bool EvasObj::checkObjects()
{
    EFLCPP_LOG_TRACE << "Checking Evas Objects: created - " << CreatedObjects << " deleted - " << DeletedObjects;
    return CreatedObjects == DeletedObjects;
}

void EvasObj::setEventHandler(const EvasEvent event, EvasEvents::Handler handler)
{
    _evasEventHandler.setEventHandler(*getHandle(), event, std::move(handler));
}

void EvasObj::setKeyEventHandler(const EvasEvent event, EvasEvents::KeyHandler handler)
{
    _evasEventHandler.setKeyEventHandler(*getHandle(), event, std::move(handler));
}

void EvasObj::setMouseEventHandler(const EvasEvent event, EvasEvents::MouseHandler handler)
{
    _evasEventHandler.setMouseEventHandler(*getHandle(), event, std::move(handler));
}

void EvasObj::setSmartEventHandler(const char* event, SmartEvents::Handler handler)
{
    _smartEventHandler.setEventHandler(*getHandle(), event, std::move(handler));
}

} // namespace EflCpp
