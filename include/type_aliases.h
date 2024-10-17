#pragma once

#include <cstdint>
#include <tuple>
#include <optional>
#include <thread>
#include "torch/torch.h"


using Reward = float;
using State = at::Tensor;
using Action = at::Tensor;
using DiscAction = int;
using DiscActions = std::vector<DiscAction>;
using DiscActionDist = std::vector<float>;
using Parameter = float;
using Parameters = std::vector<Parameter>;
using Sizes = std::vector<std::size_t>;
using Threads = std::vector<std::thread>

template < typename ActionSpace
         , typename Info >
using EnvTimeStep = std::tuple< State
                              , Reward
                              , bool // terminated flag
                              , bool // truncated flag
                              , std::optional<ActionSpace>
                              , std::optional<Info> >;

