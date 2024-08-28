#pragma once

#include "concepts.h"

/**
 * @brief Base class providing a unified interface for various function approximators.
 *
 * The FunctionApproximator class serves as a flexible wrapper to standardize the
 * interface for different types of function approximators. This allows users to
 * integrate models ranging from simple linear regressions implemented in Eigen to
 * complex deep neural networks built with libraries like LibTorch, all within a
 * consistent API. The primary purpose of this class is to ensure that any function
 * approximator, regardless of its underlying implementation, adheres to a common
 * structure, facilitating seamless integration with the rest of the AsyncRL++ library.
 * Use this class template for any policy-function or value-function approximators.
 *
 * @tparam Derived The specific function approximator class inheriting from this base class.
 * @tparam PredictionType The type of the output produced by the function approximator (must have a .size() method).
 * @tparam StateType The type representing the input state used for predictions.
 */

template <typename Derived,
          typename PredictionType,
          typename StateType>
requires HasSize<PredictionType>
class FunctionApproximator 
{ 

public:

    // Public API

    /**
     * @brief Predict the output based on the given state.
     * 
     * This function delegates the call to the derived class's predict method.
     * 
     * @param state The input state for which to make a prediction.
     * @return PredictionType The predicted output.
     */

    PredictionType predict( const StateType &state ) const { 
        return static_cast<Derived*>( this )->predict( state );
    }

    /**
     * @brief Get a reference to the parameters of the function approximator.
     * 
     * This method allows access to the internal parameters of the approximator, 
     * enabling updates and modifications. Implementation is delegated to the derived
     * class.
     * 
     * @return auto& A reference to the parameters of the function approximator.
     */

    auto& get_param_reference() { 
        return static_cast<Derived*>( this )->get_parameter_reference();
    }
};
