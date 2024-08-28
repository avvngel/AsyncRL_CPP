#pragma once

/**
 * @brief Base class for policies using the CRTP pattern to enable static polymorphism.
 * 
 * @tparam Derived The derived policy class.
 * @tparam FunctionApproximator The function approximator used to approximate the action distribution.
 * @tparam StateType The type representing the state in the environment.
 * @tparam ActionType The type representing the action.
 */

template < typename Derived
         , typename FunctionApproximator
         , typename StateType
         , typename ActionType >

class Policy
{ 
public:
    
    // Public Constructor

    /**
     * @brief Constructs a Policy object with the given function approximator.
     * 
     * @param dist_approx The function approximator for the action distribution.
     */
    
    Policy( FunctionApproximator dist_approx ) : dist_approx_( dist_approx ) {}
    
    // Public APIs

    /**
     * @brief Samples an action given the current state and random number generator.
     * 
     * @param state The current state.
     * @param rng The random number generator used for sampling.
     * @return ActionType The sampled action.
     */
    
    ActionType sample( const StateType& state, std::mt19937& rng ) const
    { 
        return static_cast<Derived*>( this )->sample( state, rng );
    }
    
    // Getters

    /**
     * @brief Gets a reference to the parameters of the function approximator.
     * 
     * @return A reference to the function approximator's parameters.
     */
    
    auto get_param_reference()
    { 
        return dist_approx_.get_param_reference();
    }
   
    /**
     * @brief Gets the number of possible actions given a state.
     * 
     * @param state The current state.
     * @return std::size_t The number of possible actions.
     */

    auto get_n_actions( const StateType& state )
    { 
        static std::size_t n_actions{ dist_approx_.predict( state ).size() };
        return n_actions;
    }
 
protected:    

    FunctionApproximator& dist_approx_; /**< Reference to the function approximator used by the policy. */
  
};
