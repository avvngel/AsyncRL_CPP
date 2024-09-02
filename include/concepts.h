#pragma once

#include <type_traits>
#include "torch/torch.h"
#include "action_space.h"

template <typename T>
concept DiscreteAS = std::is_same_v<T, DiscreteUniformActionSpace> 
                  || std::is_same_v<T, DiscreteVariableActionSpace>;

template <typename T>
concept ContinuousAS = std::is_same_v<T, ContinuousUniformActionSpace>
                    || std::is_same_v<T, ContinuousVariableActionSpace>;

template <typename T>
concept IsActionSpace = DiscreteAS<T> || ContinuousAS<T>;

template <typename T>
concept HasSize = requires( T t )
                { 
                    { t.size() } -> std::convertible_to<std::size_t>;
                };






