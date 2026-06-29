#ifndef OPTIONAL_H
#define OPTIONAL_H

template <typename data_type> class Optional {
    private:
        data_type value;
        bool if_value;

    public:
        Option() : if_value(false) {}
        Option(T initial_value) : value(initial_value), if_value(true) {}

        bool has_value() const {
            return if_value;
        }

        data_type get_value() {
            if (!if_value) {
                //throw std::runtime_error("Option does not have a value");
                return 0;
            }
            return value;
        }

        /*const T& operator*() const {
            return get_value();
        }

        const T* operator->() const {
            return &get_value();
        }

        T& operator*() {
            return get_value();
        }

        T* operator->() {
            return &get_value();
        }
        */

        void set_value(data_type new_value) {
            value = new_value;
            contains_value = true;
        }

        void reset() {
            contains_value = false;
        }
};

#endif