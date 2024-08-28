#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "test_approximators.h"
#include "test_policies.h"
#include "actor.h"
#include "type_aliases.h"
#include "random_engine.h"


using TestActor = Actor<SimplePolicy, DiscState, DiscAction>;

int test_select_action()
{   
    SimpleApprox test_fn;
    SimplePolicy test_policy( test_fn );
    TestActor actor( test_policy, RandomEngine::get_rng() );
    DiscState test_state{ 0 };
    int n_selections{ 100 };

    for ( int i = 0; i !=  n_selections; i++ )
    { 
        // Select Action
        DiscAction selected_action = actor.select_action( test_state );

        // Compare to expected result
        if ( selected_action != test_fn.get_expected_action() )
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
    SimplePolicy test_policy( test_fn );
    TestActor actor( test_policy, RandomEngine::get_rng() );
    DiscState test_state{ 0 };
    
    // Set up test params
    int n_selections{ 1000 };
    float critical_number{ 4 }; // 99.9937% confidence

    // Compute upper conf bound for hit rate based on binomial distribution
    std::size_t n_unique_actions{ test_fn.predict( test_state ).size() };
    float hit_prob = 1.0f/n_unique_actions;
    float sd = std::sqrt( n_selections*hit_prob*( 1.0f - hit_prob ) );
    float hits_ub = hit_prob*n_selections + critical_number*( sd ) + 1;
    float hit_rate_ub = hits_ub/n_selections;

    // Count how often random selection matches the expected selection
    int n_matches{ 0 };
    for ( int i = 0; i != n_selections; i++ ) 
    { 
        if ( actor.select_random( test_state ) == test_fn.get_expected_action() )
            ++n_matches;
    }
    float hit_rate{ static_cast<float>( n_matches )/n_selections };
    
    // Verfity if hit rate is within accepted tolerance
    if ( hit_rate < hit_rate_ub )
        return 0;
    std::cout << "n_matches: " << n_matches << std::endl;
    std::cerr << "Method 'select_random' Failed: expected hit rate of no greater than"
              << hit_rate_ub
              << " but got "
              << hit_rate << std::endl;
    return 1;
}

int test_discrete_exploration()
{
    SimpleApprox test_fn;
    SimplePolicy test_policy( test_fn );
    TestActor actor( test_policy, RandomEngine::get_rng() );
    DiscState test_state{ 0 };

    // Set up test params
    int n{ 1000 }; // number of selections
    float epsilon{ .05 };
    float critical_num{ 4 }; // 99.9937% confidence

    // Compute lower conf bound for number of hits based on binomial dist.
    std::size_t n_unique_actions{ test_fn.predict( test_state ).size() };
//    int n = std::ceil( n_selections*epsilon ); // number of random selections
    float hit_prob = 1 - epsilon*( n_unique_actions - 1 )/n_unique_actions;
    float stdev = std::sqrt( n*hit_prob*( 1.0f - hit_prob ) );
    float n_matches_lb = std::ceil( hit_prob*n - critical_num*( stdev ) );
    std::cout << n << ' ' << stdev << ' ' << n_matches_lb << std::endl;
    int n_matches{ 0 };

    // Count how often selected action matches expected action
    for ( int i = 0; i != n; i++ )
    { 
        if ( actor.explore( test_state, epsilon ) == test_fn.get_expected_action() )
            ++n_matches;
    }
    
    // Check if match count is within expected tolerance
    if ( n_matches_lb-1 < n_matches )
        return 0; // Test passed

    std::cerr << "Method 'explore' Failed: expected no less than "
              << n_matches_lb
              << " match(es), but got "
              << n_matches << std::endl;
    return 1; // Test failed
}

int main()
{ 
    if ( test_select_action() != 0 )
        return 1;
    
    if ( test_select_random() != 0 )
        return 1;

    if ( test_discrete_exploration() != 0 )
        return 1;

    return 0;
}
