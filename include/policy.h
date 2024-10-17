#pragma once

#include <torch/torch.h>
#include "type_aliases.h"

/**
 * @brief Base class for policies using the CRTP pattern to enable static polymorphism.
 * 
 * @tparam Derived The derived policy class.
 * @tparam FunctionApproximator The function approximator used to approximate the action distribution.
 * @tparam StateType The type representing the state in the environment.
 * @tparam ActionType The type representing the action.
 */

template < typename Derived,
           IsActionSpace ActionSpace >
class Policy
{ 
public:
    
    // Public Constructor

    /**
     * @brief Constructs a Policy object with the given function approximator.
     * 
     * @param dist_approx The torch::nn::Module for approximating the action distribution
     * @param action_space A torch::Tensor specifying the action_space representation
     */
    
    Policy( torch:nn:Module dist_approx, at::Tensor& action_space ) 
    : dist_approx_( dist_approx ), action_space_ action_space {}
    
    // Public APIs

    /**
     * @brief Samples an action given the current state and random number generator.
     * 
     * @param state The current state.
     * @param rng The random number generator used for sampling.
     * @return ActionType The sampled action.
     */
    
    Action sample( const State& state, at::Generator& rng )
    { 
        return static_cast<Derived*>( this )->sample( state, rng );
    }
    
    // Getters

    /**
     * @brief Gets a reference to the parameters of the function approximator.
     * 
     * @return A reference to the function approximator's parameters.
     */
    
    torch::Tensor get_param_reference()
    { 
        return dist_approx_.get_param_reference();
    }
    
    /**
     * @brief Get the action space of the environment
     *
     * If the action space is continuous, the resulting Tensor will have dimensions nx2,
     * with n being the number of action variables, and dim(1) containing the upper and
     * lower bounds for each action variable.
     * 
     * If the action space is discrete, the resultint Tensor wil have dimensions n,1,
     * where dim(1) contains the number of options per action variable
     * 
     * @return A torch::Tensor describing the action space of the environment.
     */

    ActionSpace get_action_space()
    { 
        return action_space_;
    }

protected:    

    torch::nn::Module& dist_approx_; /**< Reference to the torch::nn:Module used by the policy. */
    const ActionSpace action_space_ /// < Reference to the action space specification of the environment
};
