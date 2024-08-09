#pragma once

#include <random>
#include <utility>
#include "concepts.h"

template < typename PolicyType
         , typename StateType
         , typename ActionType >

requires DiscreteAction ActionType || ContinuousAction ActionType
class Actor
{ 
public:
    
    // Public Constructor
    Actor( PolicyType policy, std::mt19937 rng )
    : policy_( policy ) 
    , rng_( std::move( rng ) )
    , rand_dist( 0.0, 1.0 ) {};
    
    // Public APIs
    
    ActionType select_action( const StateType& state ) const
    {
        return policy_.sample( state );
    }
    
    ActionType select_random( const StateType& state ) const
    { 
        if constexpr ( DiscreteAction<ActionType> )
            return select_random_discrete( state );
        else
            return select_random_continuous( state );
    }

    ActionType explore( const StateType& state, float epsilon) const
    { 
        if ( random() < epsilon )
            return select_random( state );

        else
            return select_action( state );
    }

protected:

    // Private Members
    PolicyType& policy_;
    std::mt19937 rng_;
    std::uniform_real_distribution<> rand_dist;
    

    /**
     * @brief Generates a random floating-point number between 0.0 and 1.0.
     * 
     * This method uses the uniform distribution initialized in the constructor.
     * 
     * @return float A random number between 0.0 and 1.0.
     */    

    // Private APIs
    float random() { return rand_dist( rng_ ); }
};

private:

    ActionType select_random_discrete( const StateType& ) const
    { 
        //
    }

    ActionType select_random_continuous( const StateType& ) const
    { 
        //
    }


