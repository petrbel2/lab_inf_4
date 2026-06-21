#include <iostream>
#include "lazySequence.hpp"
#include "generator.hpp"

int main() {
    // Создаем генератор для последовательности квадратов
    auto square_gen = new SquareGenerator<int>();
    
    LazySequence<int> test_sequence(square_gen);

}