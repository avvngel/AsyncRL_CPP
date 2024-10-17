#pragma once

#include <tuple>
#include "torch/torch.h"

template < typename ActorAllocStrategy
         , typename EnvAllocStrategy
         , typename EnvArg
         , bool EnableLogging >

class SetupManager
{
    void pre_thread_setup( ){  }; // Need to decide what to do here
    
    auto create_thread_resources( torch::nn::Module nn_module
                                , PolicyTypes policy_enum
                                , EnvArg env )
    {
        auto actor = ActorAllocStrategy::create_actor( 
            nn_module, PolicyFactory::create_policy<policy_enum>( nn_module ) 
            );
        auto env = EnvAllocStrategy::create_env( env_arg );
        return std::make_tuple( actor, env );
    }
    
    auto create_thread_resources( UnknownPolicyType policy, EnvArg env )
};
