#pragma once

#include "torch/torch.h"
#include "policy.h"
#include "concrete_policies.h"

class PolicyFactory
{
public:
    static auto create_policy( torch::nn::Module nn_module
                             , PolicyTypes policy_enum )
    { 
        return PolicySelector<policy_enum>( nn_module );
    }
    
};
