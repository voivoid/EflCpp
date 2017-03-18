#pragma once

#include "EflCpp/evas_obj.h"
#include "exception.h"

namespace EflCpp
{

class Window;
class ElmObj : public EvasObj
{
public:
    ~ElmObj();

    void setStyle(const char* style);
    const char* getStyle() const;

    void allowFocus(bool allow = true);
    void setFocus(bool focus = true);

    std::string getText() const;
    void setText(const char* text);

    void disable(bool disabled = true);
    bool isDisabled() const;

    Window& getWindow() const;

protected:
    template <typename... Args>
    ElmObj(const char* objId, ElmObj* parent, Evas_Object* (*factory)(Evas_Object*, Args...), Args... args)
        : EvasObj(createEvasObject(objId, parent, factory, args...), objId)
    {
        assertWidgetIsValid();
    }

private:
    template <typename... Args>
    static Evas_Object* createEvasObject(const char* objId, ElmObj* parent, Evas_Object* (*factory)(Evas_Object*, Args...), Args... args)
    {
        Evas_Object* obj = factory(parent ? parent->getHandle() : nullptr, args...);
        if (!obj)
        {
            throw EflException{"Failed to create evas object %1%", objId};
        }

        return obj;
    }

    void assertWidgetIsValid() const;

private:
};

} // namespace EflCpp
