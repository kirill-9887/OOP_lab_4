#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <iostream>
#include <exception>
#include <limits>
#include "./point.h"
#include <type_traits>
#include <concepts>

template<typename T>
concept IsFigure = requires (T t, std::ostream& os, std::istream& is) {
    { is >> t } -> std::same_as<std::istream&>;
    { os << t } -> std::same_as<std::ostream&>;
    { t.calc_centre() } -> std::same_as<Point<typename T::value_type>>;
    { static_cast<typename T::value_type>(t) } -> std::convertible_to<typename T::value_type>;
};

template<typename T>
requires IsFigure<T> || (std::is_pointer_v<T> && IsFigure<std::remove_pointer_t<T>>)
class MyArray
{
    using element_type = std::remove_pointer_t<T>;

private:
    size_t _capacity;
    size_t _size;
    std::shared_ptr<T[]> _body;

public:
    MyArray(size_t n) :
        _capacity(n),
        _size(n),
        _body(std::make_shared<T[]>(n))
    {}

    MyArray(const std::initializer_list<T>& figures) :
        _capacity(figures.size()),
        _size(figures.size()),
        _body(std::make_shared<T[]>(figures.size()))
    {
        size_t i{0};
        for (const auto &figure : figures) {
            _body[i] = figure;
            ++i;
        }
    }

    MyArray(const MyArray<T>& other) :
        _capacity(other._capacity),
        _size(other._size),
        _body(std::make_shared<T[]>(other._capacity))
    {
        for (size_t i{0}; i < _size; ++i) {
            _body[i] = other._body[i];
        }
    }

    MyArray(MyArray<T>&& other) noexcept {
        _capacity = other._capacity;
        _size = other._size;
        _body = std::move(other._body);
        other._capacity = 0;
        other._size = 0;
        other._body = nullptr;
    }

    MyArray<T>& operator=(const MyArray<T>& other) {
        if (this != &other) {
            MyArray<T> other_copy(other);
            std::swap(_capacity, other_copy._capacity);
            std::swap(_size, other_copy._size);
            std::swap(_body, other_copy._body);
        }
        return *this;
    }

    MyArray<T>& operator=(MyArray<T>&& other) noexcept {
        if (this != &other) {
            _capacity = other._capacity;
            _size = other._size;
            _body = std::move(other._body);
            other._capacity = 0;
            other._size = 0;
            other._body = nullptr;
        }
        return *this;
    }

    virtual ~MyArray() noexcept = default;

public:
    std::istream& read(size_t index, std::istream& is) {
        if constexpr (std::is_pointer_v<T>) {
            is >> *_body[index];
        } else {
            is >> _body[index];
        }
        return is;
    }

    std::istream& read_all(std::istream& is) {
        size_t old_size = _size;
        _size = 0;
        for (size_t i{0}; i < old_size; ++i) {
            try {
                read(i, is);
                ++_size;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return is;
            }
        }
        return is;
    }
    
    std::ostream& print(std::ostream& os) {
        for (size_t i{0}; i < _size; ++i) {
            os << i << ": ";
            if constexpr (std::is_pointer_v<T>) {
                os << *_body[i] << std::endl;
            } else {
                os << _body[i] << std::endl;
            }
        }
        return os;
    }

    std::ostream& print_centres(std::ostream& os) const {
        for (size_t i{0}; i < _size; ++i) {
            os << i << ": ";
            if constexpr (std::is_pointer_v<T>) {
                os << _body[i]->calc_centre() << std::endl;
            } else {
                os << _body[i].calc_centre() << std::endl;
            }
        }
        return os;
    }

    std::ostream& print_squares(std::ostream& os) const {
        for (size_t i{0}; i < _size; ++i) {
            os << i << ": ";
            if constexpr (std::is_pointer_v<T>) {
                os << static_cast<typename element_type::value_type>(*_body[i]) << std::endl;
            } else {
                os << static_cast<typename element_type::value_type>(_body[i]) << std::endl;
            }
        }
        return os;
    }

    typename element_type::value_type total_square() const {
        typename element_type::value_type total_square{0};
        for (size_t i{0}; i < _size; ++i) {
            if constexpr (std::is_pointer_v<T>) {
                total_square += static_cast<typename element_type::value_type>(*_body[i]);
            } else {
                total_square += static_cast<typename element_type::value_type>(_body[i]);
            }
        }
        return total_square;
    }

    void remove(size_t index) {
        for (size_t i{index}; i < _size - 1; ++i) {
            _body[i] = _body[i + 1];
        }
        --_size;
    }
};

#endif