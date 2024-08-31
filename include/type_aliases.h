#pragma once

#include <cstdint>
#include "torch/torch.h"

using DiscState = int;
using DiscStates = std::vector<DiscState>;
using DiscAction = int;
using DiscActions = std::vector<DiscAction>;
using DiscActionDist = std::vector<float>;
using Parameter = float;
using Parameters = std::vector<Parameter>;
using Sizes = std::vector<std::size_t>

