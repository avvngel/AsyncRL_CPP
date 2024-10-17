#pragma once

#include "type_aliases.h"

template<typename Derived>
class ExplorationStrategy
{ 
    Action explore( Policy& policy, at::Generator rng )
    { 
        return static_cast<Derived*>( this )->explore;
    }
}
