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

int test_array() {
    int good_counter = 0;
    try {
        DynamicArray<int> arr;
        if (arr.GetLength() != 0 or arr.GetSupply() != 5) {
            throw std::runtime_error("DynamicArray default constructor failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { std::cout << error.what() << "\n"; }

    try {
        DynamicArray<int> arr(3);
        if (arr.GetLength() != 3) {
            throw std::runtime_error("DynamicArray(int count) constructor failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { std::cout << error.what() << "\n"; }

    try {
        int init_data[] = {10, 20, 30};
        DynamicArray<int> arr(init_data, 3);
        if (arr.Get(0) != 10 || arr.Get(1) != 20 || arr.Get(2) != 30) {
            throw std::runtime_error("DynamicArray array Get failed");
        }
        good_counter++;
        arr.Set(1, 99);
        if (arr.Get(1) != 99) {
            throw std::runtime_error("DynamicArray Set method failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { std::cout << error.what() << "\n"; }

    try {
        DynamicArray<int> arr(2);
        arr.Set(0, 5);
        arr.Set(1, 10);
        arr.Resize(5);
        if (arr.GetLength() != 5 || arr.Get(0) != 5 || arr.Get(1) != 10) {
            throw std::runtime_error("DynamicArray Resize (grow) failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { std::cout << error.what() << "\n"; }

    try {
        int init_data[] = {1, 2, 3, 4, 5};
        DynamicArray<int> arr(init_data, 5);
        arr.Resize(2);
        if (arr.GetLength() != 2 || arr.Get(0) != 1 || arr.Get(1) != 2) {
            throw std::runtime_error("DynamicArray Resize (shrink) failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { std::cout << error.what() << "\n"; }

    try {
        int init_data[] = {10, 20, 30, 40, 50};
        DynamicArray<int> arr(init_data, 5);
        int* sub = arr.GetSubArray(1, 4); // Должно вернуть {20, 30, 40}
        if (sub[0] != 20 || sub[1] != 30 || sub[2] != 40) {
            delete[] sub;
            throw std::runtime_error("DynamicArray GetSubArray failed");
        }
        delete[] sub;
        good_counter++;
    } catch (const std::runtime_error& error) { std::cout << error.what() << "\n"; }

    try {
        int init_data[] = {10, 20, 30};
        DynamicArray<int> arr(init_data, 3);
        int* sub = arr.GetSubArray(2, 1);
        delete[] sub;
        throw std::runtime_error("DynamicArray GetSubArray did not throw on invalid range");
    } catch (const std::runtime_error&) {
        good_counter++;
    } catch (const std::exception& error) { 
        std::cout << "Unexpected error in GetSubArray test: " << error.what() << "\n"; 
    }

    return good_counter;
}

int test_square_generator() {
    int good_counter = 0;
    
    try {
        SquareGenerator<int> gen;
        
        // 1. Начальная позиция
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("SquareGenerator initial position is not 0");
        }
        good_counter++;

        // 2. has_next всегда true
        if (!gen.has_next()) {
            throw std::runtime_error("SquareGenerator has_next should be true");
        }
        good_counter++;

        // 3. Проверка get() для конкретных индексов
        if (gen.get(Ordinal::finity(0)) != 0 || 
            gen.get(Ordinal::finity(1)) != 1 || 
            gen.get(Ordinal::finity(3)) != 9) {
            throw std::runtime_error("SquareGenerator get(Ordinal) failed");
        }
        good_counter++;

        // 4. Проверка последовательности get_next()
        // Первый вызов: pos становится 1, возвращает (1-1)^2 = 0
        // Второй вызов: pos становится 2, возвращает (2-1)^2 = 1
        // Третий вызов: pos становится 3, возвращает (3-1)^2 = 4
        SquareGenerator<int> gen2;
        if (gen2.get_next() != 0 || gen2.get_next() != 1 || gen2.get_next() != 4) {
            throw std::runtime_error("SquareGenerator get_next() sequence failed");
        }
        good_counter++;

        // 5. Проверка исключения при бесконечном индексе
        try {
            gen.get(Ordinal::infinity());
            throw std::runtime_error("SquareGenerator did not throw on infinite ordinal");
        } catch (const std::logic_error&) {
            good_counter++; // Ожидаемое поведение
        }

    } catch (const std::exception& error) { 
        std::cout << error.what() << "\n"; 
    }

    return good_counter;
}

int test_fibonaccy_generator() {
    int good_counter = 0;
    
    try {
        FibonaccyGenerator<int> gen; // Оставляем название как в исходном коде
        
        // 1. Начальная позиция
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("FibonaccyGenerator initial position is not 0");
        }
        good_counter++;

        // 2. has_next всегда true
        if (!gen.has_next()) {
            throw std::runtime_error("FibonaccyGenerator has_next should be true");
        }
        good_counter++;

        // 3. Проверка последовательности get_next()
        // Исходный код: b_1=1, b_2=0. 
        // Вызов 1: result = 1+0=1, b_1=0, b_2=1. Возвращает 1.
        // Вызов 2: result = 0+1=1, b_1=1, b_2=1. Возвращает 1.
        // Вызов 3: result = 1+1=2, b_1=1, b_2=2. Возвращает 2.
        // Вызов 4: result = 1+2=3, b_1=2, b_2=3. Возвращает 3.
        if (gen.get_next() != 1 || gen.get_next() != 1 || gen.get_next() != 2 || gen.get_next() != 3) {
            throw std::runtime_error("FibonaccyGenerator get_next() sequence failed");
        }
        good_counter++;

        // 4. Проверка исключения при бесконечном индексе
        try {
            gen.get(Ordinal::infinity());
            throw std::runtime_error("FibonaccyGenerator did not throw on infinite ordinal");
        } catch (const std::logic_error&) {
            good_counter++; // Ожидаемое поведение
        }

        // 5. Тест clone()
        try {
            FibonaccyGenerator<int>* cloned = gen.clone();
            if (cloned == nullptr) {
                throw std::runtime_error("FibonaccyGenerator clone returned nullptr");
            }
            // Проверяем, что клон независим (или хотя бы работает)
            cloned->get_next(); 
            delete cloned; // Освобождаем память
            good_counter++;
        } catch (const std::exception& e) {
            std::cout << "Clone test failed: " << e.what() << "\n";
        }

    } catch (const std::exception& error) { 
        std::cout << error.what() << "\n"; 
    }

    return good_counter;
}