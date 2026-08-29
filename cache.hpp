#ifndef CACHE_H 
#define CACHE_H
#include "dynamicArray.hpp"
#include "ordinal.hpp"

template <typename data_type>
class Cache {
    private:
        DynamicArray<data_type> buffer;
        int capacity;
        int count;
        Ordinal first_index; 
        Ordinal last_index; 
    public:
        Cache(int cap): buffer(cap), capacity(cap), count(0), first_index(0, 0), last_index(0, 0) {}

        bool is_empty() {
            if (count == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        data_type get(int logical_index) {
            return buffer.Get(logical_index - first_index.get_finite());
        }

        data_type get(Ordinal logical_index) {
            return buffer.Get(logical_index.get_finite() - first_index.get_finite());
        }

        int get_count() {
            return count;
        }
        int get_capacity() {
            return capacity;
        } 

        Ordinal get_first_index() {
            return first_index;
        }
        Ordinal get_last_index() {
            return last_index;
        }

        bool contains(int l_index) {
            Ordinal logical_index(0, l_index);
            if ((first_index <= logical_index) and (logical_index < last_index)) {
                return true;
            }
            else {
                return false;
            }
        }

        bool contains(Ordinal logical_index) {
            if ((first_index <= logical_index) and (logical_index < last_index)) {
                return true;
            }
            else {
                return false;
            }
        }

        void push(data_type item) {
            if (count < capacity) {
                last_index++;
                buffer.Set(count, item);
                count++;
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
};


#endif