#ifndef GENERATOR_H
#define GENERATOR_H

template<typename data_type>
class Generator {
    public:
        virtual int position() const = 0;
        virtual bool has_next() const = 0;

        virtual data_type get_next() = 0;

        //virtual Ordinal estimate_remaining() const { return Omega::infinity(); } 

        //virtual Generator<T>* clone() const = 0; // Копия генератора с pos = 0, используется в derive-операциях, строится от всей исходной посл-сти, не от текущей pos

        virtual ~Generator() {};
};

template<typename data_type>
class SquareGenerator: public Generator<data_type> {
    private:
        int pos;
    public:
        SquareGenerator(): pos(0) {};

        int position() const{
            return pos;
        }

        bool has_next() const{
            return true;
        }

        data_type get_next() {
            pos++;
            return ((pos - 1) * (pos - 1));
        }
        
};

#endif