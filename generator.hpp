#ifndef GENERATOR_H
#define GENERATOR_H

#include <functional>
//#include <stdexcept>

template<typename data_type>
class Generator {
private:
    std::function<data_type(int)> generate_func;
    int current_position;
    int max_elements;
    bool is_infinite;

public:
    // Конструктор для конечной последовательности
    Generator(std::function<data_type(int)> func, int count) 
        : generate_func(func), current_position(0), max_elements(count), is_infinite(false) {}
    
    // Конструктор для бесконечной последовательности
    Generator(std::function<data_type(int)> func) 
        : generate_func(func), current_position(0), max_elements(-1), is_infinite(true) {}
    
    // Проверка наличия следующего элемента
    bool hasNext() const {
        return is_infinite || current_position < max_elements;
    }
    
    // Получить следующий элемент
    data_type next() {
        //if (!hasNext()) {
        //    throw std::out_of_range("Generator exhausted: no more elements");
        //}
        return generate_func(current_position++);
    }
    
    // Сброс генератора в начало
    void reset() {
        current_position = 0;
    }
    
    // Получить текущую позицию
    int getCurrentPosition() const {
        return current_position;
    }
    
    
    // Получить элемент по индексy
    data_type get(int index) {
        //if (!is_infinite && index >= max_elements) {
        //    throw std::out_of_range("Index out of bounds");
        //}
        return generate_func(index);
    }
};

#endif