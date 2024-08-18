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
    
    // Public Constructors
    Actor( PolicyType policy, std::mt19937 rng )
    : policy_( policy )
    , rng_( std::move( rng ) )
    , rand_dist( 0.0, 1.0 ) 
    {
        static_assert( !ContinuousAction<ActionType>
                     , "Continuous Action Space requires the specification of an exploration window");
    };

    Actor( PolicyType policy
         , std::mt19937 rng
         , std::pair<float, float> exploration_window )
    : policy_( policy )
    , rng_( std::move( rng ) )
    , rand_dist( 0.0, 1.0 ) 
    {
        assert( exploration_window[ 0 ] < exploration_window[ 1 ]
              && "Min value must be less than max value" );
    };
 
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
    std::pair<float, float> exploration_window_{ 0.0, 0.0 };
    

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

    ActionType select_random_discrete()
    { 
        static std::uniform_int_distribution<> rand_action_dist( 0, policy_.n_actions );
        return rand_action_dist( rng_ );
    }

    ActionType select_random_continuous( const StateType& ) const
    { 
        static std::uniform_real_distribution<> rand_action_dist( exploration_window_[ 0 ]
                                                                , exploration_window_[ 1 ] );
        return rand_action_dist( rng_ );
    }


