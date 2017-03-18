#include "EflCpp/application.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

int Application::run(const int argc, char** const argv)
{
    elm_init(argc, argv);
    const bool created = onCreate();
    if (created)
    {
        elm_run();
    }

    return elm_shutdown();
}

void Application::stop()
{
    elm_exit();
}

void Application::addGuiIdleTask(ApplicationTasks::Task task)
{
    _appTasks.addIdleTask(std::move(task));
}

void Application::addSyncTaskForMainLoop(ApplicationTasks::Task task)
{
    _appTasks.addSyncTaskForMainLoop(std::move(task));
}

void Application::addAsyncTaskForMainLoop(ApplicationTasks::Task task)
{
    _appTasks.addAsyncTaskForMainLoop(std::move(task));
}

} // namespace EflCpp
