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
    LazySequence(): length(0, 0), gen_pos(0, 0), generator(new EmptyGenerator<data_type>()), cache(10) {}
    LazySequence(Generator<data_type>* gen): length(gen->get_length()), gen_pos(0, 0), generator(gen), cache(10) {}
    LazySequence (data_type* items, int count): length(0, count), gen_pos(0, 0), generator(new EmptyGenerator<data_type>()), cache(10) {
        Generator<data_type>* old_generator;
        for (int i = 0; i < count; i++) {
            old_generator = generator;
            generator = new AppendGenerator(Ordinal(0, i + 1), items[i], generator);
            delete old_generator;
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
        if (length.get_finite() == 0) {
            throw std::logic_error("Sequence doesn't have a last element");
        }      
        return this->Get(Ordinal(length.get_infinite(), length.get_finite() - 1));
    }
 
    data_type Get(int index) {
        if (index < 0) {
            throw std::logic_error("Index below zero");
        }
        if (length.get_finite() <= index and length.get_infinite() == 0) {
            throw std::logic_error("Index greater than length");
        }
        if (cache.contains(index)) {
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
        if (length <= index) {
            throw std::logic_error("Index greater than length");
        }
        if (cache.contains(index)) {
            return cache.get(index);
        }
        if (index < gen_pos) {
            throw std::logic_error("Index passed and deleted from cache");
        }
        if (gen_pos.get_infinite() < index.get_infinite()) {
            data_type result = generator->get(index);
            return result;
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

    Ordinal GetMaterializedCount() const{
        return gen_pos;
    }

    LazySequence<data_type>* Append(data_type item) {
        length++;
        return new LazySequence<data_type>(new AppendGenerator(length, item, generator->clone()));
    }
    
    LazySequence<data_type>* Prepend(data_type item) {
        if (length.get_infinite() == 0) {
        length++;
        }
        return new LazySequence<data_type>(new PrependGenerator(length, item, generator->clone()));
    }

    LazySequence<data_type>* InsertAt(data_type item, int index) {
        Ordinal new_index(0, index);
        if (length.get_infinite() == 0) {
        length++;
        }
        return new LazySequence<data_type>(new InsertGenerator(length, index, item, generator->clone()));
    }

    LazySequence<data_type>* InsertAt(data_type item, Ordinal index) {
        if (length.get_infinite() == index.get_infinite()) {
        length++;
        }
        return new LazySequence<data_type>(new InsertGenerator(length, index, item, generator->clone()));
    }

    LazySequence<data_type>* Remove(int index) {
        Ordinal new_index(0, index);
        if (length.get_infinite() == 0) {
        length--;
        }
        return new LazySequence<data_type>(new RemoveGenerator(length, index, generator->clone()));
    }

    LazySequence<data_type>* Remove(Ordinal index) {
        if (length.get_infinite() == index.get_infinite()) {
        length--;
        }
        return new LazySequence<data_type>(new RemoveGenerator(length, index, generator->clone()));
    }

    LazySequence<data_type>* Map(data_type(*func)(data_type)) {
        return new LazySequence<data_type>(new MapGenerator(length, func, generator->clone()));
    }

    LazySequence<data_type>* Where(bool(*func)(data_type)) {
        return new LazySequence<data_type>(new WhereGenerator(length, func, generator->clone()));
    }

    data_type Reduce(data_type(*func)(data_type, data_type)) {
        if (length.get_infinite() != 0) {
            throw std::logic_error("Can't reduce infinite sequence");
        }
        LazySequence<data_type>* copy_seq = this->Clone();
        data_type arg = func(copy_seq->Get(0), copy_seq->Get(1));
        for(int i  = 2; i < length.get_finite(); i++) {
            arg = func(arg, copy_seq->Get(i));
        }
        delete copy_seq;
        return arg;
    }
    
    LazySequence<data_type>* Concat(LazySequence <data_type> *list) {
        return new LazySequence<data_type>(new ConcatGenerator(length, list, generator->clone()));        
    }

    LazySequence <data_type>* GetSubsequence(int startIndex, int endIndex) {
        if (endIndex <= startIndex or length < Ordinal(0, endIndex)) {
            throw std::logic_error("Incorrect indexes");
        }
        return new LazySequence<data_type>(new SubsequenceGenerator(Ordinal(0, startIndex), Ordinal(0, endIndex), generator->clone()));
    }

    LazySequence <data_type>* GetSubsequence(Ordinal startIndex, Ordinal endIndex) {
        if (endIndex <= startIndex or length < endIndex) {
            throw std::logic_error("Incorrect indexes");
        }
        return new LazySequence<data_type>(new SubsequenceGenerator(startIndex, endIndex, generator->clone()));
    }

    LazySequence<data_type>* Clone() {
        return new LazySequence<data_type>(generator->clone());
    }

    ~LazySequence() {
        delete generator;
    }
};

#endif