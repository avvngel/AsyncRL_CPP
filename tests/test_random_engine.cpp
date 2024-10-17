#include <iostream>
#include <set>
#include <limits>
#include "random_engine.h"

int test_set_seed() { 
    
    // Set a test seed and get a seed_generator
    unsigned int test_seed = 2;
    auto test_seed_generator{ at::make_generator<at::CPUGeneratorImpl>( test_seed ) };

    // Set RandomEngine seed and get a seeded rng
    RandomEngine::set_seed( test_seed );

    // Get rng from RandomEngine and rng with seed set by test seed generator
    auto next_seed{ torch::randint( std::numeric_limits<int>::max(), {1}, test_seed_generator() ).item() };
    at::Generator test_rng{ at::make_generator<at::CPUGeneratorImpl>( next_seed ) };
    at::Generator rng = RandomEngine::get_rng();
    
    // Generate sequences and compare
    int seq_len = 1000;
    
    at::Tensor test_seq{ torch::rand( { seq_len }, test_rng ) };
    at::Tensor seq{ torch::rand( { seq_len }, test_rng ) };
    
    
    if ( !at::equal( seq, test_seq ) )
    { 
        std::cout << "Test Failed: Seeded RNG sequences do not match.";
        return 1;
    }

    std::cout << "Test Passed: Seeded RNG sequences match.";
    return 0;     
}

int test_unseeded_rng() { 

    auto rng{ RandomEngine::get_rng() };
    int seq_len = 1000;
    rand_tensor{ torch::rand( { seq_len }, rng ) };
    std_dev{ torch::std( rand_tensor ) }
    

    if ( std_dev.item<double>() > 0 )
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

