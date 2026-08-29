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
    LazySequence(Generator<data_type>* gen): length(gen->get_length()), gen_pos(0, 0), generator(gen), cache(10) {}
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
    /*
    Generator<data_type>* GetGen() {
        return generator;
    }
    */
    
    

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
        if (length <= index) {
            throw std::logic_error("Index greater than length");
        }
        else if (cache.contains(index)) {
            return cache.get(index);
        }
        else if (index < gen_pos) {
            throw std::logic_error("Index passed and deleted from cache");
        }
        else if (gen_pos.get_infinite() < index.get_infinite()) {
            gen_pos = index;
            data_type result = generator->get(index);
            cache.push(result);
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

    //LazySequence <data_type>* GetSubsequence(int startIndex, int endIndex) {
    //}

    //int GetMaterializedCount() const{
    //    return cache.get_last_index();
    //}

    LazySequence<data_type>* Append(data_type item) {
        length++;
        return new LazySequence<data_type>(new AppendGenerator(length, item, generator->clone()));
    }
    /*
    Sequence<data_type>* Prepend(data_type item) {
        if (length.get_infinite() == 0) {
        length++;
        }
        Generator<data_type>* old_gen = generator;
        generator = new PrependGenerator(length, item, generator->clone());
        delete old_gen;
        return this;
    }
    */
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

    LazySequence<data_type>* Clone() {
        return new LazySequence<data_type>(generator->clone());
    }

    ~LazySequence() {
        delete generator;
    }
};

template <typename data_type>
class ConcatGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        Ordinal concat_start;
        LazySequence<data_type>* concat_seq;
        Generator<data_type>* base;
    public:
        ConcatGenerator(Ordinal length, LazySequence<data_type>* conc, Generator<data_type>* base_gen): length(length + conc.GetLength()), 
        pos(0, 0), concat_start(length), concat_seq(conc), base(base_gen) {}
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            return 0;
            //mistake
        }
        

        data_type get_next() {
            if (this->has_next()) {
                pos++;
                if (pos < Ordinal(concat_start.get_infinite(), concat_start.get_finite())) {
                    return base->get_next();
                }
                else {
                    return concat_seq->Get(Ordinal(pos.get_infinite() - concat_start.get_infinite(), pos.get_finite() - concat_start.get_finite()));
                }
            }
            else {
                throw std::runtime_error("No more elements in ConcatGenerator");
            }
        }

        ConcatGenerator* clone() const {
            return new ConcatGenerator(length, concat_seq->Clone(), base->clone());
        }
};

template <typename data_type>
class ConcatGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        Ordinal concat_start;
        LazySequence<data_type>* concat_seq;
        Generator<data_type>* base;
    public:
        ConcatGenerator(Ordinal length, LazySequence<data_type>* conc, Generator<data_type>* base_gen): length(length + conc.GetLength()), 
        pos(0, 0), concat_start(length), concat_seq(conc), base(base_gen) {}
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            return 0;
            //mistake
        }
        

        data_type get_next() {
            if (this->has_next()) {
                pos++;
                if (pos < Ordinal(concat_start.get_infinite(), concat_start.get_finite())) {
                    return base->get_next();
                }
                else {
                    return concat_seq->Get(Ordinal(pos.get_infinite() - concat_start.get_infinite(), pos.get_finite() - concat_start.get_finite()));
                }
            }
            else {
                throw std::runtime_error("No more elements in ConcatGenerator");
            }
        }

        ConcatGenerator* clone() const {
            return new ConcatGenerator(length, concat_seq->Clone(), base->clone());
        }
};

#endif