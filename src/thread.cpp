#include "EflCpp/thread.h"

#include <thread>

namespace EflCpp
{
namespace
{
static const auto GuiThreadId = std::this_thread::get_id();
}

bool isGuiThread()
{
    return GuiThreadId == std::this_thread::get_id();
}
} // namespace EflCpp
