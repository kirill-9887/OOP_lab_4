#ifndef FIGURE_H
#define FIGURE_H

#include "./point.h"
#include <iostream>
#include <initializer_list>
#include <exception>
#include <string>
#include <memory>
#include <vector>
#include <type_traits>
#include <concepts>

template<Scalar T>
class Figure
{    
    template<Scalar A>
    friend std::ostream& operator<<(std::ostream& os, const Figure<A>& obj);
    
    template<Scalar A>
    friend std::istream& operator>>(std::istream& is, Figure<A>& obj);

public:
    using value_type = T;

protected:
    int _vertices_number;
    std::unique_ptr<Point<T>[]> _points;

public:
    int get_vertices_number() const {
        return _vertices_number;
    }

protected:
    Figure(const std::vector<Point<T>>& points) :
        _vertices_number(points.size()),
        _points(std::make_unique<Point<T>[]>(points.size()))
    {
        if (points.size() < 3) {
            throw std::invalid_argument("There are too few vertices");
        }
        set_points(points);
    }

    Figure(const std::initializer_list<Point<T>>& points) :
        _vertices_number(points.size()),
        _points(std::make_unique<Point<T>[]>(points.size()))
    {
        if (points.size() < 3) {
            throw std::invalid_argument("There are too few vertices");
        }
        set_points(std::vector<Point<T>>(points));
    }

    Figure(const Figure<T>& other) :
        _vertices_number(other._vertices_number),
        _points(std::make_unique<Point<T>[]>(other._vertices_number))
    {
        for (size_t i{0}; i < static_cast<size_t>(other._vertices_number); ++i) {
            _points[i] = other._points[i];
        }
    }

    Figure(Figure<T>&& other) noexcept :
        _vertices_number(other._vertices_number),
        _points(std::move(other._points))
    {
        other._vertices_number = 0;
    }

public:
    virtual Figure<T>& operator=(const Figure<T>& other) {
        if (this != &other) {
            _vertices_number = other._vertices_number;
            _points = std::make_unique<Point<T>[]>(other._vertices_number);
            for (size_t i{0}; i < static_cast<size_t>(other._vertices_number); ++i) {
                _points[i] = other._points[i];
            }
        }
        return *this;
    }

    Figure<T>& operator=(Figure<T>&& other) noexcept {
        if (this != &other) {
            _vertices_number = other._vertices_number;
            _points = std::move(other._points);
            other._vertices_number = 0;
        }
        return *this;
    }

public:
    virtual ~Figure() noexcept = default;

public:
    virtual Point<T> operator[](int point_index) const {
        if (point_index >= _vertices_number) {
            throw std::out_of_range("Point index is out of range");
        }
        return _points[point_index];
    }

public:
    Point<T> calc_centre() const {
        Point<T> summ;
        for (size_t i{0}; i < static_cast<size_t>(_vertices_number); ++i) {
            summ += _points[i];
        }
        return summ / _vertices_number;
    }

    explicit operator T() const {
        return square();
    }

public:
    virtual bool operator==(const Figure<T>& other) const = 0;

    bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }

protected:
    void set_points(const std::vector<Point<T>>& points) noexcept(false) {
        if (sides_invalid(points)) {
            std::string s;
            for (size_t i = 0; i < points.size(); ++i) {
                s += points[i].str();
            }
            throw std::invalid_argument("Invalid sides. Points: " + s);
        }
        if (points.size() != _vertices_number) {
            throw std::invalid_argument("Number of vertices does not match the existing one");
        }
        size_t ind{0};
        for (const auto &p : points) {
            _points[ind] = p;
            ++ind;
        }
    }

    virtual void print(std::ostream& os) const {
        os << "[ ";
        for (size_t i{0}; i < static_cast<size_t>(_vertices_number) - 1; ++i) {
            os << _points[i] << ", ";
        }
        os << _points[_vertices_number - 1] << " ]";
    }

    virtual void read(std::istream& is) {
        std::vector<Point<T>> points(_vertices_number);
        for (size_t i{0}; i < static_cast<size_t>(_vertices_number); ++i) {
            is >> points[i];
        }
        set_points(points);
    }

    virtual T square() const = 0;

protected:
    virtual bool sides_invalid(const std::vector<Point<T>>& points) {
        for (size_t i{0}; i < points.size(); ++i) {
            Point<T> v1 = points[(i + 1) % points.size()] - points[i];
            Point<T> v2 = points[(i + 2) % points.size()] - points[(i + 1) % points.size()];
            T v_product_factor = vector_product_factor(v1, v2);
            if (v_product_factor > 0 || std::abs(v_product_factor) < Point<T>::eps || 
                    v1.length() < Point<T>::eps || v2.length() < Point<T>::eps) {
                return true;
            }
        }
        return false;
    }
};

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& obj) {
    obj.print(os);
    return os;
}

template<Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& obj) {
    obj.read(is);
    return is;
}

#endif