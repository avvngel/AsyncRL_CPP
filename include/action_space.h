#pragma once

#include "torch/torch.h"

struct DiscreteUniformActionSpace
{
    DiscreteActionSpace( int num_vars, int num_actions )
    : n_vars( num_vars ), n_actions( num_actions ) { }
    
    int n_vars, n_actions;
};

struct DiscreteVariableActionSpace
{
    DiscreteActionSpace( int num_vars, at::Tensor& num_actions )
    : n_vars( num_vars ), n_actions( num_actions ) { }

    int n_vars;
    at::Tensor& n_actions;
};

struct ContinuousUniformActionSpace
{ 
    ContinuousActionSpace( int num_vars, std::pair<float> uniform_bounds )
    : n_vars( num_vars ), lb( uniform_bounds.left ), ub( uniform_bounds.right )
    { }

    int n_vars, lb, ub;
};

struct ContinuousVariableActionSpace
{ 
    ContinuousActionSpace( at::Tensor& bounds )
    : lower_bounds( bounds.index( Slice(), 0 ).contiguous() ), 
      upper_bounds( bounds.index( Slice(), 1 ).contiguous() )
    { }

    at::Tensor& lower_bounds;
    at::Tensor& upper_bounds;
};

using ActionSpaceTypes = std::tuple< DiscreteUniformActionSpace
                                   , DiscreteVariableActionSpace
                                   , ContinuousUniformActionSpace
                                   , ContinuousVariableActionSpace >

