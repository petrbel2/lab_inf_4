#include <iostream>
#include "lazySequence.hpp"
#include "tests.hpp"

int add_3(int arg) {
        return arg + 3;
    }

bool if_even(int arg) {
    if (arg % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    // Площадка 1
    int big_counter; 
    big_counter = test_cache();
    std::cout<<"Cache testing. successful tests "<<big_counter<<" out of 8\n";
    big_counter = test_ordinal();
    std::cout<<"Ordinal testing. successful tests "<<big_counter<<" out of 8\n";
    big_counter = test_optional();
    std::cout<<"Optional testing. successful tests "<<big_counter<<" out of 1\n";
    big_counter = test_array();
    std::cout<<"dynamicArray testing. successful tests "<<big_counter<<" out of 8\n";
    big_counter = test_square_generator();
    std::cout<<"SquareGenerator testing. successful tests "<<big_counter<<" out of 4\n";
    big_counter = test_fibonaccy_generator();
    std::cout<<"FibonaccyGenerator testing. successful tests "<<big_counter<<" out of 4\n";
    
    
    /* Площадка 2
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int> basic_seq(square_gen);

    std::cout<<basic_seq.GetLength().get_infinite()<<" ";
    std::cout<<basic_seq.GetLength().get_finite()<<"\n";
    std::cout<<basic_seq.Get(0)<<"\n";
    std::cout<<basic_seq.Get(1)<<"\n";
    std::cout<<basic_seq.Get(2)<<"\n";
    std::cout<<basic_seq.Get(3)<<"\n";
    std::cout<<basic_seq.Get(4)<<"\n";
    std::cout<<basic_seq.Get(5)<<"\n";
    */

    // Площадка 3
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int>* basic_seq = new LazySequence<int>(square_gen);
    basic_seq = basic_seq->Append(90);
    basic_seq = basic_seq->Prepend(40);
    basic_seq = basic_seq->InsertAt(60, 3);

    std::cout<<basic_seq->GetLast()<<"\n";
    std::cout<<basic_seq->GetFirst()<<"\n";
    std::cout<<basic_seq->Get(3)<<"\n";
    std::cout<<basic_seq->Get(3)<<"\n";
    std::cout<<basic_seq->Get(0)<<"\n";
    std::cout<<basic_seq->Get(1)<<"\n";
    std::cout<<basic_seq->Get(4)<<"\n";
    std::cout<<basic_seq->Get(5)<<"\n";
    delete basic_seq;

    /* Площадка 4
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int> test_sequence(square_gen);
    test_sequence.Map(add_3);
    test_sequence.Where(if_even);
    std::cout<<test_sequence.Get(0)<<"\n";
    std::cout<<test_sequence.Get(1)<<"\n";
    std::cout<<test_sequence.Get(2)<<"\n";
    std::cout<<test_sequence.Get(3)<<"\n";
    std::cout<<test_sequence.Get(4)<<"\n";
    std::cout<<test_sequence.Get(5)<<"\n";
    /*
    LazySequence<int> empty_thing;
    empty_thing.Append(3);
    empty_thing.Prepend(2);
    empty_thing.Append(7);
    empty_thing.Prepend(1);
    empty_thing.InsertAt(6, 3);
    empty_thing.InsertAt(5, 3);
    empty_thing.InsertAt(4, 3);
    std::cout<<empty_thing.GetLength().get_finite()<<"\n";
    std::cout<<empty_thing.GetLength().get_infinite()<<"\n";
    //std::cout<<empty_thing.GetLast();
    for (int i = 0; i < 7; i++) {
        std::cout<<empty_thing.Get(i)<<"\n";
    }
    */
    /*
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int>* test_sequence = new LazySequence<int>(square_gen);
    std::cout<<test_sequence->Get(5)<<"\n";
    test_sequence = test_sequence->Prepend(3);
    std::cout<<test_sequence->Get(0)<<"\n";
    std::cout<<test_sequence->Get(5)<<"\n";
    delete test_sequence; 
    */   
}


