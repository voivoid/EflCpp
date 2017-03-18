#pragma once

#include "EflCpp/elementary_inc.h"

#include <vector>

namespace EflCpp
{

template <typename T>
std::vector<T> createVectorFromEinaList(const Eina_List& list)
{
    std::vector<T> vec;

    const auto size = eina_list_count(&list);
    vec.reserve(size);

    void* elem = nullptr;
    const Eina_List* l = nullptr;
    EINA_LIST_FOREACH(&list, l, elem)
    {
        vec.push_back(static_cast<T>(elem));
    }

    return vec;
}

template <typename T>
Eina_List* createEinaListFromVector(const std::vector<T>&)
{
    return nullptr;
}

} // namespace EflCpp
