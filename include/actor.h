#pragma once

#include <random>
#include <utility>
#include <cassert>
#include "concepts.h"

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
         , typename StateType
         , typename ActionType >

requires DiscreteAction<ActionType> || ContinuousAction<ActionType>
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

    Actor( PolicyType policy, std::mt19937 rng )
    : policy_( policy ), rng_( std::move( rng ) ), rand_dist( 0.0, 1.0 )
    {
        static_assert( !ContinuousAction<ActionType>
                     , "Continuous Action Space requires the specification of an exploration window");
    };

    /**
     * @brief Constructor for continuous action spaces.
     * 
     * Initializes the Actor with the given policy, random number generator, and 
     * exploration window. This constructor should be used when the environment of
     * interest provides a continuous interval of actions to choose from.
     * 
     * @param policy The policy used by the actor to select actions.
     * @param rng The random number generator used for stochastic action selection.
     * @param exploration_window A pair of floats specifying the minimum and maximum bounds for exploration.
     */

    Actor( PolicyType policy
         , std::mt19937 rng
         , std::pair<float, float> exploration_window )
    : policy_( policy ), rng_( std::move( rng ) ), rand_dist( 0.0, 1.0 )
    {
        assert( exploration_window.first < exploration_window.second
              && "Min value must be less than max value" );
    };
 
    // Public APIs

    /**
     * @brief Selects an action based on the current policy.
     * 
     * Uses the policy's `sample` method to select an action given the current state.
     * 
     * @param state The current state of the environment.
     * @return The action selected by the policy.
     */
    
    ActionType select_action( const StateType& state )
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
    
    ActionType select_random( const StateType& state )
    {

        if constexpr ( DiscreteAction<ActionType> )
            return select_random_discrete( state );
        else
            return select_random_continuous();
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
    
    ActionType explore( const StateType& state, float epsilon)
    { 
        if ( random() < epsilon )
            return select_random( state );

        else
            return select_action( state );
    }

protected:

    // Protected Members
    PolicyType& policy_;
    std::mt19937 rng_;
    std::uniform_real_distribution<> rand_dist;
    std::pair<float, float> exploration_window_{ 0.0, 0.0 };
    

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

    float random() { return rand_dist( rng_ ); }

private:

    /**
     * @brief Selects a random action from a discrete set of actions.
     * 
     * This method assumes that the action space is discrete and returns a random action
     * based on a uniform distribution over the available actions.
     * 
     * @param state The current state of the environment.
     * @return A randomly selected discrete action.
     */

    ActionType select_random_discrete( const StateType& state)
    { 
        static std::uniform_int_distribution<> rand_action_dist( 0, policy_.get_n_actions( state ) );
        return rand_action_dist( rng_ );
    }

    /**
     * @brief Selects a random action from a continuous range.
     * 
     * This method assumes that the action space is continuous and returns a random action
     * within the exploration window specified in the continuous constructor.
     * 
     * @return A randomly selected continuous action.
     */

    ActionType select_random_continuous()
    { 
        static std::uniform_real_distribution<> rand_action_dist( exploration_window_.first
                                                                , exploration_window_.second );
        return rand_action_dist( rng_ );
    }

};
