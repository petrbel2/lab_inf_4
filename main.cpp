#include <iostream>
#include "lazySequence.hpp"
#include "generator.hpp"

int main() {
    auto square_gen = new SquareGenerator<int>();
    
    LazySequence<int> test_sequence(square_gen);

    std::cout<<test_sequence.Get(5);
    std::cout<<test_sequence.Get(5);
}