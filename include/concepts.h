#pragma once

#include <type_traits>

template <typename T>
concept DiscreteAction = std::is_integral_v<T>;

template <typename T>
concept ContinuousAction = std::is_floating_point_v<T>;

template <typename T>
concept HasSize = requires( T t )
                { 
                    { t.size() } -> std::convertible_to<std::size_t>;
                };






