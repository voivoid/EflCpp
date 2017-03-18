#pragma once

#include <boost/optional.hpp>

namespace EflCpp
{
namespace Preferences
{
namespace Details
{
}

template <typename T>
void set(const char* key, const T& value);

template <typename T>
boost::optional<T> get(const char* key);

void remove(const char* key);

} // namespace Preferences
} // namespace EflCpp
