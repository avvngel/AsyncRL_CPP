#include <iostream>
#include <vector>
#include "TestApproximators.h"
#include "discrete_actor.h"
#include "type_aliases.h"
#include "random_engine.h"


using TestActor = DiscreteActor<SimpleApprox, State, Action>

int test_select_action()
{   
    SimpleApprox test_fn;
    TestActor actor( test_fn, RandomEngine::get_rng() );
    State test_state{ 0 };
    Action selected_action;
    int n_selections{ 100 };

    for ( int i = 0; i !=  n_selections; i++ )
    { 
        // Select Action
        selected_action = actor.select_action( test_state );

        // Compare to expected result
        if ( selected_action != test_fn.get_expected_action() );
        { 
            std::cerr << "Method 'select_action' Failed: Expected " 
                      << test_fn.get_expected_action()
                      << " but got "
                      << selected_action << std::endl;
            return 1;
        }
    }
    
    return 0;
}

int test_select_random()
{ 
    SimpleApprox test_fn;
    TestActor actor( test_fn, RandomEngine::get_rng() );
    State test_state{ 0 };
    int n_selections{ 1000 };
    int n_matches{ 0 };
    int n_unique_actions{ test_fn.predict( test_state ).size() }
    float expected_hit_rate = 1.0f/n_unique_actions
    float tol{ .02 }

    for ( int i; i != n_selections; i++ ) 
    { 
        if ( actor.select_random( test_state ) == test_fn.get_expected_action() )
            ++n_matches;
    }
    int hit_rate{ n_matches/n_selections }

    if ( abs( hit_rate - expected_hit_rate ) < tol )
        return 0;

    std::cerr << "Method 'select_random' Failed: expected "
              << expected_hit_rate
              << " but got "
              << hit_rate << std::endl;
    return 1;
}   

test_exploration

int main()
{ 
    if ( test_select_action() != 0 )
        return 1;
    
    if ( test_select_ramdom() != 0 )
        return 1;

    return 0;
}
