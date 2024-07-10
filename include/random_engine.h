#ifndef RANDOM_ENGINE_H
#define RANDOM_ENGINE_H

class RandomEngine { 
public:
    // Constructor
    RandomEngine( ) = default;    

    // Delete copy constructor and assignent operator
    RandomEngine( const &RandomEngine ) = delete;
    RandomEngine& operator=( const RandomEngine& ) = delete;

    // Setters
    void set_seed( unsigned int s ) { 
        seed = s;
        seed_set = true
}

    // Getters
    std::mt19937 get_rng() {
        if ( seed_set ) 
        {
            static unsigned int next_seed = seed;
            next_seed = ( next_seed + 1 )*2
            return std::mt19937{ next_seed };
        }
        else 
        { 
            std::random_device rd;
            return std:mt19937{ rd() }
        }
    }

private:
    // Private Attributes
    unsigned int seed;
    bool seed_set = false;
};

#endif // RANDOM_ENGINE_H
