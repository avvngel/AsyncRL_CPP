#pragma once

#include "concepts.h"

template <typename PolicyType>
class Learner
{ 
public:
    Learner( GradientCalculator& grad_calculator ) 
    : grad_calculator_( std::move( grad_calculator ) ) {};
    
    void update( PolicyType policy, Gradients gradients )
    { 
        // parameter update logic
    }
    
    void accumulate_grad(  )
};
