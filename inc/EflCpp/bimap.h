#pragma once

#include "EflCpp/assert.h"

#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

namespace EflCpp
{

template <typename Key, typename Value>
using BiMap = boost::bimap<boost::bimaps::unordered_set_of<Key>, boost::bimaps::unordered_set_of<Value>>;

template <typename Key, typename Value>
BiMap<Key, Value> makeUnorderedBimap(const std::initializer_list<typename BiMap<Key, Value>::value_type>& list)
{
    return BiMap<Key, Value>(std::begin(list), std::end(list));
}

template <typename Key, typename Value>
Value getBimapValueByKey(const BiMap<Key, Value>& bimap, const Key key)
{
    auto iter = bimap.left.find(key);
    if (iter == bimap.left.end())
    {
        EFLCPP_FAIL_WITH_MESSAGE("Bimap key not found");
    }

    return iter->second;
}

template <typename Key, typename Value>
Key getBimapKeyByValue(const BiMap<Key, Value>& bimap, const Value value)
{
    auto iter = bimap.right.find(value);
    if (iter == bimap.right.end())
    {
        EFLCPP_FAIL_WITH_MESSAGE("Bimap value not found");
    }

    return iter->second;
}

} // namespace EflCpp
