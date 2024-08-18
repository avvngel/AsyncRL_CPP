#include <random>
#include "policy.h"
#include "TestApproximators.h"
#include "type_aliases.h"

class SimplePolicy : public Policy<SimplePolicy, SimpleApprox, State, DiscAction>
{ 
public:
    
    using Policy::Policy;

    // Public APIs
    DiscAction sample( State& state, std::mt19937 rng ) const
    { 
        
    }
    
}
