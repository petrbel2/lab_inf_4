#ifndef OMEGA_H
#define OMEGA_H 

class Omega {
private:
    int infinite;
    int finite;
public:
    Omega(int num_1, int num_2): infinite(num_1), finite(num_2) {}
    Omega(): infinite(0), finite(0) {}

    static Omega finity(int length) { return Omega(0, length); }
    static Omega infinity() { return Omega(1, 0); }
    static Omega omega_times(int k) { return Omega(k, 0); }
    static Omega zero() { return Omega(0, 0); }

    bool is_infinite() const { return infinite > 0; }
    bool is_finite() const { return infinite == 0; }

    int get_infinite() const { return infinite; }
    int get_finite() const { return finite; }

    bool operator==(const Omega& other) const {
            return infinite == other.infinite && finite == other.finite;
        }
};

#endif