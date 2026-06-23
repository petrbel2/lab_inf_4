#ifndef LAZYSEQUENCE_H 
#define LAZYSEQUENCE_H
#include "sequence.hpp"
#include "ordinal.hpp"
#include "generator.hpp"
#include "cashe.hpp"
#include <functional>

template <typename data_type>
class LazySequence: public Sequence<data_type>
{
private:
    Omega length;
    int gen_pos;
    Generator<data_type>* generator;
    Cache<data_type>* cache;
public:
    //LazySequence(): length(0), generator() {}
    LazySequence(Generator<data_type>* gen): length(1, 0), gen_pos(0), generator(gen), cache(10) {}
    //LazySequence (data_type* items, int count);
    //LazySequence (Sequence<data_type>* seq);
    //LazySequence (data_type(*)(Sequence<data_type>*), Sequence<data_type>);
    //LazySequence (std::function<data_type>(Sequence<data_type>*), Sequence<data_type>*);
    Ordinal GetLength() const{
        return length;
    }

    data_type GetFirst() {
    }

    data_type GetLast() {
    }

    data_type Get(int index) {
        if (cache->contains(index)) {
            return cache->get(index);
        }
        else {
            while(gen_pos < (index - 1)) {
                cache->push(generator->get_next());
                gen_pos++;
            }
            data_type result = generator->get_next();
            cache->push(result);
            return result;
        }
    }

    LazySequence <data_type>* GetSubsequence(int startIndex, int endIndex) {

    }

    //size_t GetMaterializedCount() const;

    //Sequence<data_type>* Append(data_type item);

    //Sequence<data_type>* Prepend(data_type item);

    //LazySequence<data_type>* InsertAt(data_type item, int index);

    //LazySequence<data_type>* Concat(LazySequence <data_type> *list);

};

#endif