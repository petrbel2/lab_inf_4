#ifndef GENERATOR_H
#define GENERATOR_H
#include "ordinal.hpp"

template<typename data_type>
class Generator {
    public:
        virtual Ordinal position() const = 0;
        virtual bool has_next() const = 0;
        virtual data_type get(Ordinal elem_position) = 0;
        virtual data_type get_next() = 0;

        //virtual Ordinal estimate_remaining() const { return Omega::infinity(); } 

        virtual Generator<data_type>* clone() const = 0; 

        virtual ~Generator() {};
};

template<typename data_type>
class SquareGenerator: public Generator<data_type> {
    private:
        Ordinal pos;
    public:
        SquareGenerator(): pos(0, 0) {}

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
            return 0;
            //its mistake
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
        data_type b_1;
        data_type b_2;
    public:
        FibonaccyGenerator(): pos(0, 0), b_1(1), b_2(0) {}

        Ordinal position() const{
            return pos;
        }

        bool has_next() const{
            return true;
        }

        Generator<data_type>* clone() const{
            FibonaccyGenerator<data_type>* clone_gen = new FibonaccyGenerator<data_type>();
            return clone_gen;
        }

        data_type get(Ordinal elem_position) {
            return 0;
            //its mistake
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
        AppendGenerator(Ordinal elem_pos, data_type elem, Generator<data_type>* base_gen): length(elem_pos), pos(0, 0), elem(elem), base(base_gen) {}

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            if (elem_position == length) {
                return elem;
            }
            else {
            if (pos < length) {
                return base->get(elem_position);
            }
            else if (pos == length) {
                return elem;
            }
            else {
                std::cout<<"YOU DUMB MOTHERFUCKER";
                return 0;
            }
            }
        }

        data_type get_next() {
            if (pos < length) {
                pos++;
                return base->get_next();
            } else if (pos == length) {
                pos++;
                return elem;
            }
            return elem; 
        }

        AppendGenerator* clone() const {
            return new AppendGenerator(length, elem, base->clone());
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
        PrependGenerator(Ordinal length, data_type elem, Generator<data_type>* base_gen): length(length), pos(0, 0), elem(elem), base(base_gen) {}
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            if (pos == pos.finity(0)) {
                return elem;
            } else {
                return base->get(elem_position);
            }
            //mistake
        }

        data_type get_next() {
            if (this->has_next()) {
                return base->get_next();
            }
            else {
                return 0;
                //mistake
            }
        }

        PrependGenerator* clone() const {
            return new PrependGenerator(length, elem, base->clone());
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
        InsertGenerator(Ordinal length, Ordinal elem_pos, data_type elem, Generator<data_type>* base_gen): length(length), pos(0, 0), elem_pos(elem_pos), elem(elem), base(base_gen) {}
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            if (pos == elem_pos) {
                return elem;
            } else {
                return base->get(elem_position);
            }
            //mistake
        }

        data_type get_next() {
            if (this->has_next()) {
                return base->get_next();
            }
            else {
                return 0;
                //mistake
            }
        }

        InsertGenerator* clone() const {
            return new InsertGenerator(length, elem, base->clone());
        }
};

#endif