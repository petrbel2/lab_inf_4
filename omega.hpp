#ifndef OMEGA_H
#define OMEGA_H 

class Omega {
private:
    int finite;
    int infinite;
public:
    Omega(int num_1, int num_2): finite(num_1), infinite(num_2) {}
    Omega(): finite(0), infinite(0) {}
};

#endif