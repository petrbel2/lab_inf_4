#include <iostream>
#include "lazySequence.hpp"
#include "generator.hpp"

int main() {
    // Создаем генератор для последовательности квадратов
    auto square_gen = new Generator<int>([](int index) {return index * index;
    }, 10);
    
    LazySequence<int> test_sequence(square_gen);

    
}