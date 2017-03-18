#pragma once

#include "EflCpp/application_tasks.h"
#include "EflCpp/elementary_fwd.h"

namespace EflCpp
{

class AppControl;
class Application
{
public:
    virtual int run(int argc, char** argv);
    void stop();

    void addGuiIdleTask(ApplicationTasks::Task task);
    void addSyncTaskForMainLoop(ApplicationTasks::Task task);
    void addAsyncTaskForMainLoop(ApplicationTasks::Task task);

#ifdef EFLCPP_TIZEN
public:
    class EventHandler;
#endif

private:
    virtual bool onCreate() = 0;

#ifdef EFLCPP_TIZEN
    virtual void onPause();
    virtual void onResume();
    virtual void onTerminate();
    virtual void onLowBattery();
    virtual void onLowMemory();
    virtual void onLanguageChanged();
    virtual void onOrientationChanged();
    virtual void onRegionChanged();
    virtual void onAppControl(const AppControl& control);
#endif

private:
    ApplicationTasks _appTasks;
};

} // namespace EflCpp
