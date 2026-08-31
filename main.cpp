#include <iostream>
#include "lazySequence.hpp"
#include "tests.hpp"
#include "stream.hpp"
#include "onlineStatistics.hpp"
#include <iomanip>
//#include <cstdio>


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

int sum_reduce(int a, int b) {
    return a + b;
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int deserialize_int(const std::string &text) {
    return std::stoi(text);
}

std::string serialize_int(const int &text) {
    return std::to_string(text);
}

void print_stats(const OnlineStatistics<int> &stats) {
    std::cout << "count=" << stats.get_count()
              << " sum=" << stats.get_sum()
              << " mean=" << std::fixed << std::setprecision(2) << stats.get_mean()
              << " min=" << stats.get_min()
              << " max=" << stats.get_max()
              << " median=" << stats.get_median() << '\n';
}

void process_stream(ReadOnlyStream<int> &stream) {
    OnlineStatistics<int> stats;
    stream.open();
    while (!stream.is_end_of_stream()) {
        int value = stream.read();
        stats.add(value);
        std::cout << "read " << value << " -> ";
        print_stats(stats);
    }

    stream.close();
}

void run_file_stream_mode() {
    std::string path;
    std::cout << "File path with one integer per line: ";
    //clear_input_line();
    std::getline(std::cin, path);

    if (path.empty()) {
        throw std::invalid_argument("File path cannot be empty");
    }

    FileReadStream<int> stream(path, deserialize_int);
    process_stream(stream);
}

void run_file_write_stream_mode() {
    std::string path;
    std::cout << "File path with one integer per line: ";
    //clear_input_line();
    std::getline(std::cin, path);

    if (path.empty()) {
        throw std::invalid_argument("File path cannot be empty");
    }

    FileWriteStream<int> stream(path, serialize_int);
    stream.open();
    int flag = 1;
    int data;
    while (flag) {
        std::cout<<"Enter number\n";
        std::cin>>data;
        stream.write(data);
        std::cout<<"Enter 0 to stop\n";
        std::cin>>flag;
    }
    stream.close();
}

void run_tests() {
    int total_counter = 0; 
    int big_counter; 
    big_counter = test_cache();
    total_counter += big_counter;
    std::cout<<"Cache testing. successful tests "<<big_counter<<" out of 8\n";
    big_counter = test_ordinal();
    total_counter += big_counter;
    std::cout<<"Ordinal testing. successful tests "<<big_counter<<" out of 8\n";
    big_counter = test_optional();
    total_counter += big_counter;
    std::cout<<"Optional testing. successful tests "<<big_counter<<" out of 1\n";
    big_counter = test_array();
    total_counter += big_counter;
    std::cout<<"dynamicArray testing. successful tests "<<big_counter<<" out of 8\n";
    big_counter = test_square_generator();
    total_counter += big_counter;
    std::cout<<"SquareGenerator testing. successful tests "<<big_counter<<" out of 4\n";
    big_counter = test_fibonaccy_generator();
    total_counter += big_counter;
    std::cout<<"FibonaccyGenerator testing. successful tests "<<big_counter<<" out of 4\n";
    big_counter = test_append_generator();
    total_counter += big_counter;
    std::cout<<"AppendGenerator testing. successful tests "<<big_counter<<" out of 4\n";
    big_counter = test_prepend_generator();
    total_counter += big_counter;
    std::cout<<"PrependGenerator testing. successful tests "<<big_counter<<" out of 3\n";
    big_counter = test_insert_generator();
    total_counter += big_counter;
    std::cout<<"InsertGenerator testing. successful tests "<<big_counter<<" out of 3\n";
    big_counter = test_remove_generator();
    total_counter += big_counter;
    std::cout<<"RemoveGenerator testing. successful tests "<<big_counter<<" out of 3\n";
    big_counter = test_map_generator();
    total_counter += big_counter;
    std::cout<<"MapGenerator testing. successful tests "<<big_counter<<" out of 3\n";
    big_counter = test_where_generator();
    total_counter += big_counter;
    std::cout<<"WhereGenerator testing. successful tests "<<big_counter<<" out of 3\n";
    big_counter = test_subseq_generator();
    total_counter += big_counter;
    std::cout<<"SubsequenceGenerator testing. successful tests "<<big_counter<<" out of 3\n";
    big_counter = test_concat_generator();
    total_counter += big_counter;
    std::cout<<"ConcatGenerator testing. successful tests "<<big_counter<<" out of 4\n";
    big_counter = test_generators_together();
    total_counter += big_counter;
    std::cout<<"Multiple generators testing. successful tests "<<big_counter<<" out of 1\n";
    big_counter = test_lazyseqreadstream();
    total_counter += big_counter;
    std::cout<<"LazySequenceReadStream testing. successful tests "<<big_counter<<" out of 12\n";
    big_counter = test_seqreadstream();
    total_counter += big_counter;
    std::cout<<"SequenceReadStream testing. successful tests "<<big_counter<<" out of 8\n";
    big_counter = test_seqwritestream();
    total_counter += big_counter;
    std::cout<<"SequenceWriteStream testing. successful tests "<<big_counter<<" out of 5\n";
    std::cout<<"Total successful tests: "<<total_counter<<" out of 85\n";
    std::cout<<"Failed tests: "<<85 - total_counter<<"\n";
}

int main() {  
    run_file_stream_mode();
    //run_file_write_stream_mode();
   // run_tests();
    
    int choice;
    int buffer;
    int index;
    
    auto gen = new SquareGenerator<int>();
    LazySequence<int>* seq = new LazySequence<int>(gen);
    
    std::cout << " [1] Get Length\n";
    std::cout << " [2] Get First\n";
    std::cout << " [3] Get Last\n";
    std::cout << " [4] Get at index\n";
    std::cout << " [5] Append\n";
    std::cout << " [6] Prepend\n";
    std::cout << " [7] Insert at index\n";
    std::cout << " [8] Remove at index\n";
    std::cout << " [9] Map\n";
    std::cout << " [10] Where\n";
    std::cout << " [11] Reduce\n";
    std::cout << " [12] Concat\n";
    std::cout << " [13] Get Subsequence\n";
    std::cout << " [0] Exit\n";
    std::cout << "----------------------------\n";
    
    while (true) {
        std::cout << "Choose: ";
        if (!(std::cin >> choice)) {
            std::cout << "Error: not a number.\n";
            clear_input_buffer();
            continue;
        }
        
        switch (choice) {
            case 1:
                std::cout<< "Length: " <<seq->GetLength().get_infinite()<<", "<<seq->GetLength().get_finite() << "\n";
                break;
            case 2:
                try {
                    std::cout<<"First: "<<seq->GetFirst()<<"\n";
                } catch (const std::exception& e) {
                    std::cout<<"Error: "<<e.what()<<"\n";
                }
                break;
            case 3:
                try {
                    std::cout<<"Last: "<<seq->GetLast()<<"\n";
                } catch (const std::exception& e) {
                    std::cout<<"Error: "<<e.what()<<"\n";
                }
                break;
            case 4:
                std::cout<<"Index: ";
                std::cin>>index;
                try {
                    std::cout<<"Element: "<<seq->Get(index)<<"\n";
                } catch (const std::exception& e) {
                    std::cout<<"Error: "<<e.what()<<"\n";
                }
                break;
            case 5:
                std::cout<<"New element: ";
                std::cin>>buffer;
                seq = seq->Append(buffer);
                break;
            case 6:
                std::cout<<"New element: ";
                std::cin>>buffer;
                seq = seq->Prepend(buffer);
                break;
            case 7:
                std::cout<<"Index: ";
                std::cin>>index;
                std::cout<<"New element: ";
                std::cin>>buffer;
                seq = seq->InsertAt(buffer, index);
                break;
            case 8:
                std::cout<<"Index: ";
                std::cin>>index;
                seq = seq->Remove(index);
                break;
            case 9:
                seq = seq->Map(add_3);
                std::cout<<"Mapped sequence\n";
                break;
            case 10:
                seq = seq->Where(if_even);
                std::cout<<"Filtered sequence\n";
                break;
            case 11:
                try {
                    int result = seq->Reduce(sum_reduce);
                    std::cout<<"Reduced result: "<<result<<"\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            case 12:
                std::cout<<"Concat length: ";
                std::cin>>buffer;
                {
                    auto concat_gen = new SquareGenerator<int>();
                    LazySequence<int>* concat_seq = new LazySequence<int>(concat_gen);
                    for (int i = 0; i < buffer; i++) {
                        int val;
                        std::cout<<"Element: ";
                        std::cin>>val;
                        concat_seq = concat_seq->Append(val);
                    }
                    seq = seq->Concat(concat_seq);
                    delete concat_seq;
                }
                break;
            case 13:
                {
                    int start_idx, end_idx;
                    std::cout<<"Start index: ";
                    std::cin>>start_idx;
                    std::cout<<"End index: ";
                    std::cin>>end_idx;
                    try {
                        LazySequence<int>* subseq = seq->GetSubsequence(start_idx, end_idx);
                        std::cout<<"Subsequence length: "<<subseq->GetLength().get_infinite()<<", "<<subseq->GetLength().get_finite()<<"\n";
                        delete subseq;
                    } catch (const std::exception& e) {
                        std::cout<<"Error: " <<e.what()<<"\n";
                    }
                }
                break;
            case 0:
                std::cout<<"Leaving\n";
                delete seq;
                return 0;
            default:
                std::cout<<"Wrong number.\n";
                break;
        }
    }
}



