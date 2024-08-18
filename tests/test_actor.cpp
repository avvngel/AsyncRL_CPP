#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
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
    
    // Set up test params
    int n_selections{ 1000 };
    float critical_number{ 2.576 };
    float tol{ 1e-3 };  

    // Compute expected hit rate based on binomial distribution
    int n_unique_actions{ test_fn.predict( test_state ).size() };
    float hit_prob = 1.0f/n_unique_actions;
    float sd = std::sqrt( n_selections*hit_prob*( 1.0f - hit_prob ) );
    float expected_hits = hit_prob*n_selections + critical_number*( sd );
    float expected_hit_rate = expected_hits/n_selections;

    // Count how often random selection matches the expected selection
    int n_matches{ 0 };
    for ( int i = 0; i != n_selections; i++ ) 
    { 
        if ( actor.select_random( test_state ) == test_fn.get_expected_action() )
            ++n_matches;
    }
    float hit_rate{ static_cast<float>( n_matches )/n_selections };
    
    // Verfity if hit rate is within accepted tolerance
    if ( std::abs( hit_rate - expected_hit_rate ) < tol )
        return 0;

    std::cerr << "Method 'select_random' Failed: expected hit rate of "
              << expected_hit_rate
              << " with a tolerance of "
              << tol
              << " but got "
              << hit_rate << std::endl;
    return 1;
}   

int test_exploration()
{ 
    SimpleApprox test_fn;
    TestActor actor( test_fn, RandomEngine::get_rng() );
    State test_state{ 0 };

    // Set up test params
    int n_selections{ 1000 };
    float epsilon{ .05 };
    float critical_num{ 2.576 };

    // Compute expected number of hits based on binomial distribution
    int n_unique_actions{ test_fn.predict( test_state ).size() };
    int n = std::ceil( n_selections*epsilon ); // number of random selections
    float hit_prob = 1.0f/n_unique_actions;
    float stdev = std::sqrt( n*hit_prob*( 1.0f - hit_prob ) );
    float expected_matches = std::ceil( hit_prob*n + critical_num*( stdev ) );
    
    int n_matches{ 0 };

    // Count how often selected action matches expected action
    for ( int i = 0; i != n_selections; i++ )
    { 
        if ( actor.explore( test_state, epsilon ) == test_fn.get_expected_action() )
            ++n_matches;
    }
    
    // Check if match count is within expected tolerance
    if ( std::abs( n_matches - expected_matches ) <= tol )
        return 0; // Test passed

    std::cerr << "Method 'explore' Failed: expected "
              << expected_matches
              << " matches, but got "
              << n_matches << std::endl;
    return 1; // Test failed
}

int main()
{ 
    if ( test_select_action() != 0 )
        return 1;
    
    if ( test_select_ramdom() != 0 )
        return 1;

    if ( test_exploration() != 0 )
        return 1;

    return 0;
}
