#pragma once

#include <vector>
#include <iostream>
#include "funct_approx.h"
#include "type_aliases.h"

class SimpleApprox : public FunctionApproximator< SimpleApprox
                                                , DiscActionDist
                                                , State > 
{ 
public:
    //Public Constructor
    SimpleApprox() : params( 20, 1 ) {}

    // Public APIs
    DiscActionDist predict( State& state )
    { 
        ( void )state;
        DiscActionDist res( 100, 0 );
        res[ expected_action ] = 1;
        return res;
    }
    
    Parameters& get_param_references()
    { 
        return params;
    }
    
    // Getters
    DiscAction get_expected_action()
    { 
        return expected_action;
    }
private:
    // Private Members
    Parameters params;
    DiscAction expected_action{ 50 };
};

