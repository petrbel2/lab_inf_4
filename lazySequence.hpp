#ifndef LAZYSEQUENCE_H 
#define LAZYSEQUENCE_H
#include "sequence.hpp"

template <typename data_type>
class LazySequence: public Sequence<data_type>
{
private:
    LinkedList<data_type> list;
public:
    LazySequence(): list() {}
    LazySequence (data_type* items, int count);
    LazySequence (Sequence<data_type>* seq);
    LazySequence (data_type(*)(Sequence<data_type>*), Sequence<data_type>)
    LazySequence (std::function<data_type>(Sequence<data_type>*), Sequence<data_type>*)
    Cardinal GetLength() const{
    }

    data_type GetFirst() {
    }

    data_type GetLast() {
    }

    data_type Get(int index) {

    }

    LazySequence <data_type>* GetSubsequence(int startIndex, int endIndex) {

    }

    size_t GetMaterializedCount() const;

    Sequence<T>* Append(T item);

    Sequence<T>*Prepend(T item);

    LazySequence <T>*InsertAt(T item, int index);

    LazySequence <T>* Concat(LazySequence <T> *list);
};

#endif