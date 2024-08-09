#pragma once

#include "lib_type_aliases.h"

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
    
    auto get_param_reference()
    { 
        return dist_approx_.get_param_reference();
    }

protected:
    
    FunctionApproximator& dist_approx_;
  
};
