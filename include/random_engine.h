#pragma once

#include<random>

class RandomEngine { 
public:
    // Constructor
    RandomEngine( ) = default;    

    // Delete copy constructor and assignent operator
    RandomEngine( const &RandomEngine ) = delete;
    RandomEngine& operator=( const RandomEngine& ) = delete;

    // Setters
    static void set_seed( unsigned int s ); 

    // Getters
    static std::mt19937 get_rng();

private:
    // Private Attributes
    static unsigned int seed;
    static bool seed_set;
};

