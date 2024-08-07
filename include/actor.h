#pragma once

#include <random>

/**
 * @brief Base class template for Actor using Curiously Recurring Template Pattern (CRTP).
 * 
 * This class represents an agent in a reinforcement learning setting. The agent selects actions
 * based on a function approximator, which can represent a policy or value function. The class
 * provides mechanisms for action selection, exploration, and random action selection.
 * 
 * @tparam Derived The derived class that inherits from this base class.
 * @tparam FunctionApproximator The type of the function approximator used to generate action distributions or parameters.
 * @tparam StateType The type representing the state of the environment.
 * @tparam ActionType The type representing the action that the agent can take.
 */

template <typename Derived, 
          typename FunctionApproximator, 
          typename StateType, 
          typename ActionType>
class Actor
{ 
public:
    
    // Public Constructor
    Actor( FunctionApproximator& action_dist_approx, std::mt19937& rng,  )
    : action_dist_approx_( action_dist_approx ), rng_( rng ) {};
    
    // Public APIs
    
    /**
     * @brief Selects an action based on the current state using the derived class's implementation.
     * 
     * This method is overridden by the derived class to implement the specific action selection logic.
     * 
     * @param state The current state of the environment.
     * @return ActionType The selected action.
     */

    ActionType select_action( const StateType& state ) const
    {
        return static_cast<Derived*>( this )->select_action( state );
    }
    

    /**
     * @brief Selects a random action based on the current state.
     * 
     * This method is overridden by the derived class to implement the specific random action selection logic.
     * 
     * @param state The current state of the environment.
     * @return ActionType The randomly selected action.
     */

    ActionType select_random( const StateType& state ) const
    { 
        return static_cast<Derived*>( this )->select_random( state );
    }

    /**
     * @brief Explores the action space by selecting either a random action or an action based on the policy.
     * 
     * This method implements epsilon-greedy exploration. With a probability of epsilon, a random action
     * is selected; otherwise, the action is selected based on the policy.
     * 
     * @param state The current state of the environment.
     * @param epsilon The exploration rate, where a higher value increases the likelihood of random action selection.
     * @return ActionType The selected action.
     */    

    ActionType explore( const StateType& state, float epsilon) const
    { 
        if ( random() < epsilon )
            return select_random( state );

        else
            return select_action( state );    
    }

protected:

    // Private Members
    FunctionApproximator& action_dist_approx_;
    auto& rng;
    std::uniform_real_distribution<> rand_dist( 0.0, 1.0 );
    

    /**
     * @brief Generates a random floating-point number between 0.0 and 1.0.
     * 
     * This method uses the uniform distribution initialized in the constructor.
     * 
     * @return float A random number between 0.0 and 1.0.
     */    

    // Private APIs
    float random() { return rand_dist( rng ) };
};
