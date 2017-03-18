#include "EflCpp/scrollable.h"

#include "EflCpp/bimap.h"
#include "EflCpp/elementary_inc.h"
#include "EflCpp/elm_obj.h"
#include "EflCpp/scroller.h"

#include <boost/polymorphic_pointer_cast.hpp>

namespace EflCpp
{

namespace
{
static const auto MovementBlockBimap = makeUnorderedBimap<Scrollable::MovementBlock, Elm_Scroller_Movement_Block>(
    {{Scrollable::MovementBlock::None, ELM_SCROLLER_MOVEMENT_NO_BLOCK},
     {Scrollable::MovementBlock::Horizontal, ELM_SCROLLER_MOVEMENT_BLOCK_HORIZONTAL},
     {Scrollable::MovementBlock::Vertical, ELM_SCROLLER_MOVEMENT_BLOCK_VERTICAL},
     {Scrollable::MovementBlock::Both, static_cast<Elm_Scroller_Movement_Block>(ELM_SCROLLER_MOVEMENT_BLOCK_HORIZONTAL | ELM_SCROLLER_MOVEMENT_BLOCK_VERTICAL)}});

static const auto BarVisibilityBimap = makeUnorderedBimap<Scrollable::BarVisibility, Elm_Scroller_Policy>({
    {Scrollable::BarVisibility::Auto, ELM_SCROLLER_POLICY_AUTO}, {Scrollable::BarVisibility::On, ELM_SCROLLER_POLICY_ON}, {Scrollable::BarVisibility::Off, ELM_SCROLLER_POLICY_OFF},
});
}

Scrollable::Scrollable(Evas_Object& obj)
    : _obj(obj)
{
}

void Scrollable::setBlock(MovementBlock block)
{
    elm_scroller_movement_block_set(&_obj, getBimapValueByKey(MovementBlockBimap, block));
}

Scrollable::MovementBlock Scrollable::getBlock() const
{
    return getBimapKeyByValue(MovementBlockBimap, elm_scroller_movement_block_get(&_obj));
}

void Scrollable::setBarVisibility(BarVisibility hPolicy, BarVisibility vPolicy)
{
    elm_scroller_policy_set(&_obj, getBimapValueByKey(BarVisibilityBimap, hPolicy), getBimapValueByKey(BarVisibilityBimap, vPolicy));
}

std::pair<Scrollable::BarVisibility, Scrollable::BarVisibility> Scrollable::getBarVisibility() const
{
    Elm_Scroller_Policy hPolicy = {};
    Elm_Scroller_Policy vPolicy = {};
    elm_scroller_policy_get(&_obj, &hPolicy, &vPolicy);

    return std::make_pair(getBimapKeyByValue(BarVisibilityBimap, hPolicy), getBimapKeyByValue(BarVisibilityBimap, vPolicy));
}

} // namespace EflCpp
