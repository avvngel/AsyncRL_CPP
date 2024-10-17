#pragma once

#include "cstddef"
#include "torch/torch.h"
#include "type_aliases.h"
#include "exploration_strategy.h"
#include "random_selector.h"

template < typename EpsilonProvider
         , typename  PolicyType >
class EpsilonGreedy : ExplorationStrategy<EpsilonGreedy>
{ 
public:
    EpsilonGreedy( EpsilonProvider epsilon_provider 
                 , PolicyType policy
                 , std::size_t cache_size)
    : epsilon( epsilon_provider ) 
    , cache_size_( cache_size )
    , curr_idx( cache_size )
    { void( policy ); /* Purely to enable CTAD */ }
    
    Action explore( const State& state
                  , const PolicyType& policy
                  , at::Generator& rng )
    {  
        // Check if random_cache needs to be refreshed
        if ( curr_idx == cache_size_ )
        { 
            random_cache = torch::rand( { cache_size }, rng );
            random_cache_a = random_cache.accessor<float, 1>();
            curr_idx = 0;
        }
        
        // Epsilon Greedy
        if ( random_cache_a[ curr_idx ] < epsilon() )
        { 
            return select_random_action( policy.action_space_ );
        }

        else
        { 
            return policy.sample( state, rng );
        }
    }

private:
    EpsilonProvider epsilon;
    at::Tensor  random_cache;
    auto random_cache_a;
    std::size_t cache_size_;
    std::size_t curr_idx;
    
};

// CTAD deduction guide
EpsilonGreedy( EpsilonProvider, PolicyType, std::size_t )
       -> EpsilonGreedy< EpsilonProvider, PolicyType >;
