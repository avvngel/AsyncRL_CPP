#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <type_traits>
#include <typeinfo>

constexpr int THRESHOLD = 64;

template <typename T>
concept IsLargeType = ( sizeof( T ) > THRESHOLD );

struct SmallStrategy
{ 
    constexpr static int value = 1;
};

struct LargeStrategy
{ 
    constexpr static int value = 2;
};


using LargeType = std::array<std::int64_t, 9>;
using SmallType = std::array<std::int64_t, 1>;

template <typename T>
using DefaultStrategy = std::conditional_t< IsLargeType<T>
                                          , LargeStrategy
                                          , SmallStrategy >;

int main( )
{ 
    constexpr int small_val = DefaultStrategy<SmallType>::value;
    constexpr int large_val = DefaultStrategy<LargeType>::value;
    
    std::cout << "Small Value: " << small_val << std::endl
              << "Large Value: " << large_val << std::endl;
}

