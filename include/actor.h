#pragma once

#include <random>
#include <utility>
#include <cassert>
#include "concepts.h"
#include "type_aliases.h"
#include "random_selector.h"

/**
 * @brief The Actor class represents an agent that selects actions in a given environment.
 * 
 * This class uses a specified policy to select actions based on an environment's current 
 * state. It readily offers uniform random action-selection without further specification
 * to enable epsilon-greedy exploration. It additionally houses a random number 
 * generator, which is to be provided by an instance of the RandomEngine class in order 
 * to enable global seeding and reproducibility of results across multiple agents.
 * This class currently does not support multi-dimensional action spaces or action space
 * representations with varying size that vary from state to state.
 * 
 * @tparam PolicyType The type of the policy used to select actions.
 * @tparam StateType The type representing the state of the environment.
 * @tparam ActionType The type representing the action taken by the agent.
 */

template < typename PolicyType >

class Actor
{
public:
    
    // Public constructors

    /**
     * @brief Constructor for discrete action spaces.
     * 
     * Initializes the Actor with the given policy and random number generator (RNG).
     * This constructor should be used when the environment of interest provides only
     * a discrete set of actions to choose from.
     * 
     * @param policy The policy used by the actor to select actions.
     * @param rng The random number generator used for stochastic action selection.
     */

    Actor( PolicyType policy, at::Generator rng )
    : policy_( policy ), rng_( std::move( rng ) ), rand_dist( 0.0, 1.0 )

    // Public APIs

    /**
     * @brief Selects an action based on the current policy.
     * 
     * Uses the policy's `sample` method to select an action given the current state.
     * 
     * @param state The current state of the environment.
     * @return The action selected by the policy.
     */
    
    Action select_action( const State& state )
    {
        return policy_.sample( state, rng_ );
    }

    /**
     * @brief Selects an action randomly, either from a discrete or continuous distribution.
     * 
     * This method selects an action uniformly at random, either from a discrete set of actions
     * or from a continuous range, depending on the action type.
     * 
     * @param state The current state of the environment.
     * @return A randomly selected action.
     */
    
    Action select_random( const State& state )
    {
        static auto actions = policy_.get_action_space();
        return select_random_action( actions, rng_ );
    }

    /**
     * @brief Selects an action using an epsilon-greedy strategy.
     * 
     * With probability `epsilon`, this method selects an action randomly. Otherwise, it selects
     * the action that the policy would normally choose.
     * 
     * @param state The current state of the environment.
     * @param epsilon The probability [0, 1] of selecting a random action.
     * @return The selected action.
     */
    
    Action explore( const State& state, float epsilon)
    { 
        if ( random() < epsilon )
            return select_random( );

        else
            return select_action( state );
    }

protected:

    // Protected Members
    PolicyType& policy_;
    at::Generator rng_;

    // Protected APIs

    /**
     * @brief Generates a random floating-point number between 0.0 and 1.0.
     * 
     * This method uses the uniform distribution initialized in the constructor to
     * return a random floating-point number between 0.0 and 1.0. This method is 
     * called internally to support the epsilon-greedy exploration.
     * 
     * @return float A random number between 0.0 and 1.0.
     */

    float random() { return torch::rand( { 1 }, rng_ ).item<float>( ); }

};
