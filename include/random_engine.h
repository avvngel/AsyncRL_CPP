#pragma once

#include <random>
#include "torch/torch.h"

/**
 * @brief A utility class for managing global random number generation with optional seeding.
 *
 * The RandomEngine class provides a mechanism for setting a global seed while enabling 
 * threads to have their own local seed to ensure reproducibility and sufficient
 * variability across all random number generators used within the library. By
 * default, the random engine is unseeded, producing non-deterministic random sequences 
 * because the random number generators (RNGs) returned by this class are seeded with a 
 * non-deterministic sequence of seeds. Once a seed is set, a seed generator produces a 
 * deterministic sequence of seeds, ensuring that the RNGs returned will produce 
 * deterministic sequences of numbers across runs.
 */

class RandomEngine {
public:

    // Public Constructor

    /**
     * @brief Default constructor for the RandomEngine.
     *
     * Initializes the random engine without setting a seed. Random number generation
     * will be non-deterministic until a seed is explicitly set.
     */

    RandomEngine( ) = default;

    /**
     * @brief Deleted copy constructor to prevent copying.
     *
     * This class should not be copied to ensure consistent random number generation
     * across the library.
     */

    RandomEngine( const RandomEngine& ) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment.
     *
     * This class should not be assigned to another instance to ensure consistent random
     * number generation across the library.
     */

    RandomEngine& operator=( const RandomEngine& ) = delete;

    // Public APIs

    /**
     * @brief Sets the seed for the random number generator.
     *
     * Once the seed is set, a seed generator produces a deterministic sequence of seeds
     * that are used to seed all subsequent RNGs returned by get_rng(). This ensures that
     * the RNGs will produce the same sequence of numbers across different runs.
     *
     * @param s The seed value to be set.
     */

    static void set_seed( unsigned int s );

    /**
     * @brief Returns a new random number generator.
     *
     * @return A an at::Generator random number generator.
     */
    
    static at::Generator get_rng();

private:
    // Private Attributes

    /// The seed value for the seed generator
    static unsigned int seed; 

    /// Flag indicating whether the seed has been set
    static bool seed_set;
};

