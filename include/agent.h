

#pragma once

#include <memory>
#include "random_engine.h"

template <typename Derived,
          typename StateType,
          typename ActionType, 
          typename FunctionApproximatorType>
class Agent { 

public:
    // Constructor
    Agent( FunctionApproximatorType &value_fn )
    : value_fn_( value_fn ) { };
    
    // APIs
    ActionType explore( StateType state, float epsilon ) { 
       
        if ( random() < epsilon ) {        // Compare uniform random number to epsilon
            return select_random( state ); // Select Random Action
        }
        else { 
            return select_action( state ); // Select Greedy Action
        }            
    }
    
    ActionType select_action( StateType state ) { 
        return static_cast<Derived*>( this )->select_action( state )
}

    ActionType select_random( StateType state ) { 
        return static_cast<Derived*>( this )->select_random( state ) 
}

private:
    // Private Attributes
    FunctionApproximatorType& value_fn_;
    auto gen = RandomEngine::get_rng();
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Private API
    float random() { return dis( gen ) };
};
