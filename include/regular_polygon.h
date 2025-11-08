#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H

#include "./figure.h"
#include <type_traits>
#include <concepts>
#include <vector>
#include <numbers>

template <Scalar T>
std::vector<Point<T>> gen_regular_polygon_points(int v_count, T start_x, T start_y, T start_angle, T side) {
    std::vector<Point<T>> point_vector(v_count);
    point_vector[0] = Point<T>(start_x, start_y);
    T angle = std::numbers::pi - std::numbers::pi * (v_count - 2) / v_count;
    for (int i = 1; i < v_count; ++i) {
        point_vector[i] = point_vector[i - 1] + (Point<T>(0, 1) * side).rotate(start_angle - angle * (i - 1));
    }
    return point_vector;
}

template <Scalar T, int V>
class RegularPolygon : public Figure<T>
{
public:
    RegularPolygon() :
        Figure<T>(gen_regular_polygon_points<T>(V, 0, 0, 0, 1))
    {
    }

    RegularPolygon(const std::vector<Point<T>>& points) :
        Figure<T>(points)
    {
        if (points.size() != V) {
            throw std::invalid_argument("Invalid vertices number");
        }
    }

    RegularPolygon(const std::initializer_list<Point<T>>& points) :
        Figure<T>(points)
    {
        if (points.size() != V) {
            throw std::invalid_argument("Invalid vertices number");
        }
    }

    RegularPolygon(const RegularPolygon<T, V>& other) :
        Figure<T>(other)
    {}

    RegularPolygon(RegularPolygon<T, V>&& other) noexcept :
        Figure<T>(std::move(other))
    {}

    RegularPolygon<T, V>& operator=(const Figure<T>& other) override {
        const RegularPolygon<T, V> *ptr = dynamic_cast<const RegularPolygon<T, V>*>(&other);
        if (!ptr) {
            throw std::invalid_argument("Figure being assigned is not a regular polygon");
        }
        Figure<T>::operator=(other);
        return *this;
    }

    RegularPolygon<T, V>& operator=(const RegularPolygon<T, V>& other) {
        Figure<T>::operator=(other);
        return *this;
    }

    RegularPolygon<T, V>& operator=(RegularPolygon<T, V>&& other) noexcept {
        if (this != &other) {
            this->_vertices_number = other._vertices_number;
            this->_points = std::move(other._points);
            other._vertices_number = 0;
        }
        return *this;
    }

    ~RegularPolygon() noexcept = default;

public:
    bool operator==(const Figure<T>& other) const override {
        const RegularPolygon<T, V>* ptr = dynamic_cast<const RegularPolygon<T, V>*>(&other);
        if (!ptr) {
            return false;
        }
        return (this->_vertices_number == other.get_vertices_number() && 
                (this->_points[1] - this->_points[0]).abs_eq(ptr->_points[1] - ptr->_points[0]));
    }

protected:
    void print(std::ostream& os) const override {
        switch (V) {
        case 3:
            os << "Triangle: ";
            break;
        case 6:
            os << "Hexagone: ";
            break;
        case 8:
            os << "Octagon: ";
            break;
        default:
            os << "RegularPolygon(" << V << "): ";
            break;
        }
        Figure<T>::print(os);
    }

    T square() const override {
        T side = (this->_points[1] - this->_points[0]).length();
        T perimeter = this->_vertices_number * side;
        T small_radius = side / std::tan(std::numbers::pi / this->_vertices_number);
        return 0.5 * perimeter * small_radius;
    }

protected:
    bool sides_invalid(const std::vector<Point<T>>& points) override {
        if (points.size() != V || Figure<T>::sides_invalid(points)) {
            return true;
        }
        double need_angle = std::numbers::pi - std::numbers::pi * (points.size() - 2) / points.size();
        for (size_t i{0}; i < points.size(); ++i) {
            Point<T> v1 = points[(i + 1) % points.size()] - points[i];
            Point<T> v2 = points[(i + 2) % points.size()] - points[(i + 1) % points.size()];
            T angle = v1.angle_to(v2);
            if (std::abs(need_angle - angle) > Point<T>::eps) {
                return true;
            }
        }
        return false;
    }
};

#endif