#pragma once

#include "EflCpp/elementary_fwd.h"
#include "EflCpp/events/evas_events.h"
#include "EflCpp/events/smart_events.h"
#include "EflCpp/geo.h"
#include "EflCpp/log.h"
#include "EflCpp/macros.h"

#include <boost/current_function.hpp>
#include <boost/scope_exit.hpp>

#include <memory>

namespace EflCpp
{

constexpr double HintExpand = 1.f;
constexpr double HintFill = -1.f;

class EvasObj : public std::enable_shared_from_this<EvasObj>
{
public:
    class Access
    {
    private:
        static Evas_Object* getHandle(EvasObj& w);
        static const Evas_Object* getHandle(const EvasObj& w);

        friend class Canvas;
    };

public:
    virtual ~EvasObj();

    DISABLE_COPY_MOVE_SEMANTICS(EvasObj)

    bool operator==(const EvasObj& obj) const;

    static EvasObj& getRef(Evas_Object& obj);
    static EvasObj* getPtr(Evas_Object& obj);

    void show();
    void hide();
    bool isVisible() const;

    CoordRect getGeometry() const;
    CoordSize getSize() const;

    void move(CoordPoint point);
    void resize(CoordSize size);

    void setFocus(bool focus = true);

    void setColor(const Color& color);
    Color getColor() const;

    void lower();
    void raise();
    void setLayer(short layer);
    short getLayer() const;

    using AlignmentPoint = Details::Point2D<double>;
    using WeightPoint = Details::Point2D<double>;

    void setHintMinSize(CoordSize size);
    void setHintMaxSize(CoordSize size);
    void setHintFixedSize(CoordSize size);
    void setHintAlignmentPoint(AlignmentPoint point);
    void setHintWeightPoint(WeightPoint point);
    void setHintPaddingRect(const CoordRect& rect);

    enum class DisplayMode
    {
        Default,
        Compress,
        Expand,
        DontChange
    };
    void setHintDisplayMode(DisplayMode);

    enum class AspectControl
    {
        Default,
        Neither,
        Horizontal,
        Vertical,
        Both
    };
    void setHintAspectControl(AspectControl, CoordSize ratio);

    void setRepeatEvents(bool enable = true);
    void setPropagateEvents(bool enable = true);
    void setIgnoreEvents(bool ignore = true);

    int getRefCount() const;
    void incRefCount();
    void decRefCount();

    struct Deleter
    {
        void operator()(EvasObj* obj) const
        {
            delObject(obj);
            obj->decRefCount();
        }
    };

    static bool checkObjects();

    void setEventHandler(EvasEvent event, EvasEvents::Handler handler);
    void setKeyEventHandler(EvasEvent event, EvasEvents::KeyHandler handler);
    void setMouseEventHandler(EvasEvent event, EvasEvents::MouseHandler handler);

    void setSmartEventHandler(const char* event, SmartEvents::Handler handler);

    void delObject();

    static constexpr const char* EventDeleteRequest = "delete,request";
    static constexpr const char* EventClicked = "clicked";

    const char* getObjId() const
    {
        return _objId;
    }

protected:
    EvasObj(Evas_Object* obj, const char* const objId);

    Evas_Object* getHandle();
    const Evas_Object* getHandle() const;
    static Evas_Object* getHandle(EvasObj& w);
    static const Evas_Object* getHandle(const EvasObj& w);

    void setData(const char* key, const void* data);
    void* getData(const char* key) const;

private:
    static void delObject(EvasObj*);

private:
    Evas_Object* _obj;
    EvasEvents _evasEventHandler;
    SmartEvents _smartEventHandler;
    const char* _objId;
};

template <typename T>
using WidgetPtr = std::shared_ptr<T>;

template <typename T>
using UniqueWidgetPtr = std::unique_ptr<T, EvasObj::Deleter>;

#define EFLCPP_DECL_EFL_WIDGET(widget)                                                                 \
    template <typename... Args>                                                                        \
    static EflCpp::WidgetPtr<widget> create(Args&&... args)                                            \
    {                                                                                                  \
        return EflCpp::WidgetPtr<widget>{new widget(std::forward<Args>(args)...), EvasObj::Deleter{}}; \
    }                                                                                                  \
    template <typename... Args>                                                                        \
    static EflCpp::UniqueWidgetPtr<widget> createUnique(Args&&... args)                                \
    {                                                                                                  \
        return EflCpp::UniqueWidgetPtr<widget>{new widget(std::forward<Args>(args)...)};               \
    }

template <typename T>
T& releaseWidgetPtr(UniqueWidgetPtr<T>&& ptr)
{
    ptr->decRefCount();
    return *ptr.release();
}

#define EFLCPP_LOG_OBJECT_METHOD LOG_CURRENT_SCOPE(getObjId(), BOOST_CURRENT_FUNCTION)

} // namespace EflCpp
