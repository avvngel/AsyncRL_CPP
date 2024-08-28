#include <random>
#include "policy.h"
#include "TestApproximators.h"
#include "type_aliases.h"

/** 
 * @file TestPolicies.h
 * @brief Simple implementations of Policy for testing and debugging.
 */

/**
 * @class SimplePolicy
 * @brief Example Policy implementation that employs the SimpleApprox to return a discrete action
*/

class SimplePolicy : public Policy<SimplePolicy, SimpleApprox, DiscState, DiscAction>
{ 
public:
    
    using Policy<SimplePolicy, SimpleApprox, DiscState, DiscAction>::Policy;

    // Public APIs
    DiscAction sample( const DiscState& state, std::mt19937& rng )
    { 
        DiscActionDist weights{ dist_approx_.predict( state ) };
        std::discrete_distribution<> action_dist( weights.begin(), weights.end() );
        return action_dist( rng );
    }
    
    DiscAction get_expected_action()
    { 
        return dist_approx_.get_expected_action();
    }
};
