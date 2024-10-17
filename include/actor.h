#pragma once

#include <random>
#include <utility>
#include <cassert>
#include "concepts.h"
#include "type_aliases.h"

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

template < typename PolicyType
         , typename ExplorationStrategy >
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

    Actor( PolicyType policy
         , ExplorationStrategy exploration_strategy
         , at::Generator rng
         )
    : policy_( policy )
    , exploration_strategy_( exploration_strategy )
    , rng_( std::move( rng ) ) { }

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
     * @brief Selects an action using an epsilon-greedy strategy.
     * 
     * With probability `epsilon`, this method selects an action randomly. Otherwise, it selects
     * the action that the policy would normally choose.
     * 
     * @param state The current state of the environment.
     * @param epsilon The probability [0, 1] of selecting a random action.
     * @return The selected action.
     */
    
    Action explore( const State& state )
    {
        return exploration_strategy_.explore( state, rng_ );
    }

protected:

    // Protected Members
    PolicyType& policy_;
    at::Generator rng_;
    ExplorationStrategy exploration_strategy_;

};

// Deduction Guide for CTAD
template <typename PolicyType, ExplorationStrategy>
Actor( PolicyType, ExplorationStrategy, at::Generator ) 
     -> Actor< PolicyType, ExplorationStategy >;
