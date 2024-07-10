#ifndef AGENT_H
#define AGENT_H
#include <memory>
#include "random_engine.h"
template <typename Derived,
          typename StateType, 
          typename FunctionApproximatorType,
          typename FunctionApproximatorOutputType> 
class Agent { 
public:
    // Constructor
    Agent( FunctionApproximatorType &value_fn )
    : value_fn_( value_fn ) { };
    
    // APIs
    StateType explore( StateType state, float epsilon ) { 
       
        if ( dis( gen ) < epsilon ) {      // Compare uniform random number to epsilon
            return static_cast<T*>( this )->select_random( state ); // Select Random Action
        }
        else { 
            return static_cast<T*>( this )->select_action( state );       // Select Greedy Action
        }            
    }
    
    StateType select_action( StateType state ) { /* Implement in Derived */ }

    StateType select_random( StateType state ) { /* Implement in Derived */ }

private:
    FunctionApproximatorType& value_fn_;
    auto gen = RandomEngine::get_rng();
    std::uniform_real_distribution<> dis(0.0, 1.0);
};

#endif // AGENT_H
