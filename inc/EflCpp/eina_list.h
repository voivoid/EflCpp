#pragma once

#include "EflCpp/elementary_inc.h"

#include <vector>

namespace EflCpp
{

template <typename VectorElem, typename EinaListElem = VectorElem>
std::vector<VectorElem> createVectorFromEinaList(const Eina_List* list)
{
    if (!list)
    {
        return {};
    }

    std::vector<VectorElem> vec;

    const auto size = eina_list_count(list);
    vec.reserve(size);

    void* elem = nullptr;
    const Eina_List* l = nullptr;
    EINA_LIST_FOREACH(list, l, elem)
    {
        vec.emplace_back(static_cast<EinaListElem>(elem));
    }

    return vec;
}

template <typename T>
Eina_List* createEinaListFromVector(const std::vector<T>&)
{
    return nullptr;
}

} // namespace EflCpp
