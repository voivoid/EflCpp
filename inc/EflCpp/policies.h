#pragma once

namespace EflCpp
{

namespace Policies
{

enum class AutoQuit
{
    NoAutoQuit,
    OnLastWindowClosed
};

enum class OnExit
{
    DoNothing,
    DeleteWindows
};

enum class Throttle
{
    Config,
    Always,
    Never
};

enum class Acceleration
{
    OpenGl,
    ThreeD,
    Hardware
};

void set(Policies::AutoQuit policy);
void set(Policies::OnExit policy);
void set(Policies::Throttle policy);
void set(Policies::Acceleration policy);

template <typename T>
T get();

} // namespace Policies
} // namespace EflCpp
