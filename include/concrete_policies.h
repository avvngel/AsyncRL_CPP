#pragma once

#include "torch/torch.h"
#include "policy.h"
#include "type_aliases.h"

class DirectActionPolicy : public Policy<DirectActionPolicy>
{ 
public:

    // Public Constructor
    using Policy<DirectActionPolicy>::Policy;
    
    // Public APIs
    Action sample( const State& state, at::Generator& rng ){ 
        void( rng ); // Silence warning but maintain common interface
        return dist_approx_( state );
    }
};

class SoftmaxPolicy : public Policy<SoftmaxPolicy>
{ 
public:
    
    // Public Constructor
    using Policy<SoftmaxPolicy>::Policy;

    // Public APIs
    Action sample( const State& state, at::Generator& rng ){ 
        // Implement this later
}
};

class GaussianPolicy : public Policy<GaussianPolicy>
{ 
public:
    
    // Public Constructor
    using Policy<GaussianPolicy>::Policy;
    
    // Public APIs
    Action sample( const State& state, at::Generator& rng ){ 
        // Implement this later
}
};

enum class PolicyTypes
{
    Custom, 
    DirectActionPolicy,
    SoftmaxPolicy,
    GaussianPolicy
};

template <PolicyEnum
struct PolicySelector
