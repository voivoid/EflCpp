#include "EflCpp/application_tasks.h"

#include "EflCpp/assert.h"
#include "EflCpp/log.h"
#include "EflCpp/safe_callback.h"
#include "EflCpp/thread.h"

#include <mutex>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
namespace
{
std::mutex AsyncTasksMutex;

Eina_Bool idleTaskHandler(void* const data)
{
    EFLCPP_ASSERT(data);

    ApplicationTasks::Tasks& idleTasks = *reinterpret_cast<ApplicationTasks::Tasks*>(data);

    if (idleTasks.empty())
    {
        return ECORE_CALLBACK_CANCEL;
    }

    auto task = std::move(idleTasks.front());
    idleTasks.pop();
    EFLCPP_LOG_TRACE << "Executing idle task handler...";
    task();
    EFLCPP_LOG_TRACE << "Executing idle task handler done.";

    return idleTasks.empty() ? ECORE_CALLBACK_CANCEL : ECORE_CALLBACK_RENEW;
}

void* syncTaskHandler(void* const data)
{
    EFLCPP_ASSERT(data);

    ApplicationTasks::Task& task = *reinterpret_cast<ApplicationTasks::Task*>(data);

    EFLCPP_LOG_TRACE << "Executing sync task handler...";
    task();
    EFLCPP_LOG_TRACE << "Executing sync task handler done";

    return nullptr;
}

void asyncTaskHandler(void* const data)
{
    EFLCPP_ASSERT(data);
    ApplicationTasks::Tasks& asyncTasks = *reinterpret_cast<ApplicationTasks::Tasks*>(data);
    ApplicationTasks::Task task;

    {
        std::unique_lock<std::mutex> lock(AsyncTasksMutex);
        if (asyncTasks.empty())
        {
            return;
        }

        task = std::move(asyncTasks.front());
        asyncTasks.pop();
    }

    EFLCPP_LOG_TRACE << "Executing async task handler...";
    task();
    EFLCPP_LOG_TRACE << "Executing async task handler done.";
}
} // namespace anonymous

void ApplicationTasks::addIdleTask(Task task)
{
    EFLCPP_ASSERT(isGuiThread());

    const bool firstTask = _idleTasks.empty();
    _idleTasks.push(std::move(task));

    if (firstTask)
    {
        ecore_idler_add(EFLCPP_WRAP_INTO_SAFE_CALLBACK(idleTaskHandler), &_idleTasks);
    }
}

void ApplicationTasks::addSyncTaskForMainLoop(Task task)
{
    EFLCPP_ASSERT(!isGuiThread());
    ecore_main_loop_thread_safe_call_sync(EFLCPP_WRAP_INTO_SAFE_CALLBACK(syncTaskHandler), &task);
}

void ApplicationTasks::addAsyncTaskForMainLoop(Task task)
{
    EFLCPP_ASSERT(!isGuiThread());

    {
        std::unique_lock<std::mutex> lock(AsyncTasksMutex);
        _asyncTasks.push(std::move(task));
    }

    ecore_main_loop_thread_safe_call_async(EFLCPP_WRAP_INTO_SAFE_CALLBACK(asyncTaskHandler), &_asyncTasks);
}

void ApplicationTasks::forceProcessPendingTasks()
{
    EFLCPP_ASSERT(isGuiThread());

    EFLCPP_LOG_INFO << "Forcing pending idle tasks execution...";
    while (!_idleTasks.empty())
    {
        auto task = std::move(_idleTasks.front());
        _idleTasks.pop();
        EFLCPP_LOG_TRACE << "Forcing idle task handler...";
        task();
        EFLCPP_LOG_TRACE << "Forcing idle task handler done.";
    }

    EFLCPP_LOG_INFO << "Forcing pending async tasks execution...";
    ApplicationTasks::Tasks asyncTasks;
    {
        std::unique_lock<std::mutex> lock(AsyncTasksMutex);
        asyncTasks = std::move(_asyncTasks);
    }
    while (!asyncTasks.empty())
    {
        auto task = std::move(asyncTasks.front());
        asyncTasks.pop();
        EFLCPP_LOG_TRACE << "Forcing async task handler...";
        task();
        EFLCPP_LOG_TRACE << "Forcing async task handler done.";
    }

    EFLCPP_LOG_INFO << "Pending tasks processed";
}

} // namespace EflCpp
