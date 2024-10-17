#pragma once

template < Derived >
class EpsilonProvider
{ 
    float operator()()
    {
        return static_cast<Derived*>( this )();
    }
};
