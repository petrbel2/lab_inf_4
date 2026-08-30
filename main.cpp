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

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    

    /* Площадка 3
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
    */

    /* Площадка 4
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int>* basic_seq = new LazySequence<int>(square_gen);
    basic_seq = basic_seq->Map(add_3);
    basic_seq = basic_seq->Where(if_even);
    std::cout<<basic_seq->Get(0)<<"\n";
    std::cout<<basic_seq->Get(1)<<"\n";
    std::cout<<basic_seq->Get(2)<<"\n";
    std::cout<<basic_seq->Get(3)<<"\n";
    std::cout<<basic_seq->Get(4)<<"\n";
    std::cout<<basic_seq->Get(5)<<"\n";
    */
    
    /*
    LazySequence<int>* empty_thing = new LazySequence<int>;
    empty_thing = empty_thing->Append(3);
    empty_thing = empty_thing->Prepend(2);
    empty_thing = empty_thing->Append(7);
    empty_thing = empty_thing->Prepend(1);
    empty_thing = empty_thing->InsertAt(6, 3);
    empty_thing = empty_thing->InsertAt(5, 3);
    empty_thing = empty_thing->InsertAt(4, 3);
    std::cout<<empty_thing->GetLength().get_finite()<<"\n";
    std::cout<<empty_thing->GetLength().get_infinite()<<"\n";
    std::cout<<empty_thing->GetLast()<<"\n";
    for (int i = 0; i < 7; i++) {
        std::cout<<empty_thing->Get(i)<<"\n";
    }
    
    /*
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int>* test_sequence = new LazySequence<int>(square_gen);
    std::cout<<test_sequence->Get(5)<<"\n";
    test_sequence = test_sequence->Prepend(3);
    std::cout<<test_sequence->Get(0)<<"\n";
    std::cout<<test_sequence->Get(5)<<"\n";
    delete test_sequence; 
    */   
    /*
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int>* basic_seq = new LazySequence<int>(square_gen);
    auto square_gen_2 = new SquareGenerator<int>();
    LazySequence<int>* test_sequence_2 = new LazySequence<int>(square_gen_2);
    basic_seq = basic_seq->Concat(test_sequence_2);
    Ordinal to_get(1, 5);
    std::cout<<basic_seq->GetLength().get_infinite()<<" "<<basic_seq->GetLength().get_finite()<<"\n";
    std::cout<<basic_seq->Get(5)<<"\n";
    std::cout<<basic_seq->Get(to_get);
    delete basic_seq;
    */
    /*
    auto square_gen = new SquareGenerator<int>();
    LazySequence<int>* basic_seq = new LazySequence<int>(square_gen);
    basic_seq = basic_seq->GetSubsequence(4, 10);
    for (int i = 0; i < 5; i++) {
        std::cout<<basic_seq->Get(i)<<"\n";
    }
    std::cout<<basic_seq->Get(0)<<"\n";
    delete basic_seq;
    */
    int choice;
    int buffer;
    
    test_LinkedList();
    test_Queue();
    test_Stack();
    test_Deque();
    test_Vector();
    std::cout<<"Enter queue length: ";
    std::cin>>buffer; 
    int* arr = new int[buffer];
    for (int i = 0; i < buffer; i++) {
        std::cout<<"Element: ";
        std::cin>>arr[i];
    }
    Queue<int> test_1(arr, buffer);
    delete[] arr;
    std::cout<<"Enter Stack length: ";
    std::cin>>buffer;
    int* arr1 = new int[buffer];
    for (int i = 0; i < buffer; i++) {
        std::cout<<"Element: ";
        std::cin>>arr1[i];
    }
    Stack<int> test_2(arr1, buffer);
    delete[] arr1;
    std::cout<<"Enter Deque length: ";
    std::cin>>buffer;
    int* arr2 = new int[buffer];
    for (int i = 0; i < buffer; i++) {
        std::cout<<"Element: ";
        std::cin>>arr2[i];
    }
    Deque<int> test_3(arr2, buffer);
    delete[] arr2;
        std::cout<<"Enter vector length: ";
    std::cin>>buffer;
    int* arr4 = new int[buffer];
    for (int i = 0; i < buffer; i++) {
        std::cout<<"Element: ";
        std::cin>>arr4[i];
    }
    Vector<int> test_4(arr4, buffer);
    delete[] arr4;
    printf(" [1] Get Queue length\n");
    printf(" [2] Get Steque length\n");
    printf(" [3] Get Deque length\n");
    printf(" [4] Append Queue element\n");
    printf(" [5] Append Steque element\n");
    printf(" [6] Append Deque element\n");
    printf(" [7] Prepend Deque element\n");
    printf(" [8] Get Queue element\n");
    printf(" [9] Get Steque element\n");
    printf(" [10] Get Deque element\n");
    printf(" [11] Get Vector length\n");
    printf(" [12] Get Vector norm\n");
    printf(" [13] Sum vectors\n");
    printf(" [14] Subtract vectors\n");
    printf(" [15] Multiply vectors\n");
    printf(" [16] Multiply vector \n");
    printf(" [0] Exit\n");
    printf("----------------------------\n");
    while (1) {
        
        printf("Choose: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: введено не число.\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                std::cout<<test_1.GetLength()<<"\n";
                break;
            case 2:
                std::cout<<test_2.GetLength()<<"\n";
                break;
            case 3:
                std::cout<<test_3.GetLength()<<"\n";
                break;
            case 4:
                std::cout<<"New element: ";
                std::cin>>buffer;
                test_1.Append(buffer);
                clear_input_buffer();
                break;
            case 5:
                std::cout<<"New element: ";
                std::cin>>buffer;
                test_2.Append(buffer);
                clear_input_buffer();
                break;
            case 6:
                std::cout<<"New element: ";
                std::cin>>buffer;
                test_3.Append(buffer);
                clear_input_buffer();
                break;
            case 7:
                std::cout<<"New element: ";
                std::cin>>buffer;
                test_3.Prepend(buffer);
                clear_input_buffer();
                break;
            case 8:
                std::cout<<test_1.Pop()<<"\n";
                break;
            case 9:
                std::cout<<test_2.Pop()<<"\n";
                break;
            case 10:
                std::cout<<test_3.PopFront()<<"\n";
                break;
            case 11:
                std::cout<<test_4.GetLength()<<"\n";
                break;
            case 12:
                std::cout<<test_4.vector_norm()<<"\n";
                break;
            case 13:
                {
                std::cout<<"Length: ";
                std::cin>>buffer;
                int* arr3 = new int[buffer];
                for (int i = 0; i < buffer; i++) {
                    std::cout<<"Element: ";
                    std::cin>>arr3[i];
                }
                Vector<int> test_7(arr3, buffer);
                delete[] arr3;
                test_4 = test_4 + test_7;
                break;
                }
            case 14:
                {
                std::cout<<"Length: ";
                std::cin>>buffer;
                int* arr4 = new int[buffer];
                for (int i = 0; i < buffer; i++) {
                    std::cout<<"Element: ";
                    std::cin>>arr4[i];
                }
                Vector<int> test_5(arr4, buffer);
                delete[] arr4;
                test_4 = test_4 - test_5;
                break;
                }
            case 15:
                {
                std::cout<<"Length: ";
                std::cin>>buffer;
                int* arr5 = new int[buffer];
                for (int i = 0; i < buffer; i++) {
                    std::cout<<"Element: ";
                    std::cin>>arr5[i];
                }
                Vector<int> test_6(arr5, buffer);
                delete[] arr5;
                int multiresult = test_4 * test_6;
                std::cout<<multiresult<<"\n";
                break;
                }
            case 16:
                {
                std::cout<<"Skalar: ";
                std::cin>>buffer;
                test_4 = test_4 * buffer;
                break;
                }
            default:
                std::cout<<"Wrong number.\n";
                break;
            case 0:
                std::cout<<"Leaving\n";
                return 0;
        }
    }
}


