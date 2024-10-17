#pragma once

#include <cstdint>
#include "config_defaults.h" 

struct RolloutConfig
{ 
    RolloutConfig
    ( std::uint32_t random_cache_size = default_random_cache_size
    , 
    )

    : std::uint32_t random_cache_size_( random_cache_size )
    ,
    { }
   
    std::uint32_t random_cache_size_;
}
