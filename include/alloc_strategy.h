#pragma once

/**
 * @file alloc_strategy.h
 *
 * Contains strategy structs for creating thread-specific resources by either
 * allocating on the stack or TLS
 *
 **/


/**
 * @brief Strategy for allocating Actor on thread stack
 **/
struct ActorStackAllocStrategy
{
    /**
     * @brief Function template for creating stack-allocated Actor
     *
     * @tparam Actor The type of Actor object to instantiate
     * @tparam Args Parameter pack of the types passed to the Actor constructor
     * @param args The arguments passed to the Actor constructor.
     *
     * @return instance of Actor
     **/
    template < typename Actor, typename... Args >
    static Actor create_actor( Args... args )
    {
        return Actor( std::foward<Args>( args )... );
    };
};

/**
 * @brief Strategy for allocating Actor on thread-local storage
 **/
struct ActorTLSAllocStrategy
{

    /**
     * @brief Function template for creating TLS-allocated Actor
     *
     * @tparam Actor The type of Actor object to instantiate
     * @tparam Args Parameter pack of the types passed to the Actor constructor
     * @param args The arguments passed to the Actor constructor.
     *
     * @return Reference to threal_local Actor instance
     **/

    template < typename, Actor, typename... Args >
    static Actor& create_actor( Args... args )
    {
        thread_local Actor actor( std::forward<Args>( args )... );
        return actor;
    };
};

/**
 * @brief Strategy for allocating Environment on thread stack
 **/
struct EnvStackAllocStrategy
{
     /**
     * @brief Function template for creating stack-allocated Environment
     *
     * @tparam EnvFactory The type of the factory callable
     * 
     * Must return an object with a **step** method (See <hyperlink> for requirements)
     *
     * @return Instance of type returned by env_factory
     **/
    template <IsEnvFactory EnvFactory>
    static auto create_env( EnvFactory env_factory )
    {
        return env_factory( );
    };

    /**
     * @brief Function template for creating stack-allocated Environment
     *
     * @tparam Enviroment The type of Environment object to instantiate
     *
     * See <hyperlink> for interface requirements.
     *
     * @param ref_env The reference Environment object to copy
     *
     * @return Copy of ref_env
     **/

 template <IsEnv Environment>
    static auto create_env( Environment& ref_env )
    {
        return Environment( ref_env ); // Create a copy of reference object
    };
};

/**
 * @brief Strategy for allocating Environment on thread-local storage
 **/
struct EnvTLSAllocStrategy
{

     /**
     * @brief Function template for creating TLS-allocated Environment
     *
     * @tparam EnvFactory The type of the factory callable
     * 
     * Must return an object with a **step** method (See <hyperlink> for requirements)
     *
     * @return Reference to thread_local instance of type returned by env_factory
     **/
   template <IsEnvFactory EnvFactory>
    static auto& create_env( EnvFactory env_factory )
    {
        thread_local env = env_factory( );
        return env;
    };
    
    /**
     * @brief Function template for creating TLS-allocated Environment
     *
     * @tparam Enviroment The type of Environment object to instantiate
     *
     * See <hyperlink> for interface requirements.
     *
     * @param ref_env The Environment object to copy
     *
     * @return Reference to thread-local copy of ref_env
     **/

template <isEnv Environment>
    static Environment& create_env( Environment& ref_env )
    {
        thread_local env = Environment( ref_env ); // Create a copy of reference object
        return env;
    }
};

// Useful concepts and aliases

template <typename Actor>
using DefaultActorAllocStrategy = std::conditional_t< IsLargeActor<Actor>
                                                    , ActorTLSAllocStrategy
                                                    , ActorStackAllocStrategy >;

template <typename Environment>
using DefaultEnvAllocStrategy = std::conditional_t< IsLargeEnv<Environment>
                                                  , EnvTLSAllocStrategy
                                                  , EnvStackAlocStrategy >;

