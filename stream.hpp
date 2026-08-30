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
        const Sequence<T> *source;
        int position;
        bool opened;

        void ensure_opened() const {
            if (!opened) {
                throw std::logic_error("Stream is not opened");
            }
        }

    public:
        SequenceReadStream(const Sequence<T> &source):source(&source), position(0), opened(false) {}

        open() {
            position = 0;
            opened = true;
        }

        void close() {
            opened = false;
        }

        bool is_end_of_stream() const {
            ensure_opened();
            return position >= source->get_length();
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

        void ensure_opened() const;
    
    public:
        LazySequenceReadStream(LazySequence<T> &source);

        void open() override;
        void close() override;
        bool is_end_of_stream() const override;
        T read() override;
        int get_position() const override;
        bool is_can_go_to_index() const override;
        int go_to_index(int index) override;
        int go_forward() override;
        int go_back() override;
        bool is_can_go_back() const override;
};

template <typename T> class SequenceWriteStream : public WriteOnlyStream<T> {
    private:
        Sequence<T> *target;
        int position;
        bool opened;

        void ensure_opened() const;
    
    public:
        SequenceWriteStream(Sequence<T> &target);

        void open() override;
        void close() override;
        int write(const T &item) override;
        int get_position() const override;
        bool is_can_go_to_index() const override;
        int go_to_index(int index) override;
        int go_forward() override;
        int go_back() override;
        bool is_can_go_back() const override;
};

template <typename T> class FileReadStream : public ReadOnlyStream<T> {
    private:
        std::string path;
        T (*deserializer)(const std::string &item);
        mutable std::ifstream input;
        int position;
        bool opened;

        void ensure_opened() const;
    
    public:
        FileReadStream(const std::string &path, T (*deserialize)(const std::string &text));

        void open() override;
        void close() override;
        bool is_end_of_stream() const override;
        T read() override;
        int get_position() const override;
        bool is_can_go_to_index() const override;
        int go_to_index(int index) override;
        int go_forward() override;
        int go_back() override;
        bool is_can_go_back() const override;
};

template <typename T> class FileWriteStream : public WriteOnlyStream<T> {
    private:
        std::string path;
        std::string (*serializer)(const T &item);
        std::ofstream output;
        int position;
        bool opened;

        void ensure_opened() const;

    public:
        FileWriteStream(const std::string &path, std::string (*serializer)(const T &item));

        void open() override;
        void close() override;
        int write(const T &item) override;
        int get_position() const override;
        bool is_can_go_to_index() const override;
        int go_to_index(int index) override;
        int go_forward() override;
        int go_back() override;
        bool is_can_go_back() const override;
};

template <typename T> LazySequenceReadStream<T>::LazySequenceReadStream(LazySequence<T> &source)
   : source(&source), position(0), opened(false) {}

template <typename T> void LazySequenceReadStream<T>::ensure_opened() const {
    if (!opened) {
        throw std::logic_error("Stream is not opened");
    }
}

template <typename T> void LazySequenceReadStream<T>::open() {
    position = 0;
    opened = true;
}

template <typename T> void LazySequenceReadStream<T>::close() {
    opened = false;
}

template <typename T> bool LazySequenceReadStream<T>::is_end_of_stream() const {
    ensure_opened();
    return source->get_length().is_finite() && position >= source->get_length().value();
}
template <typename T> T LazySequenceReadStream<T>::read() {
    ensure_opened();
    if (is_end_of_stream()) {
        throw std::out_of_range("End of stream");
    }

    T value = source->get(position);
    position++;
    return value;
}

template <typename T> int LazySequenceReadStream<T>::get_position() const {
    return position;
}

template <typename T> bool LazySequenceReadStream<T>::is_can_go_to_index() const {
    return true;
}

template <typename T> int LazySequenceReadStream<T>::go_to_index(int index) {
    ensure_opened();
    if (index < 0) {
        throw std::out_of_range("Stream position out of range");
    }
    if (source->get_length().is_finite() && index > source->get_length().value()) {
        throw std::out_of_range("Stream position out of range");
    }

    position = index;
    return position;
}

template <typename T> int LazySequenceReadStream<T>::go_forward() {
    return go_to_index(position + 1);
}

template <typename T> int LazySequenceReadStream<T>::go_back() {
    return go_to_index(position - 1);
}

template <typename T> bool LazySequenceReadStream<T>::is_can_go_back() const {
    return true;
}

template <typename T> SequenceWriteStream<T>::SequenceWriteStream(Sequence<T> &target)
    : target(&target), position(0), opened(false) {}

template <typename T> void SequenceWriteStream<T>::ensure_opened() const {
    if (!opened) {
        throw std::logic_error("Stream is not opened");
    }
}

template <typename T> void SequenceWriteStream<T>::open() {
    position = target->get_length();
    opened = true;
}

template <typename T> void SequenceWriteStream<T>::close() {
    opened = false;
}

template <typename T> int SequenceWriteStream<T>::write(const T&item) {
    ensure_opened();
    if (position < 0 || position > target->get_length()) {
        throw std::out_of_range("Write position out of range");
    }

    if (position == target->get_length()) {
        Sequence<T> *result = target->append(item);
        target = result;
    } else {
        Sequence<T> *without_old_item = target->remove(position);
        target = without_old_item;
        Sequence<T> *result = target->insert(item, position);
        target = result;        
    }

    position++;
    return position;
}

template <typename T> int SequenceWriteStream<T>::get_position() const {
    return position;
}

template <typename T> bool SequenceWriteStream<T>::is_can_go_to_index() const {
    return true;
}

template <typename T> int SequenceWriteStream<T>::go_to_index(int index) {
    ensure_opened();
    if (index < 0 || index > target->get_length()) {
        throw std::out_of_range("Stream position out of range");
    }

    position = index;
    return position;
}

template <typename T> int SequenceWriteStream<T>::go_forward() {
    return go_to_index(position + 1);
}

template <typename T> int SequenceWriteStream<T>::go_back() {
    return go_to_index(position - 1);
}

template <typename T> bool SequenceWriteStream<T>::is_can_go_back() const {
    return true;
}

template <typename T> FileReadStream<T>::FileReadStream(const std::string &path, 
    T (*deserializer)(const std::string &text)) : path(path), deserializer(deserializer),
    input(), position(0), opened(false) {}

template <typename T> void FileReadStream<T>::ensure_opened() const {
    if (!opened) {
        throw std::logic_error("Stream is not opened");
    }
}

template <typename T> void FileReadStream<T>::open() {
    input.close();
    input.clear();
    input.open(path);
    if (!input.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }

    position = 0;
    opened = true;
}

template <typename T> void FileReadStream<T>::close() {
    input.close();
    opened = false;
}

template <typename T> bool FileReadStream<T>::is_end_of_stream() const {
    ensure_opened();
    return input.peek() == EOF;
}

template <typename T> T FileReadStream<T>::read() {
    ensure_opened();
    std::string line;
    if (!std::getline(input, line)) {
        throw std::out_of_range("End of stream");
    }

    position++;
    return deserializer(line);
}

template <typename T> int FileReadStream<T>::get_position() const {
    return position;
}

template <typename T> bool FileReadStream<T>::is_can_go_to_index() const {
    return true;
}

template <typename T> int FileReadStream<T>::go_to_index(int index) {
    ensure_opened();
    if (index < 0) {
        throw std::out_of_range("Stream position out of range");
    }
    input.clear();
    input.seekg(0); // Возвращаемся в начало
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

template <typename T> int FileReadStream<T>::go_forward() {
    return go_to_index(position + 1);
}

template <typename T> int FileReadStream<T>::go_back() {
    return go_to_index(position - 1);
}

template <typename T> bool FileReadStream<T>::is_can_go_back() const {
    return true;
}

template <typename T> FileWriteStream<T>::FileWriteStream(const std::string &path,
    std::string (*serializer)(const T &item)) : path(path), serializer(serializer),
    output(), position(0), opened(false) {}

template <typename T> void FileWriteStream<T>::ensure_opened() const {
    if (!opened) {
        throw std::logic_error("Stream is not opened");
    }
}

template <typename T> void FileWriteStream<T>::open() {
    output.close();
    output.clear();
    output.open(path);
    if (!output.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }

    position = 0;
    opened = true;
}

template <typename T> void FileWriteStream<T>::close() {
    output.close();
    opened = false;
}

template <typename T> int FileWriteStream<T>::write(const T &item) {
    ensure_opened();
    output << serializer(item) << '\n';
    position++;
    return position;
}

template <typename T> int FileWriteStream<T>::get_position() const {
    return position;
}

template <typename T> bool FileWriteStream<T>::is_can_go_to_index() const {
    return false;
}

template <typename T> int FileWriteStream<T>::go_to_index(int) {
    ensure_opened();
    throw std::logic_error("FileWriteStream does not support go_to_index");
}

template <typename T> int FileWriteStream<T>::go_forward() {
    ensure_opened();
    throw std::logic_error("FileWriteStream does not support go_forward");
}

template <typename T> int FileWriteStream<T>::go_back() {
    ensure_opened();
    throw std::logic_error("FileWriteStream does not support go_back");
}

template <typename T> bool FileWriteStream<T>::is_can_go_back() const {
    return false;
}