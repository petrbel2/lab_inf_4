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
            if (elem_position.get_infinite() or elem_position.get_finite() < 0) {
                return -731; //mistake
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
            if (elem_position.get_infinite() or (elem_position.get_finite() < pos.get_finite())) {
                return 0; //mistake
            }
            else {
                data_type getresult;
                while (elem_position.get_finite() > pos.get_finite()) {
                    getresult = get_next();
                }
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
        AppendGenerator(Ordinal elem_pos, data_type elem, Generator<data_type>* base_gen): length(elem_pos), pos(0, 0), elem(elem), base(base_gen) {}

        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            if (elem_position == (Ordinal(length.get_infinite(), length.get_finite() - 1))) {
                return elem;
            }
            else {
            if (pos < (Ordinal(length.get_infinite(), length.get_finite() - 1))) {
                pos = elem_position;
                return base->get(elem_position);
            }
            else if (pos == length) {
                return elem;
            }
            else {
                std::cout<<"YOU DUMB MOTHERFUCKER";
                return -42;
            }
            }
        }

        data_type get_next() {
            if (pos < (Ordinal(length.get_infinite(), length.get_finite() - 1))) {
                pos++;
                return base->get_next();
            } else if (pos == (Ordinal(length.get_infinite(), length.get_finite() - 1))) {
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
            if (elem_position == Ordinal::finity(0)) {
                return elem;
            } else {
                pos = elem_position;
                return base->get(elem_position);
            }
            //mistake
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
                    return -100;
                    //mistake
                }
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
            if (elem_position == elem_pos) {
                pos = elem_position;
                return elem;
            } else {
                pos = elem_position;
                return base->get(elem_position);
            }
            //mistake
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
                return -666;
                //mistake
            }
        }

        InsertGenerator* clone() const {
            return new InsertGenerator(length, elem_pos, elem, base->clone());
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
        RemoveGenerator(Ordinal length, Ordinal elem_pos, Generator<data_type>* base_gen): length(length), pos(0, 0), elem_pos(elem_pos), base(base_gen) {}
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            if (elem_position == elem_pos and this->has_next()) {
                pos++;
                base->get_next();
                pos++;
                return base->get_next();
            } else {
                return -69;//mistake
                //pos = elem_position;
                //return base->get(elem_position);
            }
            //mistake
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
                return -67;
                //mistake
            }
        }

        RemoveGenerator* clone() const {
            return new RemoveGenerator(length, elem_pos, base->clone());
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
        MapGenerator(Ordinal length, data_type(*func)(data_type), Generator<data_type>* base_gen): length(length), pos(0, 0), func(func), base(base_gen) {}
        
        Ordinal position() const {
            return pos;
        }

        bool has_next() const {
            return pos <= length;
        }

        data_type get(Ordinal elem_position) {
            pos = elem_position;
            return func(base->get(elem_position));
            //mistake
        }

        data_type get_next() {
            if (this->has_next()) {
                pos++;
                return func(base->get_next());
            }
            else {
                return -68;
                //mistake
            }
        }

        MapGenerator* clone() const {
            return new MapGenerator(length, func, base->clone());
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
        WhereGenerator(Ordinal length, bool(*func)(data_type), Generator<data_type>* base_gen): length(length), pos(0, 0), func(func), base(base_gen) {}
        
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
            bool flag = false;
            data_type result;
            while (not flag) {
                if (base->has_next()) {
                    pos++;
                    result = base->get_next();
                    flag = func(result);
                }
                else {
                    return 0;
                    //mistake
                }
            }
            return result;
        }

        WhereGenerator* clone() const {
            return new WhereGenerator(length, func, base->clone());
        }
};

#endif