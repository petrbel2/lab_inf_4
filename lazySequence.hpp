#ifndef LAZYSEQUENCE_H 
#define LAZYSEQUENCE_H
#include "sequence.hpp"
#include "generator.hpp"
#include "cache.hpp"

template <typename data_type>
class LazySequence: public Sequence<data_type>
{
private:
    Ordinal length;
    int gen_pos;
    Generator<data_type>* generator;
    Cache<data_type> cache;
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
        return this->Get(0);
    }

    data_type GetLast() {
        if (length.get_finite() == 0) {
            return -1000;
        }
        else {
            if (cache.contains(length)) {
                return cache.get(length);
            }
            else {
                return generator->get(length);
            } 
        }
    }
 
    data_type Get(int index) {
        if (cache.contains(index)) {
            return cache.get(index);
        }
        else {
            while(gen_pos < index) {
                cache.push(generator->get_next());
                gen_pos++;
            }
            data_type result = generator->get_next();
            cache.push(result);
            gen_pos++;
            return result;
        }
        // создать ошибку для перескока
    }

    //LazySequence <data_type>* GetSubsequence(int startIndex, int endIndex) {
    //}

    int GetMaterializedCount() const{
        return cache.get_last_index();
    }

    LazySequence<data_type>* Append(data_type item) {
        length++;
        generator = new AppendGenerator(length, item, generator);
        return this;
    }

    Sequence<data_type>* Prepend(data_type item) {
        if (length.get_infinite() == 0) {
        length++;
        }
        generator = new PrependGenerator(length, item, generator);
        return this;
    }

    LazySequence<data_type>* InsertAt(data_type item, int index) {
        Ordinal new_index(0, index);
        if (length.get_infinite() == 0) {
        length++;
        }
        generator = new InsertGenerator(length, new_index, item, generator);
        return this;
    }

    LazySequence<data_type>* Remove(int index) {
        Ordinal new_index(0, index);
        if (length.get_infinite() == 0) {
        length--;
        }
        generator = new RemoveGenerator(length, new_index, generator);
        return this;
    }

    LazySequence<data_type>* Map(data_type(*func)(data_type)) {
        generator = new MapGenerator(length, func, generator);
        return this;
    }

    LazySequence<data_type>* Where(bool(*func)(data_type)) {
        generator = new WhereGenerator(length, func, generator);
        return this;
    }

    //LazySequence<data_type>* Concat(LazySequence <data_type> *list);

};

#endif