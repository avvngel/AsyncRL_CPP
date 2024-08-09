#pragma once

#include "actor.h"

template <typename FunctionApproximator,
          typename StateType,
          typename ActionType>
class DiscreteActor : public Actor< DiscreteActor< FunctionApproximator
                                                 , StateType
                                                 , ActionType >
                                  , FunctionApproximator
                                  , StateType
                                  , ActionType >
{
public:
    // Public Constructor
    using Actor<DiscreteActor, FunctionApproximator, StateType, ActionType>::Actor;
    
    // Public APIs

    ActionType select_action( const StateType& state ) const
    { 
        // Get discrete probability distribution from approximator
        std::vector<float> probabilities{ this->action_dist_approx_.predict( state ) };

        // Get discrete distribution based on probabilities
        std::discrete_distribution<> action_dist( probabilities.begin() 
                                                , probabilities.end() );
        // Sample from distribution
        return action_dist( rng_ );
    }

    ActionType select_random( const StateType& state ) const
    {
        // Get discrete probability distribution from approximator
        std::vector<float> probabilities{ action_dist_approx_.predict( state ) };

        // Get uniform random probability distribution depending on the number of actions
        std::vector<float> uniform_probs( probabilities.size()
                                        , 1.0f/probabilities.size() );
        // Get uniform discrete distribution
        std::discrete_distribution<> action_dist( uniform_probs.begin(), uniform_probs.end() );
        
        // Return random sample
        return action_dist( rng_ );
    }
};
