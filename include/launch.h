#pragma once

#include <thread>
#include <cstdint>
#include <cstddef>
#include "torch/torch.h"
#include "type_aliases.h"
#include "concepts.h"

/**
 * @brief Launches an RL traning algorithm.
 * 
 * This function launches the RL training algorithm prescribed by the Algorithm
 * template parameter's static **train** member function template on a number
 * of threads dependent on the available hardware threads. It executes an initial
 * setup routine prior to initializing the threads and an on-thread setup routine
 * prior to training, both prescribed by the SetupStrategy. Thread-specific Actor
 * and Environment instances are conditionally allocated on either the stack or
 * TLS dependent on size.
 *
 * @tparam Algorithm The algorithm to be launched. ( See <hyperlink to algorithms> )
 *
 * @tparam EnvArg The type of env_arg provided. ( See env_arg param )
 *
 * @tparam SetupStrategy Optional param to specify a SetupStrategy. ( See <hyperlink> )
 *
 * @tparam Args Types of arguments to be forwarded to Algorithm::template train(  )
 *
 * @param env_arg Either an instance of the environment ( see <hyperlink> for
 * interface requirements ) or factory function that returns an enviroment. Note
 * that the latter can be used to provide different threads (actors) with different
 * environments.
 *
 * @param args Arguments to be forwarded to the Algorithm's call to **train**.
 * See documentation for specific algorithm for details on required parameters.
 **/

template < typename Algorithm
         , typename EnvArg
         , bool EnableLogging
         , typename... Args >

void launch( torch::nn::Module& nn_module
           , PolicyTypes policy_enum
           , EnvArg env_arg
           , Args... args )
{

    // Extract Environment type from env_arg
    if constexpr ( isEnvFactory<EnvArg> )
    {
        using Environment = decltype( env_arg );
    }
    else
    {
        using Environment = EnvArg;
    }

    // Determine allocation strategy for Actor and Environment
    using ActorAllocStrategy = DefaultActorAllocStrategy<Actor>;
    using EnvAllocStrategy = DefaultEnvAllocStrategy<Environment>;

    SetupManager< ActorAllocStrategy
                , EnvAllocStrategy
                , EnvArg
                , EnableLogging > setup_manager;

    setup_manager.pre_thread_setup( );

    std::size_t n_threads = std::thread::hardware_concurrency() - 6;
    Threads threads;

    for ( int i = 0; i < n_threads; ++i )
    {
        threads.emplace_back( [ & ]( )
            {
                auto [ actor, env ] setup_manager.create_thread_resources(
                                         torch::nn::Module, policy_enum, env_arg
                                         );
                
                Algorithm::train( actor, env, std::forward<Args&&>( args )... );

            }
            );
    }

    for ( auto& thread : threads )
    { 
        thread.join();
    }

};
