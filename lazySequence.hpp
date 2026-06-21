#ifndef LAZYSEQUENCE_H 
#define LAZYSEQUENCE_H
#include "sequence.hpp"
#include "omega.hpp"
#include "generator.hpp"
#include <functional>

template <typename data_type>
class LazySequence: public Sequence<data_type>
{
private:
    Omega length;
    Generator<data_type>* generator;
public:
    //LazySequence(): length(0), generator() {}
    LazySequence(Generator<data_type>* gen): length(0, 0), generator(gen) {}
    //LazySequence (data_type* items, int count);
    //LazySequence (Sequence<data_type>* seq);
    //LazySequence (data_type(*)(Sequence<data_type>*), Sequence<data_type>);
    //LazySequence (std::function<data_type>(Sequence<data_type>*), Sequence<data_type>*);
    Omega GetLength() const{
        return length;
    }

    data_type GetFirst() {
    }

    data_type GetLast() {
    }

    data_type Get(int index) {

    }

    LazySequence <data_type>* GetSubsequence(int startIndex, int endIndex) {

    }

    //size_t GetMaterializedCount() const;

    //Sequence<data_type>* Append(data_type item);

    //Sequence<data_type>*Prepend(data_type item);

    //LazySequence <data_type>*InsertAt(data_type item, int index);

    //LazySequence <data_type>* Concat(LazySequence <data_type> *list);

    ~LazySequence() {
        delete[] generator;
    }
};

#endif