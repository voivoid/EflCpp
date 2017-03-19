#include "EflCpp/policies.h"

#include "EflCpp/assert.h"
#include "EflCpp/bimap.h"

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{
namespace Policies
{

namespace
{

static const auto AutoQuitBimap = makeUnorderedBimap<AutoQuit, Elm_Policy_Quit>(
    {{Policies::AutoQuit::NoAutoQuit, ELM_POLICY_QUIT_NONE}, {Policies::AutoQuit::OnLastWindowClosed, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED}});

static const auto OnExitBimap =
    makeUnorderedBimap<OnExit, Elm_Policy_Exit>({{Policies::OnExit::DoNothing, ELM_POLICY_EXIT_NONE}, {Policies::OnExit::DeleteWindows, ELM_POLICY_EXIT_WINDOWS_DEL}});

static const auto ThrottleBimap = makeUnorderedBimap<Throttle, Elm_Policy_Throttle>({{Policies::Throttle::Config, ELM_POLICY_THROTTLE_CONFIG},
                                                                                     {Policies::Throttle::Always, ELM_POLICY_THROTTLE_HIDDEN_ALWAYS},
                                                                                     {Policies::Throttle::Never, ELM_POLICY_THROTTLE_NEVER}});

static const auto AccelarationBimap = makeUnorderedBimap<Acceleration, const char*>(
    {{Policies::Acceleration::Hardware, "hardware"}, {Policies::Acceleration::OpenGl, "opengl"}, {Policies::Acceleration::ThreeD, "3d"}});
}

void set(const Policies::AutoQuit policy)
{
    elm_policy_set(ELM_POLICY_QUIT, getBimapValueByKey(AutoQuitBimap, policy));
}

void set(const Policies::OnExit policy)
{
    elm_policy_set(ELM_POLICY_EXIT, getBimapValueByKey(OnExitBimap, policy));
}

void set(const Policies::Throttle policy)
{
    elm_policy_set(ELM_POLICY_THROTTLE, getBimapValueByKey(ThrottleBimap, policy));
}

void set(Policies::Acceleration policy)
{
    elm_config_accel_preference_set(getBimapValueByKey(AccelarationBimap, policy));
}

} // namespace Policies
} // namespace EflCpp
