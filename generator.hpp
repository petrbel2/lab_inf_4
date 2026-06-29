#ifndef GENERATOR_H
#define GENERATOR_H
#include "ordinal.hpp"

template<typename data_type>
class Generator {
    public:
        virtual Ordinal position() const = 0;
        virtual bool has_next() const = 0;
        virtual data_type get() = 0;
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

        data_type get() {
            return 0;
            //its mistake
        }

        data_type get_next() {
            pos++;
            return ((pos.get_finite() - 1) * (pos.get_finite() - 1));
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

        bool has_next() {
            if (pos < length) {
                return true;
            }
            else {
                return false;
            }
        }
        data_type get_next() {
            if this.has_next() {
                
            }
        }
        AppendGenerator<data_type>* clone() {}
}; 

template <typename data_type>
class PrependGenerator: public Generator<data_type> {
    private:
        data_type elem;
        Generator<data_type>* base;
    public:
        PrependGenerator(data_type elem, Generator<data_type>* base_gen): elem(elem), base(base_gen) {}
        
        bool has_next() {}
        data_type get_next() {}
        PrependGenerator<data_type>* clone() {}
};

#endif