#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <cmath>
#include <concepts>
#include <type_traits>

template<typename T>
concept Scalar = std::is_scalar_v<T> && std::floating_point<T>;

template<Scalar T>
class Point final
{
    template<Scalar A>
    friend Point<A>& operator+=(Point<A>& left, const Point<A>& right);

    template<Scalar A>
    friend Point<A>& operator-=(Point<A>& left, const Point<A>& right);

    template<Scalar A>
    friend Point<A> operator+(Point<A> left, const Point<A>& right);

    template<Scalar A>
    friend Point<A> operator-(Point<A> left, const Point<A>& right);

    template<Scalar A>
    friend Point<A> operator*(A k, Point<A> right);

    template<Scalar A>
    friend bool operator==(const Point<A>& left, const Point<A>& right);

    template<Scalar A>
    friend bool operator!=(const Point<A>& left, const Point<A>& right);
    
    template<Scalar A>
    friend std::ostream& operator<<(std::ostream& os, const Point<A>& obj);
    
    template<Scalar A>
    friend std::istream& operator>>(std::istream& is, Point<A>& obj);
    
    template<Scalar A>
    friend A vector_product_factor(const Point<A>& p1, const Point<A>& p2);
    
    template<Scalar A>
    friend A scalar_product(const Point<A>& p1, const Point<A>& p2);

public:
    static constexpr T eps{1e-5};

private:
    T _x{};
    T _y{};

public:
    Point() = default;

    Point(T x, T y) :
        _x(x), _y(y)
    {
    }

    Point(const Point<T>& other) = default;

    Point<T>& operator=(const Point<T>& other) = default;

    ~Point() noexcept = default;

public:
    T get_x() const {
        return _x;
    }

    T get_y() const {
        return _y;
    }

public:
    std::string str() const {
        return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
    }

    void print(std::ostream& os) const {
        os << "(" << _x << ", " << _y << ")";
    }

    void read(std::istream& is) {
        is >> _x >> _y;
    }

public:
    Point<T>& operator*=(T k) {
        _x *= k;
        _y *= k;
        return *this;
    }

    Point<T>& operator/=(T k) {
        _x /= k;
        _y /= k;
        return *this;
    }

    Point<T> operator*(T k) const {
        Point res(*this);
        res *= k;
        return res;
    }

    Point<T> operator/(T k) const {
        Point res(*this);
        res /= k;
        return res;
    }

public:
    T length() const {
        return std::sqrt(scalar_product(*this, *this));
    }

    bool abs_eq(const Point<T>& other) const {
        return std::abs(length() - other.length()) < eps;
    }

    T angle_to(const Point<T>& other) const noexcept(false) {
        if (std::abs(length()) < eps || std::abs(other.length()) < eps) {
            throw std::invalid_argument("Angle with null length vector is not defined");
        }
        T cos_ = scalar_product(*this, other) / length() / other.length();
        if (cos_ > 1.0) {
            cos_ = 1.0;
        } else if (cos_ < -1.0) {
            cos_ = -1.0;
        }
        return acos(cos_);
    }

    Point<T> rotate(T angle) const {
        Point<T> rotated(
            _x * std::cos(angle) - _y * std::sin(angle),
            _x * std::sin(angle) + _y * std::cos(angle)
        );
        return rotated;
    }
};

template<Scalar T>
Point<T>& operator+=(Point<T>& left, const Point<T>& right)  {
    left._x += right._x;
    left._y += right._y;
    return left;
}

template<Scalar T>
Point<T>& operator-=(Point<T>& left, const Point<T>& right) {
    left._x -= right._x;
    left._y -= right._y;
    return left;
}

template<Scalar T>
Point<T> operator+(Point<T> left, const Point<T>& right) {
    return left += right;
}

template<Scalar T>
Point<T> operator-(Point<T> left, const Point<T>& right) {
    return left -= right;
}

template<Scalar T>
Point<T> operator*(T k, Point<T> right) {
    return right *= k;
}

template<Scalar T>
bool operator==(const Point<T>& left, const Point<T>& right) {
    return std::abs(left._x - right._x) < Point<T>::eps && std::abs(left._y - right._y) < Point<T>::eps;
}

template<Scalar T>
bool operator!=(const Point<T>& left, const Point<T>& right) {
    return !(left == right);
}

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& obj) {
    obj.print(os);
    return os;
}

template<Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& obj) {
    obj.read(is);
    return is;
}

template<Scalar T>
T vector_product_factor(const Point<T>& p1, const Point<T>& p2) {
    return p1._x * p2._y - p2._x * p1._y;
}

template<Scalar T>
T scalar_product(const Point<T>& p1, const Point<T>& p2) {
    return p1._x * p2._x + p1._y * p2._y;
}

#endif