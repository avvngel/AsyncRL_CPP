#pragma once

#include <type_traits>

template <typename T>
concept DiscreteAction = std::is_integral_v<T>;

template <typename T>
concept ContinuousAction = std::is_floating_point_v<T>;

