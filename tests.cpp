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
        if (result != 1) {throw std::runtime_error("Invalide value got from is_infinite in test_ordinal!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = first.is_finite();
        if (result != 0) {throw std::runtime_error("Invalide value got from is_infinite in test_ordinal!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = second.is_infinite();
        if (result != 0) {throw std::runtime_error("Invalide value got from is_infinite in test_ordinal!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = second.is_finite();
        if (result != 1) {throw std::runtime_error("Invalide value got from is_finite in test_ordinal!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = first.get_infinite();
        if (result != 1) {throw std::runtime_error("Invalide value got from get_infinite in test_ordinal\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = second.get_finite();
        if (result != 0) {throw std::runtime_error("Invalide value got from get_finite in test_ordinal!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = (first == third);
        if (result != 1) {throw std::runtime_error("Invalide value got from == in test_ordinal!\n");}
        good_counter++;
    }
    catch(const std::runtime_error& error) {std::cout<<error.what();}
    try {
        result = (first == second);
        if (result != 0) {throw std::runtime_error("Invalide value got from == in test_ordinal!\n");}
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
    int init_data[] = {10, 20, 30};
    DynamicArray<int> arr(init_data, 3);
    try {
        if (arr.Get(0) != 10 || arr.Get(1) != 20 || arr.Get(2) != 30) {
            throw std::runtime_error("DynamicArray array Get failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { std::cout << error.what() << "\n"; }
    try {
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
        std::cout << "Unexpected error in GetSubArray test in dynamicArray: " << error.what() << "\n"; 
    }

    return good_counter;
}

int test_square_generator() {
    int good_counter = 0;
    SquareGenerator<int> gen;
    try {        
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("SquareGenerator get_finite incorrect result");
        }
        good_counter++;
        } 
    catch (const std::runtime_error& error) { 
            std::cout << error.what() << "\n"; 
        }
    try {
        if (!gen.has_next()) {
            throw std::runtime_error("SquareGenerator has_next incorrect result");
        }
        good_counter++;
        }
    catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
        }
    try {
        if (gen.get(Ordinal::finity(0)) != 0 or
            gen.get(Ordinal::finity(1)) != 1 or
            gen.get(Ordinal::finity(3)) != 9) {
            throw std::runtime_error("SquareGenerator get(Ordinal) failed");
        }
        good_counter++;
    } 
    catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        SquareGenerator<int> gen2;
        if (gen2.get_next() != 0 || gen2.get_next() != 1 || gen2.get_next() != 4) {
            throw std::runtime_error("SquareGenerator get_next() sequence failed");
        }
        good_counter++;
    } 
    catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }

    return good_counter;
}

int test_fibonaccy_generator() {
    int good_counter = 0;
    FibonaccyGenerator<int> gen;
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("FibonaccyGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (!gen.has_next()) {
            throw std::runtime_error("FibonaccyGenerator has_next should be true");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 1 or gen.get_next() != 1 or gen.get_next() != 2 or gen.get_next() != 3) {
            throw std::runtime_error("FibonaccyGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }

    try {
        FibonaccyGenerator<int>* cloned = gen.clone();
        if (cloned == nullptr) {
            throw std::runtime_error("FibonaccyGenerator clone returned nullptr");
        }
        cloned->get_next(); 
        delete cloned; // Освобождаем память
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }

    return good_counter;
}

int double_val(int x) {
    return x * 2;
}

bool is_even(int x) {
    return x % 2 == 0;
}

int func_seq_test(Sequence<int>* seq) {
    return seq->GetLength().get_finite();
}

int test_append_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    AppendGenerator<int> gen(Ordinal(1, 1), 99, &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("AppendGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 0 or gen.get_next() != 1 or gen.get_next() != 4) {
            throw std::runtime_error("AppendGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get(Ordinal(0, 3)) != 9 or gen.get(Ordinal(1, 0)) != 99) {
            throw std::runtime_error("AppendGenerator get() failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        AppendGenerator<int>* cloned = gen.clone();
        if (cloned->get_next() != 0) {
            throw std::runtime_error("AppendGenerator clone get_next() failture");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}

int test_prepend_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    PrependGenerator<int> gen(Ordinal(1, 0), 99, &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("PrependGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 99 or gen.get_next() != 0 or gen.get_next() != 1 or gen.get_next() != 4) {
            throw std::runtime_error("PrependGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        PrependGenerator<int>* cloned = gen.clone();
        if (cloned->get_next() != 99) {
            throw std::runtime_error("PrependGenerator clone get_next() failture");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}

int test_insert_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    InsertGenerator<int> gen(Ordinal(1, 0), 3, 99, &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("InsertGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 0 or gen.get_next() != 1 or gen.get_next() != 4 or gen.get_next() != 99) {
            throw std::runtime_error("InsertGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        InsertGenerator<int>* cloned = gen.clone();
        if (cloned->get(Ordinal(0, 3)) != 99) {
            throw std::runtime_error("InsertGenerator clone get() failture");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}

int test_remove_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    RemoveGenerator<int> gen(Ordinal(1, 0), 1, &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("RemoveGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 0 or gen.get_next() != 4 or gen.get_next() != 9) {
            throw std::runtime_error("RemoveGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        RemoveGenerator<int>* cloned = gen.clone();
        if (cloned->get_next() != 0 or cloned->get_next() != 4 or cloned->get_next() != 9) {
            throw std::runtime_error("RemoveGenerator clone get_next() failture");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}

int test_map_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    MapGenerator<int> gen(Ordinal(1, 0), double_val, &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("MapGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 0 or gen.get_next() != 2 or gen.get_next() != 8 or gen.get_next() != 18) {
            throw std::runtime_error("MapGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        MapGenerator<int>* cloned = gen.clone();
        if (cloned->get_next() != 0 or cloned->get_next() != 2 or cloned->get_next() != 8 or cloned->get_next() != 18) {
            throw std::runtime_error("MapGenerator clone get_next() failture");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}

int test_where_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    WhereGenerator<int> gen(Ordinal(1, 0), is_even, &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("WhereGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 0 or gen.get_next() != 4 or gen.get_next() != 16 or gen.get_next() != 36) {
            throw std::runtime_error("WhereGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        WhereGenerator<int>* cloned = gen.clone();
        if (cloned->get_next() != 0 or cloned->get_next() != 4 or cloned->get_next() != 16 or cloned->get_next() != 36) {
            throw std::runtime_error("WhereGenerator clone get_next() failture");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}
/*
int test_function_generator() {
    int good_counter = 0;
    LazySequence<int> start_seq;
    try {
        FunctionGenerator<int> gen(func_seq_test, &start_seq);
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("FunctionGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    } catch (const std::exception& error) {
        std::cout << error.what() << "\n";
    }
    return good_counter;
}
*/
int test_subseq_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    SubsequenceGenerator<int> gen(Ordinal(0, 1), Ordinal(0, 4), &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("SubsequenceGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 1 or gen.get_next() != 4 or gen.get_next() != 9) {
            throw std::runtime_error("SubsequenceGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        SubsequenceGenerator<int>* cloned = gen.clone();
        if (cloned->get_next() != 1 or cloned->get_next() != 4 or cloned->get_next() != 9) {
            throw std::runtime_error("SubsequenceGenerator clone get_next() failture");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}

int test_concat_generator() {
    int good_counter = 0;
    SquareGenerator<int> base_gen;
    int init_data[] = {99, 100};
    LazySequence<int> concat_seq(init_data, 2);
    ConcatGenerator<int> gen(Ordinal::finity(2), &concat_seq, &base_gen);
    try {
        if (gen.position().get_finite() != 0) {
            throw std::runtime_error("ConcatGenerator initial position is not 0");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        if (gen.get_next() != 0 || gen.get_next() != 1 || gen.get_next() != 99 || gen.get_next() != 100) {
            throw std::runtime_error("ConcatGenerator get_next() sequence failed");
        }
        good_counter++;
    } catch (const std::runtime_error& error) { 
        std::cout << error.what() << "\n"; 
    }
    try {
        ConcatGenerator<int>* cloned = gen.clone();
        if (cloned == nullptr) {
            throw std::runtime_error("ConcatGenerator clone returned nullptr");
        }
        delete cloned;
        good_counter++;
    } catch (const std::exception& error) {
        std::cout << "Clone test failed: " << error.what() << "\n";
    }
    return good_counter;
}
