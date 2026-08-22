#include <iostream>
#include "lazySequence.hpp"
#include "tests.hpp"

int test_cache() {
    Cache<int> t_cache(10);
    int good_counter = 0;
    int result;
    try {
        result = t_cache.get_capacity();
        if (result != 10) {throw std::runtime_error("Incorrect cache capacity in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = t_cache.get_count();
        if (result != 0) {throw std::runtime_error("Incorrect get_count function result in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = t_cache.is_empty();
        if (not result) {throw std::runtime_error("Incorrect is_empty function result in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        t_cache.push(5);
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = t_cache.get_count();
        if (result != 1) {throw std::runtime_error("Incorrect get_count function result in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = t_cache.is_empty();
        if (result) {throw std::runtime_error("Incorrect is_empty function result in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = t_cache.get(0);
        if (result != 5) {throw std::runtime_error("Invalide value got from get(int) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    Ordinal number(0, 0);
    try {
        result = t_cache.get(number);
        if (result != 5) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
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
        if (result != 1) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = first.is_finite();
        if (result != 0) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = second.is_infinite();
        if (result != 0) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = second.is_finite();
        if (result != 1) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = first.get_infinite();
        if (result != 1) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = second.get_finite();
        if (result != 0) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = (first == third);
        if (result != 1) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = (first == second);
        if (result != 0) {throw std::runtime_error("Invalide value got from get(Ordinal) function in test_cache!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    return good_counter;
}

int test_optional() {
    int good_counter = 0;
    int result;
    bool bool_result;
    try {
        good_counter++;
    }
    catch(const std::runtime_error& error) {
        std::cout<<error.what();
    }
    return good_counter;
}

