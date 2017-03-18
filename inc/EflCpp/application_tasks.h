#pragma once

#include <functional>
#include <memory>
#include <queue>

namespace EflCpp
{
class ApplicationTasks
{
public:
    using Task = std::function<void()>;
    using Tasks = std::queue<Task>;
    void addIdleTask(Task task);

    void addSyncTaskForMainLoop(Task task);
    void addAsyncTaskForMainLoop(Task task);

    void forceProcessPendingTasks();

private:
    Tasks _idleTasks;
    Tasks _asyncTasks;
};

} // namespace EflCpp
