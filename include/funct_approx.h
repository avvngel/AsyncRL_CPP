#pragma once

#include <type_traits>

template <typename Derived, 
          typename PredictionType,
          typename StateType>
class FunctionApproximator { 
public:

    // Static assertion to check if 'Derived' truly inherits from 'FunctionApproximator'
    static_assert(std::is_base_of<FunctionApproximator, Derived>::value,
                  "Derived must inherit from FunctionApproximator");

    // Public API
    PredictionType predict( const StateType &state ) const { 
        return static_cast<Derived*>( this )->predict( state )
    };    

    auto& get_parameter_reference() { 
        return static_cast<Derived*>( this )->get_parameter_reference()
    };
};
