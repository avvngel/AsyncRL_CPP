#include <iostream>
#include <vector>
#include <thread>
#include "torch/torch.h"

std::vector<int>& create_thread_resources(){
    thread_local std::vector<int> vec( 10, -1 );
    return vec;
}

void thread_work( std::vector<int>& vec, int thread_id )
{
    for ( int i = 0; i < vec.size(); ++i )
    { 
        vec[ i ] *= thread_id;
    }
    std::cout << "Thread " << thread_id << ": " << vec << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    int num_threads = 7;
    for ( int i = 0; i < num_threads; ++i )
    {
        threads.emplace_back( [i](  ){ 
            auto vec = create_thread_resources();

            thread_work( vec, i );
        } );
    }
    
    for ( auto& thread : threads )
    { 
        thread.join();
    }

    return 0;
}


// To compile : g++ sandbox.cpp -o sandbox -I/opt/libtorch/include -I/opt/libtorch/include/torch/csrc/api/include -L/opt/libtorch/lib -ltorch_cpu -ltorch -lc10 -Wl,-rpath,/opt/libtorch/lib -pthread
