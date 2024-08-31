#pragma once

#include "concepts.h"

template <typename PolicyType,
          typename RewardType,
          typename GradientType>
requires HasSize<GradientType>
class Learner
{
public:
    Learner( GradientCalculator& grad_calculator )
    : grad_calculator_( std::move( grad_calculator ) ) {};
    
    void update_policy( PolicyType policy, Gradients gradients )
    {
        // parameter update logic
    }

    void update_grad( RewardType reward )
    { 
        GradientType grad{ gradient_calculator_.compute( reward ) };
        d_theta_ += grad;
    }
    
protected:
    // Protected Members
    GradientType d_theta_
};
