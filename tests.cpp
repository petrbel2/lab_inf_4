#include <iostream>
#include "lazySequence.hpp"
#include "tests.hpp"

int test_cache() {
    Cache<int> t_cache(10);
    int good_counter = 0;
    int result;
    try {
        result = t_cache.get_capacity();
        if (result != 10) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    try {
        result = t_cache.get_count();
        if (result != 0) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    try {
        result = t_cache.is_empty();
        if (not result) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    
    try {
        t_cache.push(5);
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    try {
        result = t_cache.get_count();
        if (result != 1) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    try {
        result = t_cache.is_empty();
        if (result) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    try {
        result = t_cache.get(0);
        if (result != 5) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    Ordinal number(0, 0);
    try {
        result = t_cache.get(number);
        if (result != 5) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    return good_counter;
}

int test_ordinal() {
    int good_counter = 0;
    int result;
    Ordinal first(1, 1);
    Ordinal second;
    Ordinal third(1, 1);
    try {
        result = first.is_infinite();
        if (result != 1) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    try {
        result = first.is_finite();
        if (result != 0) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    try {
        result = second.is_infinite();
        if (result != 0) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    try {
        result = second.is_finite();
        if (result != 1) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    try {
        result = first.get_infinite();
        if (result != 1) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    try {
        result = second.get_finite();
        if (result != 0) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    try {
        result = (first == third);
        if (result != 1) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    try {
        result = (first == second);
        if (result != 0) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    return good_counter;
}

int test_optional() {
    int good_counter = 0;
    int result;
    bool bool_result;
    try {
        good_counter++;
    }
    catch(const char* error_message) {std::cout<<error_message;}
    return good_counter;
}

