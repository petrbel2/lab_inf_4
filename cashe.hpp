#ifndef CASH_H 
#define CASH_H
#include "dynamicArray.hpp"

template <typename data_type>
class Cache {
    private:
        DynamicArray<data_type> buffer;
        int capacity;
        int count;
        int first_index; 
        int last_index; 
    public:
        Cache(int cap): buffer(cap), capacity(cap), count(0), first_index(-1), last_index(0) {}

        bool is_empty() {
            if (count == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        data_type get(int logical_index) {
            return buffer.Get(logical_index - first_index);
        }

        int get_count() {
            return count;
        }
        int get_capacity() {
            return capacity;
        } 

        int get_first_index() {
            return first_index;
        }
        int get_last_index() {
            return last_index;
        }

        bool contains(int logical_index) {
            if ((first_index <= logical_index) and (logical_index < last_index)) {
                return true;
            }
            else {
                return false;
            }
        }

        void push(data_type item) {
            if (count < capacity) {
                count++;
                last_index++;
                buffer.Set(count, item);
            }
            else {
                for (int i = 0; i < (capacity - 1); i++) {
                    buffer.Set(i, buffer.Get(i + 1));
                }
                buffer.Set(capacity - 1, item);
                first_index++;
                last_index++;
            }
        }

        //void clear();
};


#endif