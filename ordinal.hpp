#ifndef ORDINAL_H
#define ORDINAL_H 

class Ordinal {
private:
    int infinite;
    int finite;
public:
    Ordinal(int num_1, int num_2): infinite(num_1), finite(num_2) {}
    Ordinal(): infinite(0), finite(0) {}

    static Ordinal finity(int length) { return Ordinal(0, length); }
    static Ordinal infinity() { return Ordinal(1, 0); }
    static Ordinal omega_times(int k) { return Ordinal(k, 0); }
    static Ordinal zero() { return Ordinal(0, 0); }

    bool is_infinite() const { return infinite > 0; }
    bool is_finite() const { return infinite == 0; }

    int get_infinite() const { return infinite; }
    int get_finite() const { return finite; }

    bool operator==(const Ordinal& other) const {
            return infinite == other.infinite && finite == other.finite;
        }
};

#endif