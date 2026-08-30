#ifndef GENERATOR_H
#define GENERATOR_H
#include "ordinal.hpp"
#include "sequence.hpp"

template<typename data_type>
class Generator {
    public:
        virtual Ordinal get_length() const = 0;
        virtual Ordinal position() const = 0;
        virtual bool has_next() const = 0;
        virtual data_type get(Ordinal elem_position) = 0;
        virtual data_type get_next() = 0;
        virtual Generator<data_type>* clone() const = 0; 

        virtual ~Generator() {};
};

template<typename data_type>
class SquareGenerator: public Generator<data_type> {
    private:
        Ordinal pos;
        Ordinal length;
    public:
        SquareGenerator(): pos(0, 0), length(1, 0) {}

        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const{
            return pos;
        }

        bool has_next() const{
            return true;
        }

        Generator<data_type>* clone() const{
            SquareGenerator<data_type>* clone_gen = new SquareGenerator<data_type>();
            return clone_gen;
        }
        
        data_type get(Ordinal elem_position) {
            if (elem_position.get_infinite() or elem_position.get_finite() < 0) {
                throw std::logic_error("Index out of range in square generator");
            }
            else {
                return(elem_position.get_finite() * elem_position.get_finite());
            }
        }

        data_type get_next() {
            pos++;
            return ((pos.get_finite() - 1) * (pos.get_finite() - 1));
        }
};

template<typename data_type>
class FibonaccyGenerator: public Generator<data_type> {
    private:
        Ordinal pos;
        Ordinal length;
        data_type b_1;
        data_type b_2;
    public:
        FibonaccyGenerator(): pos(0, 0), length(1, 0), b_1(1), b_2(0) {}

        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const{
            return pos;
        }

        bool has_next() const{
            return true;
        }

        FibonaccyGenerator<data_type>* clone() const{
            FibonaccyGenerator<data_type>* clone_gen = new FibonaccyGenerator<data_type>();
            return clone_gen;
        }
        
        data_type get(Ordinal elem_position) {
            if (elem_position.get_infinite() or (elem_position.get_finite() < pos.get_finite())) {
                throw std::logic_error("Index out of range in Fibonaccy generator");
            }
            else {
                data_type getresult;
                while (elem_position.get_finite() > (pos.get_finite() - 1)) {
                    getresult = get_next();
                }
                getresult = get_next();
                return getresult;
            }
        }

        data_type get_next() {
            pos++;
            data_type result = b_1 + b_2;
            b_1 = b_2;
            b_2 = result;
            return result;
        }
};

template <typename data_type>
class AppendGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        data_type elem;
        Generator<data_type>* base;
    public:
        AppendGenerator(Ordinal elem_pos, data_type elem, Generator<data_type>* base_gen): length(elem_pos), pos(0, 0), elem(elem), base(base_gen->clone()) {}

        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            data_type result;
            if (elem_position.is_infinite()) {
                if (elem_position == Ordinal(length.get_infinite(), length.get_finite() - 1)) {
                    return elem;
                }
                else {
                    return base->get(elem_position);
                }
            }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
            throw std::runtime_error("Unknown error in AppendGenerator");
        }

        data_type get_next() {
            if (pos < (Ordinal(length.get_infinite(), length.get_finite() - 1))) {
                pos++;
                return base->get_next();
            } 
            if (pos == (Ordinal(length.get_infinite(), length.get_finite() - 1))) {
                pos++;
                return elem;
            }
            throw std::runtime_error("Unknown error in AppendGenerator");
        }

        AppendGenerator* clone() const {
            return new AppendGenerator(length, elem, base->clone());
        }

        ~AppendGenerator() {
            delete base;
        }
}; 

template <typename data_type>
class PrependGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        data_type elem;
        Generator<data_type>* base;
    public:
        PrependGenerator(Ordinal length, data_type elem, Generator<data_type>* base_gen): length(length), pos(0, 0), elem(elem), base(base_gen->clone()) {}
        
        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            data_type result;
            if (elem_position.is_infinite()) {
                    return base->get(elem_position);
                }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
            throw std::runtime_error("Unknown error PrependGenerator");
        }

        data_type get_next() {
            if (pos == Ordinal::finity(0)) {
                pos++;
                return elem;
            }
            else {
                if (this->has_next()) {
                    pos++;
                    return base->get_next();
                }
                else {
                    throw std::logic_error("No more elements in PrependGenerator");
                }
            }
        }

        PrependGenerator* clone() const {
            return new PrependGenerator(length, elem, base->clone());
        }

        ~PrependGenerator() {
            delete base;
        }
};

template <typename data_type>
class InsertGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        Ordinal elem_pos;
        data_type elem;
        Generator<data_type>* base;
    public:
        InsertGenerator(Ordinal length, int elem_pos, data_type elem, Generator<data_type>* base_gen): length(length), pos(0, 0), elem_pos(0, elem_pos), elem(elem), base(base_gen->clone()) {}
        InsertGenerator(Ordinal length, Ordinal elem_pos, data_type elem, Generator<data_type>* base_gen): length(length), pos(0, 0), elem_pos(elem_pos), elem(elem), base(base_gen->clone()) {}
        
        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            data_type result;
            if (elem_position.is_infinite()) {
                if (elem_position == elem_pos) {
                    return elem;
                }
                else {
                    if (elem_pos.get_infinite() == elem_position.get_infinite() and elem_pos < elem_position) {
                        return base->get(Ordinal(elem_position.get_infinite(), elem_position.get_finite() - 1));
                    }
                    return base->get(elem_position);
                }
            }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
            throw std::runtime_error("Unknown error in InsertGenerator");
        }
        

        data_type get_next() {
            if (pos == elem_pos) {
                pos++;
                return elem;
            }
            if (this->has_next()) {
                pos++;
                return base->get_next();
            }
            else {
                throw std::logic_error("No more elements in InsertGenerator");
            }
        }

        InsertGenerator* clone() const {
            return new InsertGenerator(length, elem_pos, elem, base->clone());
        }

        ~InsertGenerator() {
            delete base;
        }
};

template <typename data_type>
class RemoveGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        Ordinal elem_pos;
        Generator<data_type>* base;
    public:
        RemoveGenerator(Ordinal length, int elem_pos, Generator<data_type>* base_gen): length(length), pos(0, 0), elem_pos(0, elem_pos), base(base_gen->clone()) {}
        RemoveGenerator(Ordinal length, Ordinal elem_pos, Generator<data_type>* base_gen): length(length), pos(0, 0), elem_pos(elem_pos), base(base_gen->clone()) {}
        
        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            data_type result;
            if (elem_position.is_infinite()) {
                if (elem_pos.get_infinite() == elem_position.get_infinite() and elem_pos < elem_position) {
                    return base->get(Ordinal(elem_position.get_infinite(), elem_position.get_finite() + 1));
                }
                return base->get(elem_position);
            }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
            throw std::runtime_error("Unknown error in RemoveGenerator");
        }

        data_type get_next() {
            if (pos == elem_pos and this->has_next()) {
                pos++;
                base->get_next();
            }
            if (this->has_next()) {
                pos++;
                return base->get_next();
            }
            else {
                throw std::logic_error("No more elements in RemoveGenerator");
            }
        }

        RemoveGenerator* clone() const {
            return new RemoveGenerator(length, elem_pos, base->clone());
        }

        ~RemoveGenerator() {
            delete base;
        }
};

template <typename data_type>
class MapGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        data_type(*func)(data_type);
        Generator<data_type>* base;
    public:
        MapGenerator(Ordinal length, data_type(*func)(data_type), Generator<data_type>* base_gen): length(length), pos(0, 0), func(func), base(base_gen->clone()) {}
        
        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            data_type result;
            if (elem_position.is_infinite()) {
                return base->get(elem_position);
                }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
            throw std::runtime_error("Unknown error in MapGenerator");
        }
        

        data_type get_next() {
            if (this->has_next()) {
                pos++;
                return func(base->get_next());
            }
            else {
                throw std::logic_error("No more elements in MapGenerator");
            }
        }

        MapGenerator* clone() const {
            return new MapGenerator(length, func, base->clone());
        }

        ~MapGenerator() {
            delete base;
        }
};

template <typename data_type>
class WhereGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        bool(*func)(data_type);
        Generator<data_type>* base;
    public:
        WhereGenerator(Ordinal length, bool(*func)(data_type), Generator<data_type>* base_gen): length(length), pos(0, 0), func(func), base(base_gen->clone()) {}
        
        Ordinal get_length() const{
            return length;
        }

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            data_type result;
            int counter = 0;
            int success_counter = 0;
            if (elem_position.is_infinite()) {
                    while (success_counter <= elem_position.get_finite()) {
                        result = base->get(Ordinal(elem_position.get_infinite(), counter));
                        counter++;
                        if (func(result)) {
                            success_counter++;
                        }
                    }
                return result;
                }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
        }

        data_type get_next() {
            bool flag = false;
            data_type result;
            while (not flag) {
                if (base->has_next()) {
                    result = base->get_next();
                    flag = func(result);
                }
                else {
                    throw std::logic_error("No more elements in WhereGenerator");
                }
            }
            pos++;
            return result;
        }

        WhereGenerator* clone() const {
            return new WhereGenerator(length, func, base->clone());
        }

        ~WhereGenerator() {
            delete base;
        }
};

/*
template <typename data_type>
class FunctionGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        data_type(*func)(data_type);
        Sequence<data_type>* values;
    public:
        FunctionGenerator(data_type(*func)(Sequence<data_type>*), Sequence<data_type>* start_val): length(1, 0), pos(0, 0), func(func), values(start_val) {}
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return true;
        }
        
        data_type get(Ordinal elem_position) {
            data_type result;
            while (pos < elem_position) {
                result = this->get_next();
            }
            return result;
        }
        

        data_type get_next() {
            pos++;
            data_type result = func(values);
            for (int i = 0; i < values.GetLength().get_finite(); i++) {
                values = values->Append(result);
                values = values->GetSubsequence(1, values->GetLength());
            }
            return result;
        }

        FunctionGenerator* clone() const {
            return new FunctionGenerator(func, values);
        }
};
*/

template <typename data_type>
class SubsequenceGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        Ordinal subseq_start;
        Ordinal subseq_end;
        Generator<data_type>* base;
    public:
        SubsequenceGenerator(Ordinal start, Ordinal end, Generator<data_type>* base_gen): length(end.get_infinite() - start.get_infinite(), end.get_finite() - start.get_finite()), 
        pos(0, 0), subseq_start(start), subseq_end(end), base(base_gen) {}

        Ordinal get_length() const {
            return length;
        }
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            data_type result;
            if (subseq_start.is_infinite() or elem_position.is_infinite()) {
                return base->get(subseq_start + elem_position);
                }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
            throw std::runtime_error("Unknown error in SubsequenceGenerator");
        }
        

        data_type get_next() {
            if (this->has_next()) {
                pos++;
                return base->get(subseq_start + pos - Ordinal(0, 1));
            }
            else {
                throw std::runtime_error("No more elements in SubsequenceGenerator");
            }
        }

        SubsequenceGenerator* clone() const {
            return new SubsequenceGenerator(subseq_start, subseq_end, base->clone());
        }

        ~SubsequenceGenerator() {
            delete base;
        }
};

template <typename data_type>
class LazySequence;

template <typename data_type>
class ConcatGenerator: public Generator<data_type> {
    private:
        Ordinal length;
        Ordinal pos;
        Ordinal concat_start;
        LazySequence<data_type>* concat_seq;
        Generator<data_type>* base;
    public:
        ConcatGenerator(Ordinal length, LazySequence<data_type>* conc, Generator<data_type>* base_gen): length(length + conc->GetLength()), 
        pos(0, 0), concat_start(length), concat_seq(conc), base(base_gen) {}

        Ordinal get_length() const {
            return length;
        }
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }
        
        data_type get(Ordinal elem_position) {
            data_type result;
            if (elem_position.is_infinite()) {
                if (elem_position >= concat_start) {
                    return concat_seq->Get(elem_position - concat_start);
                }
                return base->get(elem_position);
                }
            else {
                while (pos < elem_position) {
                    result = this->get_next();
                }
                return result;
            }
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

        ~ConcatGenerator() {
            delete base;
            delete concat_seq;
        }
};

template<typename data_type>
class EmptyGenerator: public Generator<data_type> {
    public:
        Ordinal get_length() const {
            return Ordinal(0, 0);
        }
        Ordinal position() const {
            return Ordinal(0, 0);
        }
        bool has_next() const {
            return false;
        }
        data_type get(Ordinal elem_position) {
            throw std::runtime_error("Generator is empty");
        }
        data_type get_next() {
            throw std::runtime_error("Generator is empty");
        }

        Generator<data_type>* clone() const {
            return new EmptyGenerator;
        } 

        ~EmptyGenerator() {};
};

#endif