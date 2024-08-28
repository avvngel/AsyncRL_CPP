#pragma once

#include <random>
#include <utility>
#include <cassert>
#include "concepts.h"

template < typename PolicyType
         , typename StateType
         , typename ActionType >

requires DiscreteAction<ActionType> || ContinuousAction<ActionType>
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
        assert( exploration_window.first < exploration_window.second
              && "Min value must be less than max value" );
    };
 
    // Public APIs
    
    ActionType select_action( const StateType& state )
    {
        return policy_.sample( state, rng_ );
    }
    
    ActionType select_random( const StateType& state )
    {

        if constexpr ( DiscreteAction<ActionType> )
            return select_random_discrete( state );
        else
            return select_random_continuous();
    }

    ActionType explore( const StateType& state, float epsilon)
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

private:

    ActionType select_random_discrete( const StateType& state)
    { 
        static std::uniform_int_distribution<> rand_action_dist( 0, policy_.get_n_actions( state ) );
        return rand_action_dist( rng_ );
    }

    ActionType select_random_continuous()
    { 
        static std::uniform_real_distribution<> rand_action_dist( exploration_window_.first
                                                                , exploration_window_.second );
        return rand_action_dist( rng_ );
    }

};
