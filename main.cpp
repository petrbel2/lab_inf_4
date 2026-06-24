#include <iostream>
#include "lazySequence.hpp"
#include "generator.hpp"

int main() {
    auto square_gen = new SquareGenerator<int>();
    
    LazySequence<int> test_sequence(square_gen);
    Cache<int> test_cache(10);
    test_cache.push(5);
    std::cout<<test_cache.get_count();
    std::cout<<test_cache.get_capacity();
    std::cout<<test_cache.get(0)<<"\n";
    std::cout<<test_sequence.GetLength().get_infinite()<<"\n";
    std::cout<<test_sequence.GetLength().get_finite()<<"\n";

    std::cout<<test_sequence.Get(5);
    std::cout<<test_sequence.Get(5);
}