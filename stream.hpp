#pragma once

#include "LazySequence.hpp"
#include "Sequence.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

template <typename T> class ReadOnlyStream {
    public:
        virtual ~ReadOnlyStream() = default;

        virtual void open() = 0;
        virtual void close() = 0;
        virtual bool is_end_of_stream() const = 0;
        virtual T read() = 0;
        virtual int get_position() const = 0;
        virtual bool is_can_go_to_index() const = 0;
        virtual int go_to_index(int index) = 0;
        virtual int go_forward() = 0;
        virtual int go_back() = 0;
        virtual bool is_can_go_back() const = 0;
};

template <typename T> class WriteOnlyStream {
    public:
        virtual ~WriteOnlyStream() = default;

        virtual void open() = 0;
        virtual void close() = 0;
        virtual int write(const T &item) = 0;
        virtual int get_position() const = 0;
        virtual bool is_can_go_to_index() const = 0;
        virtual int go_to_index(int index) = 0;
        virtual int go_forward() = 0;
        virtual int go_back() = 0;
        virtual bool is_can_go_back() const = 0;
};

template <typename T> class SequenceReadStream : public ReadOnlyStream<T> {
    private:
        Sequence<T> *source;
        int position;
        bool opened;

        void ensure_opened() const {
            if (!opened) {
                throw std::logic_error("Stream is not opened");
            }
        }

    public:
        SequenceReadStream(Sequence<T> &source):source(&source), position(0), opened(false) {}

        void open() {
            position = 0;
            opened = true;
        }

        void close() {
            opened = false;
        }

        bool is_end_of_stream() const {
            ensure_opened();
            return position >= source->GetLength();
        }

        T read() {
            ensure_opened();
            if (is_end_of_stream()) {
                throw std::out_of_range("End of stream");
            }

            T value = source->Get(position);
            position++;
            return value;
        }

        int get_position() const {
            return position;
        }

        bool is_can_go_to_index() const {
            return true;
        }

        int go_to_index(int index) {
            ensure_opened();
            if (index < 0 || index > source->GetLength()) {
                throw std::out_of_range("Stream position out of range");
            }
            position = index;
            return position;
        }

        int go_forward() {
            return go_to_index(position + 1);
        }

        int go_back() {
            return go_to_index(position - 1);
        }

        bool is_can_go_back() const {
            return true;
        }
};

template <typename T> class LazySequenceReadStream : public ReadOnlyStream<T> {
    private:
        LazySequence<T> *source;
        int position;
        bool opened;

        void ensure_opened() const {
            if (!opened) {
                throw std::logic_error("Stream is not opened");
            }
        }
    
    public:
        LazySequenceReadStream(LazySequence<T> &source) : source(&source), position(0), opened(false) {}

        void open() {
            position = 0;
            opened = true;
        }
        void close() {
            opened = false;
        }
        bool is_end_of_stream() const {
            ensure_opened();
            return source->GetLength().is_finite() && position >= source->GetLength().get_finite();
        }
        T read() {
            ensure_opened();
            if (is_end_of_stream()) {
                throw std::out_of_range("End of stream");
            }

            T value = source->Get(position);
            position++;
            return value;
        }
        int get_position() const {
            return position;
        }
        bool is_can_go_to_index() const {
            return true;
        }
        int go_to_index(int index) {
            ensure_opened();
            if (index < 0) {
                throw std::out_of_range("Stream position out of range");
            }
            if (source->GetLength().is_finite() && index > source->GetLength().get_finite()) {
                throw std::out_of_range("Stream position out of range");
            }

            position = index;
            return position;
        }
        int go_forward() {
            return go_to_index(position + 1);
        }
        int go_back() {
            return go_to_index(position - 1);
        }
        bool is_can_go_back() const {
            return true;
        }
};

template <typename T> class SequenceWriteStream : public WriteOnlyStream<T> {
    private:
        Sequence<T> *target;
        int position;
        bool opened;

        void ensure_opened() const {
            if (!opened) {
                throw std::logic_error("Stream is not opened");
            }
        }
    
    public:
        SequenceWriteStream(Sequence<T> &target) : target(&target), position(0), opened(false) {}

        void open() {
            position = target->GetLength();
            opened = true;
        }
        void close() {
            opened = false;
        }
        int write(const T &item) {
            ensure_opened();
            if (position < 0 || position > target->GetLength()) {
                throw std::out_of_range("Write position out of range");
            }

            if (position == target->GetLength()) {
                Sequence<T> *result = target->Append(item);
                target = result;
            } else {
                Sequence<T> *result = target->InsertAt(item, position);
                target = result;        
            }

            position++;
            return position;
        }
        int get_position() const {
            return position;
        }
        bool is_can_go_to_index() const {
            return true;
        }
        int go_to_index(int index) {
            ensure_opened();
            if (index < 0 || index > target->GetLength()) {
                throw std::out_of_range("Stream position out of range");
            }

            position = index;
            return position;
        }
        int go_forward() {
            return go_to_index(position + 1);
        }
        int go_back() {
            return go_to_index(position - 1);
        }
        bool is_can_go_back() const {
            return true;
        }
};

template <typename T> class FileReadStream : public ReadOnlyStream<T> {
    private:
        std::string path;
        T (*deserializer)(const std::string &item);
        mutable std::ifstream input;
        int position;
        bool opened;

        void ensure_opened() const {
            if (!opened) {
                throw std::logic_error("Stream is not opened");
            }
        }
    
    public:
        FileReadStream(const std::string &path, T (*deserialize)(const std::string &text)) : path(path), deserializer(deserializer), input(), position(0), opened(false) {}

        void open() {
            input.close();
            input.clear();
            input.open(path);
            if (!input.is_open()) {
                throw std::runtime_error("Cannot open file for reading");
            }

            position = 0;
            opened = true;
        }
        void close() {
            input.close();
            opened = false;
        }
        bool is_end_of_stream() const {
            ensure_opened();
            return input.peek() == EOF;
        }
        T read() {
            ensure_opened();
            std::string line;
            if (!std::getline(input, line)) {
                throw std::out_of_range("End of stream");
            }

            position++;
            return deserializer(line);
        }
        int get_position() const {
            return position;
        }
        bool is_can_go_to_index() const {
            return true;
        }
        int go_to_index(int index) {
            ensure_opened();
            if (index < 0) {
                throw std::out_of_range("Stream position out of range");
            }
            input.clear();
            input.seekg(0);
            position = 0;

            std::string ignored;
            while (position < index && std::getline(input, ignored)) {
                position++;
            }

            if (position != index) {
                throw std::out_of_range("Stream position out of range");
            }

            return position;
        }
        int go_forward() {
            return go_to_index(position + 1);
        }
        int go_back() {
            return go_to_index(position - 1);
        }
        bool is_can_go_back() const {
            return true;
        }
};

template <typename T> class FileWriteStream : public WriteOnlyStream<T> {
    private:
        std::string path;
        std::string (*serializer)(const T &item);
        std::ofstream output;
        int position;
        bool opened;

        void ensure_opened() const {
            if (!opened) {
                throw std::logic_error("Stream is not opened");
            }
        }

    public:
        FileWriteStream(const std::string &path, std::string (*serializer)(const T &item)) : path(path), serializer(serializer), output(), position(0), opened(false) {}

        void open() {
            output.close();
            output.clear();
            output.open(path);
            if (!output.is_open()) {
                throw std::runtime_error("Cannot open file for writing");
            }

            position = 0;
            opened = true;
        }
        void close() {
            output.close();
            opened = false;
        }
        int write(const T &item) {
            ensure_opened();
            output << serializer(item) << '\n';
            position++;
            return position;
        }
        int get_position() const {
            return position;
        }
        bool is_can_go_to_index() const {
            return false;
        }
        int go_to_index(int) {
            ensure_opened();
            throw std::logic_error("FileWriteStream does not support go_to_index");
        }
        int go_forward() {
            ensure_opened();
            throw std::logic_error("FileWriteStream does not support go_forward");
        }
        int go_back() override {
            ensure_opened();
            throw std::logic_error("FileWriteStream does not support go_back");
        }
        bool is_can_go_back() const {
            return false;
        }
};