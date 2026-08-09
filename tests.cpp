#include <iostream>
#include "lazySequence.hpp"
#include "tests.hpp"

int test_cache() {
    Cache<int> t_cache(10);
    int good_counter = 0;
    int result;
    bool bool_result;
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
        bool_result = t_cache.is_empty();
        if (not bool_result) {
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
        bool_result = t_cache.is_empty();
        if (bool_result) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    try {
        int result = t_cache.get(0);
        if (result != 5) {
            throw "Shit!";
        }
        good_counter++;
    }
    catch(const char* error_message) {
        std::cout<<error_message;
    }
    try {
        int result = t_cache.get(0);
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

