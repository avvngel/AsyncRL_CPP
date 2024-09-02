#pragma once

#include "torch/torch.h"
#include "type_aliases.h"

/**
 * @brief function overload for discrete actions spaces with the same number actions per
 * action variable
 *
 * @return an at::Tensor representing the selected action
 */

Action select_random_action( const DiscreteUniformActionSpace& actions
                           , at::Generator rng )
    {
        return torch.randint( actions.n_actions, { actions.n_vars, 1 }, rng );
    }

/**
 * @brief function overload for discrete actions spaces with a varying number actions per
 * action variable
 *
 * @return an at::Tensor representing the selected action
 */

Action select_random_action( const DicreteVariableActionSpace& actions
                           , at::Generator rng )
    {
        return torch::round( torch.rand( { actions.n_vars, 1 }, rng )*actions.n_actions );
    }
/**
 * @brief function overload for continuous actions spaces with the same upper and lower
 * bounds for each action variable
 *
 * @return an at::Tensor representing the selected action
 */

Action select_random_action( const ContinuousUniformActionSpace& actions
                           , at::Generator rng )
    {
        return torch.rand( { actions.n_vars, 1 }, rng )
               * ( actions.ub - actions.lb ) 
               + actions.lb;
    }

/**
 * @brief function overload for continuous actions spaces with a varying upper and lower
 * bounds for each action variable
 *
 * @return an at::Tensor representing the selected action
 */

Action select_random_action( const ContinuousVariableActionSpace& actions
                           , at::Generator rng )
    { 
        return torch.rand( actions.bounds.size( 0 ), rng )
               * ( action.bounds.index( Slice(), 1 ) - action.bounds.index( Slice(), 0 ) )
               + actions.bounds.index( Slice(), 0 );
    }

