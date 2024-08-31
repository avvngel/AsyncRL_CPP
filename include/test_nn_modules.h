#pragma once

#include "torch/torch.h"

/**
 * @file test_nn_module.h
 * @brief Sample Torch Modules for testing and debugging
 */

/**
 * @brief A trivial Torch Module that just returns the input as its forward pass
 *
 *      Used for testing Actor's interaction with RandomEngine
 */

struct SimpleNet : torch::nn::Module
{ 
    /**
     * @brief Constructor initializes a single linear layer with one weight 
     * equal to 1 and a bias of 0 (thus, returning the input).
     */

    SimpleNet()
    { 
        fc1 = register_module( 'fc1', torch::nn::Linear(1, 1) );
        torch::nn::init::constant_( fc1->weight, 1.0 );
        torch::nn::init::constant_( fc1->bias, 0.0 );
    }

    /**
     *@brief Forward pass calls forwad pass of only linear layer
     */
    
    torch::Tensor forward( torch::Tensor state )
    { 
        return fc1->forward( state );
    }
};


