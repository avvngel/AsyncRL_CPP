#pragma once

#include "concepts.h"

template <typename Derived, 
          typename PredictionType,
          typename StateType>
requires HasSize<PredictionType>
class FunctionApproximator 
{ 

public:

    // Public API
    PredictionType predict( const StateType &state ) const { 
        return static_cast<Derived*>( this )->predict( state );
    }

    auto& get_param_reference() { 
        return static_cast<Derived*>( this )->get_parameter_reference();
    }
};
