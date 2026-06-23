#ifndef SEQUENCE_H 
#define SEQUENCE_H
#include "ordinal.hpp"

template <typename data_type>
class Sequence
{
public:
    virtual data_type Get(int index) = 0;

    virtual Ordinal GetLength() const = 0;

    //virtual Sequence<data_type>* Append(data_type new_elem) = 0;
    //virtual Sequence<data_type>* Prepend(data_type new_elem) = 0;
    //virtual Sequence<data_type>* InsertAt(data_type new_elem, int postion) = 0;

    //virtual Sequence<data_type>* GetSubList(int startIndex, int endIndex) = 0; 
    //virtual Sequence<data_type>* Concat(Sequence<data_type>*) = 0;
};

#endif