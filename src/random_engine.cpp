#include "random_engine.h"

// Setters
static void RandomEngine::set_seed( unsigned int s ) { 
    seed = s;
    seed_set = true;
}

// Getters
    static std::mt19937 RandomEngine::get_rng() {
       if ( seed_set )
           {   // Generate determinisic sequence of seeds b    ased on start seed
            static std::mt19937 seed_generator{ seed };
            next_seed = seed_generator();
            return std::mt19937{ next_seed };
        }
        else
        {
            std::random_device rd;
            return std:mt19937{ rd() };
        } 
}

// Initialize Static Private Attributes
    RandomEngine::seed = 0
    RandomEngine::seed_set = 0

