#pragma once

template < typename Derived
         , typename FunctionApproximator
         , typename StateType
         , typename ActionType >

class Policy
{ 
public:
    
    // Public Constructor
    Policy( FunctionApproximator dist_approx ) : dist_approx_( dist_approx ) {}
    
    // Public APIs
    
    ActionType sample( const StateType& state, std::mt19937 rng ) const
    { 
        return static_cast<Derived*>( this )->sample( state, rng );
    }
    
    // Getters    
    auto get_param_reference()
    { 
        return dist_approx_.get_param_reference();
    }
    
    // Get Distribution Approximator
    auto return dist_approx_;

protected:
    
    FunctionApproximator& dist_approx_;
  
};
