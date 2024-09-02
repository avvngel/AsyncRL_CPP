#include "random_engine.h"

// Setters
void RandomEngine::set_seed( unsigned int s ) { 
    seed = s;
    seed_set = true;
}

// Getters
at::Generator RandomEngine::get_rng() {
   if ( seed_set )
       {   // Generate determinisic sequence of seeds based on start seed
        static at::Generator seed_generator{ at::make_generator<at::CPUGeneratorImpl>( seed ) };
        auto next_seed = seed_generator->random();
        return at::make_generator<at::CPUGeneratorImpl>( next_seed );
    }

    else
    {
        static std::random_device rd;
        return at::make_generator<at::CPUGeneratorImpl>( rd() );
    } 
}

// Initialize Static Private Attributes
unsigned int RandomEngine::seed = 0;
bool RandomEngine::seed_set = false;

