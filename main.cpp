#include <iostream>
#include "lazySequence.hpp"

int main() {
    auto square_gen = new SquareGenerator<int>();
    
    LazySequence<int> test_sequence(square_gen);

    std::cout<<test_sequence.Get(5)<<"\n";
    test_sequence.Append(90);

    std::cout<<test_sequence.Get(0)<<"\n";
    std::cout<<test_sequence.Get(1)<<"\n";
    std::cout<<test_sequence.Get(2)<<"\n";
    std::cout<<test_sequence.Get(3)<<"\n";
    std::cout<<test_sequence.Get(4)<<"\n";
    std::cout<<test_sequence.Get(5)<<"\n";

    std::cout<<test_sequence.GetLast()<<"\n";
}
//    std::cout<<test_sequence.GetLength().get_infinite()<<"\n";std::cout<<test_sequence.GetLength().get_finite()<<"\n";
//    Cache<int> test_cache(10);test_cache.push(5);std::cout<<test_cache.get_count();std::cout<<test_cache.get_capacity();std::cout<<test_cache.get(0)<<"\n";

//int big_counter = 0; 
