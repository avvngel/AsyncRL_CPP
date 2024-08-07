#include <iostream>
#include <vector>
#include "funct_approx.h"
#include "type_aliases.h"

class TestFunctApprox : public FunctionApproximator<TestFunctApprox, DiscActionDist, State> 
{ 
public:

    TestFunctApprox() : params( 20, 1 ) {};

    DiscActionDist predict( State state ) const 
    {
        std::cout << state; 
        DiscActionDist res( 100, 0 );
        res[ 50 ] = 1;
        return res;
    }
    
    Parameters& get_param_reference()
    { 
        return params;
    }
    
private:

    Parameters params;
};

static_assert(std::is_base_of<FunctionApproximator<TestFunctApprox, 
                                                   DiscActionDist, 
                                                   State>, 
                                                   TestFunctApprox>::value,
              "TestFunctApprox should derive from FunctionApproximator");

int test_predict_method()
{
    // Initialize function approximator and a test_state
    TestFunctApprox test_fn;
    int test_state{ 0 };

    // Initialize expected output
    DiscActionDist ans( 100, 0 );
    ans[ 50 ] = 1;
    
    // Compare to expected output
    if ( test_fn.predict( test_state ) != ans )
        return 1;
    return 0;
}

int test_get_param_reference_method()
{ 
    // Initialize function approximator and expected output
    TestFunctApprox test_fn;
    Parameters ans( 20, 1 );
    
    // Compare to expected output
    if ( test_fn.get_param_reference() != ans )
        return 1;
    return 0;
}

int main() 
{
    // Run Tests
 
    if ( test_predict_method() != 0)
        return 1;

    if ( test_get_param_reference_method() != 0)
        return 1;

    return 0;
}
