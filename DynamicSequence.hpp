#ifndef ARRAYSEQUENCE_H 
#define ARRAYSEQUENCE_H

#include "dynamicArray.hpp"
#include "sequence.hpp"

template <typename data_type>
class DynamicSequence: public Sequence<data_type>
{
private:
    DynamicArray<data_type> array;

public:
    DynamicSequence(data_type* items, int length) : array(items, length) {
    }

    DynamicSequence() : array() {}

    DynamicSequence(DynamicSequence <data_type> & old_array) : array(old_array.array) {}

    int GetLength() {
        return array.GetLength();
    }

    data_type Get(int index) {
        if ((index >= array.GetLength()) or (index < 0)) {
            std::cout<<"Wrong index, first value returned\n";
            return array.Get(0);
        }
        return array.Get(index);
    }

    Sequence<data_type>* Append(data_type new_elem) {
        auto result = static_cast<DynamicSequence<data_type>*>(Instance());
        result->array.Resize(array.GetLength() + 1);
        result->array.Set(array.GetLength() - 1, new_elem);
        return result;
    }

    Sequence<data_type>* Prepend(data_type new_elem) {
        auto result = static_cast<DynamicSequence<data_type>*>(Instance());
        result->array.Resize(array.GetLength() + 1);
        for (int i = array.GetLength() - 1; 0 < i; i--) {
           result->array.Set(i, array.Get(i - 1));
        }
        result->array.Set(0, new_elem);
        return result;
    }

    Sequence<data_type>* InsertAt(data_type new_elem, int position) {
        auto result = static_cast<DynamicSequence<data_type>*>(Instance());
        if ((position < 0) or (position > (array.GetLength()))) {
            std::cout<<"Wrong index\n";
            return result;
        }
        else {
            result->array.Resize(array.GetLength() + 1);
            for (int i = result->array.GetLength() - 1; position < i; i--) {
                result->array.Set(i, array.Get(i - 1));
            }
            result->array.Set(position, new_elem);
            return result;
        }
    }

    Sequence<data_type>* GetSubsequence(int startIndex, int endIndex) {
        auto result = static_cast<DynamicSequence<data_type>*>(Copy());
        result->array.Resize(endIndex);
        for (int i = startIndex; i < endIndex; i++) {
            result->array.Set(i - startIndex, array.Get(i));
        }
        result->array.Resize(endIndex - startIndex);
        return result;
    }

    // старый конкат
    //Sequence<data_type>* Concat(Sequence<data_type> *new_array) {
    //    auto result = static_cast<DynamicSequence<data_type>*>(Instance());
    //    result->array.Concat(&((static_cast<DynamicSequence<data_type>*>(new_array))->array));
    //    return result;
    //}
    
    Sequence<data_type>* Concat(Sequence<data_type> *new_array) {
        auto result = static_cast<DynamicSequence<data_type>*>(Instance());
        for (int i = 0; i < new_array->GetLength(); i++) {
            result->Append(new_array->Get(i));
        }
        return result;
    }

    virtual Sequence<data_type>* Instance() = 0;

    virtual Sequence<data_type>* Copy() = 0;
};



template <typename data_type>
class MutDynamicSequence: public DynamicSequence<data_type>
{
    public:
    MutDynamicSequence(data_type* items, int length):  DynamicSequence<data_type>(items, length) {}

    MutDynamicSequence(): DynamicSequence<data_type>() {}

    MutDynamicSequence(MutDynamicSequence <data_type> & old_array): DynamicSequence<data_type>(old_array) {}

    Sequence<data_type>* Instance() {
        return this;
    }

    Sequence<data_type>* Copy() {
        return new MutDynamicSequence<data_type>(*this); 
    }
};

template <typename data_type>
class ImmutDynamicSequence: public DynamicSequence<data_type>
{
    public:
    ImmutDynamicSequence(data_type* items, int length):  DynamicSequence<data_type>(items, length) {}

    ImmutDynamicSequence(): DynamicSequence<data_type>() {}

    ImmutDynamicSequence(ImmutDynamicSequence <data_type> & old_array): DynamicSequence<data_type>(old_array) {}

    Sequence<data_type>* Instance() {
        return new ImmutDynamicSequence<data_type>(*this); 
    }

    Sequence<data_type>* Copy() {
        return new ImmutDynamicSequence<data_type>(*this); 
    }
};

#endif