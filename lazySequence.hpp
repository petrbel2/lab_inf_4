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
    Ordinal gen_pos;
    Generator<data_type>* generator;
    Cache<data_type> cache;
public:
    LazySequence(): length(0, 0), gen_pos(0, 0), generator(), cache(10) {}
    LazySequence(Generator<data_type>* gen): length(1, 0), gen_pos(0, 0), generator(gen), cache(10) {}
    LazySequence (data_type* items, int count): length(0, count), gen_pos(0, 0), generator(), cache(10) {
        for (int i = 0; i < count; i++) {
            this->Append(items[i]);
        }
    }
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
        /*
        if (length.get_finite() == 0) {
            throw std::logic_error("Sequence doesn't have a last element");
        }
        else {
            if (cache.contains(Ordinal(length.get_infinite(), length.get_finite() - 1))) {
                return cache.get(Ordinal(length.get_infinite(), length.get_finite() - 1));
            }
            else {
                return generator->get(Ordinal(length.get_infinite(), length.get_finite() - 1));
            } 
        }
        */
       return this->Get(Ordinal(length.get_infinite(), length.get_finite() - 1));
    }
 
    data_type Get(int index) {
        if (length.get_finite() <= index and length.get_infinite() == 0) {
            throw std::logic_error("Index greater than length");
        }
        else if (cache.contains(index)) {
            return cache.get(index);
        }
        else if (Ordinal(0, index) < gen_pos) {
            throw std::logic_error("Index passed and deleted from cache");
        }
        else {
            while(gen_pos < Ordinal(0, index)) {
                cache.push(generator->get_next());
                gen_pos++;
            }
            data_type result = generator->get_next();
            cache.push(result);
            gen_pos++;
            return result;
        }
    }

    data_type Get(Ordinal index) {
        if (index.get_infinite() != 0) {
            throw std::logic_error("Index unreacheble");
        }
        else if (length.get_finite() <= index.get_finite() and length.get_infinite() == 0) {
            throw std::logic_error("Index greater than length");
        }
        else if (cache.contains(index)) {
            return cache.get(index);
        }
        else if (index < gen_pos) {
            throw std::logic_error("Index passed and deleted from cache");
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