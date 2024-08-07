#include <iostream>
#include <set>
#include "random_engine.h"

int test_set_seed() { 
    
    // Set a test seed and get a seed_generator
    unsigned int test_seed = 2;
    std::mt19937 test_seed_generator{ test_seed };

    // Set RandomEngine seed and get a seeded rng
    RandomEngine::set_seed( test_seed );

    // Get rng from RandomEngine and rng with seed set by test seed generator
    std::mt19937 test_rng{ test_seed_generator() };
    auto rng = RandomEngine::get_rng();
    
    // Generate sequences and compare
    int seq_len = 5;
    
    for ( int i = 0; i != seq_len; i++ ) 
    { 
        if ( rng() != test_rng() )
        { 
            std::cout << "Test Failed: Seeded RNG sequences do not match.";
            return 1;
        }
    }

    std::cout << "Test Passed: Seeded RNG sequences match.";
    return 0;     
}

int test_unseeded_rng() { 

    auto rng = RandomEngine::get_rng();
    std::set<uint32_t> random_numbers;
    
    for ( int i = 0; i != 100; i++ )
    { 
        random_numbers.insert( rng() );
    }

    if ( random_numbers.size() > 1 )
    {
        std::cout << "Test Passed: Unseeded RNG generates random numbers.";
        return 0;

    }
    else { 
        std::cout << "Test Failed: Unseeded RNG generates identical numbers.";
        return 1;
    }
}

int main() {
    
    if ( test_set_seed() != 0)
        return 1;
            
    if ( test_unseeded_rng() != 0)
        return 1;
   
    return 0;

}

