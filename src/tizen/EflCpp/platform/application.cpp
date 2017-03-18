#include "EflCpp/application.h"

#include "EflCpp/elementary_inc.h"
#include "EflCpp/log.h"
#include "EflCpp/platform/app_control.h"

#include <app.h>

namespace EflCpp
{

class Application::EventHandler
{
public:
    static bool appCreate(void* data)
    {
        return reinterpret_cast<Application*>(data)->onCreate();
    }

    static void appTerminate(void* const data)
    {
        return reinterpret_cast<Application*>(data)->onTerminate();
    }

    static void appControl(app_control_h ctrl, void* data)
    {
        return reinterpret_cast<Application*>(data)->onAppControl(AppControl(ctrl));
    }

    static void appPause(void* const data)
    {
        return reinterpret_cast<Application*>(data)->onPause();
    }

    static void appResume(void* const data)
    {
        return reinterpret_cast<Application*>(data)->onResume();
    }

    static void appLangChanged(app_event_info_h, void* const data)
    {
        return reinterpret_cast<Application*>(data)->onLanguageChanged();
    }

    static void appOrientChanged(app_event_info_h, void* const data)
    {
        return reinterpret_cast<Application*>(data)->onOrientationChanged();
    }

    static void appRegionChanged(app_event_info_h, void* const data)
    {
        return reinterpret_cast<Application*>(data)->onRegionChanged();
    }

    static void appLowBattery(app_event_info_h, void* const data)
    {
        return reinterpret_cast<Application*>(data)->onLowBattery();
    }

    static void appLowMemory(app_event_info_h, void* const data)
    {
        return reinterpret_cast<Application*>(data)->onLowMemory();
    }
};

int Application::run(int argc, char** argv)
{
    ui_app_lifecycle_callback_s event_callback;
    event_callback.app_control = &Application::EventHandler::appControl;
    event_callback.create = &Application::EventHandler::appCreate;
    event_callback.pause = &Application::EventHandler::appPause;
    event_callback.resume = &Application::EventHandler::appResume;
    event_callback.terminate = &Application::EventHandler::appTerminate;

    app_event_handler_h handlers[5] = {};

    ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, Application::EventHandler::appLowBattery, this);
    ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, Application::EventHandler::appLowMemory, this);
    ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, Application::EventHandler::appOrientChanged, this);
    ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, Application::EventHandler::appLangChanged, this);
    ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, Application::EventHandler::appRegionChanged, this);

    return ui_app_main(argc, argv, &event_callback, this);
}

void Application::stop()
{
    ui_app_exit();
}

void Application::onPause()
{
    EFLCPP_LOG_INFO << "Pause event";
}

void Application::onResume()
{
    EFLCPP_LOG_INFO << "Resume event";
}

void Application::onTerminate()
{
    EFLCPP_LOG_INFO << "Terminate event";
}

void Application::onLowBattery()
{
    EFLCPP_LOG_WARN << "Low battery event";
}

void Application::onLowMemory()
{
    EFLCPP_LOG_WARN << "Low memory event";
}

void Application::onLanguageChanged()
{
    EFLCPP_LOG_INFO << "Language changed event";
}

void Application::onOrientationChanged()
{
    EFLCPP_LOG_INFO << "Orientation changed event";
}

void Application::onRegionChanged()
{
    EFLCPP_LOG_INFO << "Region changed event";
}

void Application::onAppControl(const AppControl& /*control*/)
{
    EFLCPP_LOG_INFO << "AppControl event";
}

} // namespace EflCpp
