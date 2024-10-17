#pragma once

#include "type_aliases"

template < typename Derived
         , IsActionSpace ActionSpace
         , typename Info >

class Environment
{ 
public:
    EnvTimeStep< ActionSpace, Info > step( const Action& action )
    { 
        return static_cast<Derived*>( this )->step( action );
    }
};
