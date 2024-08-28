#pragma once

#include <vector>
#include <iostream>
#include "funct_approx.h"
#include "type_aliases.h"

class SimpleApprox : public FunctionApproximator< SimpleApprox
                                                , DiscActionDist
                                                , DiscState > 
{ 
public:
    //Public Constructor
    SimpleApprox() : params( 20, 1 ) {}

    // Public APIs
    DiscActionDist predict( const DiscState& state ) const
    { 
        ( void )state;
        DiscActionDist res( 1000, 0 );
        res[ expected_action ] = 1;
        return res;
    }
    
    Parameters& get_param_reference()
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

