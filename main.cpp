#include <iostream>
#include "lazySequence.hpp"
#include "generator.hpp"

int main() {
    // Создаем генератор для последовательности квадратов
    auto square_gen = new Generator<int>([](int index) {
        return index * index;
    }, 10);  // 10 элементов: 0, 1, 4, 9, 16, 25, 36, 49, 64, 81
    
    // Перебираем элементы через генератор без прямого обращения
    while (square_gen->hasNext()) {
        std::cout << square_gen->next() << " ";
    }
    std::cout << std::endl;
    
    // Сброс и повторное использование
    square_gen->reset();
    
    // Пропуск первых 3 элементов
    square_gen->skip(3);
    
    // Перебор оставшихся
    while (square_gen->hasNext()) {
        std::cout << square_gen->next() << " ";
    }
    std::cout << std::endl;
    
    delete square_gen;
    return 0;
}