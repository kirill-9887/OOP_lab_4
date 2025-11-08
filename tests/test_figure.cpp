#include <gtest/gtest.h>
#include "../include/figure.h"
#include "../include/regular_polygon.h"
#include "../include/my_array.h"
#include "./test.h"
#include <sstream>
#include <cmath>

const double pi = std::numbers::pi;

static const std::vector<double> x_points{ -10, -5.5, -3.333, -2, -1, -0.001, 0, 0.1, 1.5, 4.99, 10, 30.01 };
static const std::vector<double> y_points{ -10, -5.5, -3.333, -2, -1, -0.001, 0, 0.1, 1.5, 4.99, 10, 30.01 };
static const std::vector<double> angles{ -2*pi, -1.5*pi, -pi, -pi/2, -pi/4, -pi/3, 0, pi/3, pi/4, pi/6, pi/2, pi, 1.5*pi, 2*pi, 3*pi };
static const std::vector<double> sides{ 1.5, 5, 10, 30, 100, 500 };

TEST(FigureTest, ConstructorWithParameters) {
    for (const auto &x : x_points) {
        for (const auto &y : y_points) {
            for (const auto &angle : angles) {
                for (const auto &side : sides) {
                    EXPECT_NO_THROW((RegularPolygon<double, 8>(gen_regular_polygon_points(8, x, y, angle, side))));
                    EXPECT_NO_THROW((RegularPolygon<double, 6>(gen_regular_polygon_points(6, x, y, angle, side))));
                    EXPECT_NO_THROW((RegularPolygon<double, 3>(gen_regular_polygon_points(3, x, y, angle, side))));

                    EXPECT_ANY_THROW((RegularPolygon<double, 8>(gen_regular_polygon_points(11, x, y, angle, side))));
                    EXPECT_ANY_THROW((RegularPolygon<double, 6>(gen_regular_polygon_points(6, x, y, angle, 0.0))));
                    EXPECT_ANY_THROW((RegularPolygon<double, 2>(gen_regular_polygon_points(2, x, y, angle, side))));
                }
            }
        }
    }
}

TEST(FigureTest, ConstructorCopy) {
    {
        constexpr int v{8};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> copy(original);
        EXPECT_NE(&original, &copy);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(original[i] == points[i]);
            EXPECT_TRUE(copy[i] == points[i]);
        }
    }
    {
        constexpr int v{6};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> copy(original);
        EXPECT_NE(&original, &copy);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(original[i] == points[i]);
            EXPECT_TRUE(copy[i] == points[i]);
        }
    }
    {
        constexpr int v{3};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> copy(original);
        EXPECT_NE(&original, &copy);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(original[i] == points[i]);
            EXPECT_TRUE(copy[i] == points[i]);
        }
    }
}

TEST(FigureTest, ConstructorMove) {
    {
        constexpr int v{8};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> move_to(std::move(original));
        EXPECT_NE(&original, &move_to);
        for (int i{0}; i < v; ++i) {
            EXPECT_ANY_THROW(original[i] == points[i]);
            EXPECT_TRUE(move_to[i] == points[i]);
        }
    }
    {
        constexpr int v{6};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> move_to(std::move(original));
        EXPECT_NE(&original, &move_to);
        for (int i{0}; i < v; ++i) {
            EXPECT_ANY_THROW(original[i] == points[i]);
            EXPECT_TRUE(move_to[i] == points[i]);
        }
    }
    {
        constexpr int v{3};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> move_to(std::move(original));
        EXPECT_NE(&original, &move_to);
        for (int i{0}; i < v; ++i) {
            EXPECT_ANY_THROW(original[i] == points[i]);
            EXPECT_TRUE(move_to[i] == points[i]);
        }
    }
}

TEST(FigureTest, AssignCopyOperator) {
    {
        constexpr int v{8};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> copy;
        copy = original;
        EXPECT_NE(&original, &copy);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(original[i] == points[i]);
            EXPECT_TRUE(copy[i] == points[i]);
        }
    }
    {
        constexpr int v{6};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> copy;
        copy = original;
        EXPECT_NE(&original, &copy);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(original[i] == points[i]);
            EXPECT_TRUE(copy[i] == points[i]);
        }
    }
    {
        constexpr int v{3};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> copy;
        copy = original;
        EXPECT_NE(&original, &copy);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(original[i] == points[i]);
            EXPECT_TRUE(copy[i] == points[i]);
        }
    }
}

TEST(FigureTest, AssignMoveOperator) {
    {
        constexpr int v{8};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> move_to;
        move_to = std::move(original);
        EXPECT_NE(&original, &move_to);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(move_to[i] == points[i]);
            EXPECT_ANY_THROW(original[i] == points[i]);
        }
    }
    {
        constexpr int v{6};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> move_to;
        move_to = std::move(original);
        EXPECT_NE(&original, &move_to);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(move_to[i] == points[i]);
            EXPECT_ANY_THROW(original[i] == points[i]);
        }
    }
    {
        constexpr int v{3};
        std::vector<Point<double>> points = gen_regular_polygon_points<double>(v, 4, 4, pi/5, 3.3);
        RegularPolygon<double, v> original(points);
        RegularPolygon<double, v> move_to;
        move_to = std::move(original);
        EXPECT_NE(&original, &move_to);
        for (int i{0}; i < v; ++i) {
            EXPECT_TRUE(move_to[i] == points[i]);
            EXPECT_ANY_THROW(original[i] == points[i]);
        }
    }
}

TEST(FigureTest, OperatorDouble_Square) {
    {
        constexpr int v{3};
        std::vector<Point<double>> tr1 = gen_regular_polygon_points<double>(v, 4, 4, 0, 3.3);
        std::vector<Point<double>> tr2 = gen_regular_polygon_points<double>(v, 1.5, 2.5, pi, 10);
        std::vector<Point<double>> tr3 = gen_regular_polygon_points<double>(v, 0, 0, pi/2, 1);
        MyArray<RegularPolygon<double, v>> arr(3);
        std::stringstream ss;
        for (int i{0}; i < v; ++i) {
            ss << tr1[i].get_x() << " " << tr1[i].get_y() << " ";
        }
        ss << std::endl;
        for (int i{0}; i < v; ++i) {
            ss << tr2[i].get_x() << " " << tr2[i].get_y() << " ";
        }
        ss << std::endl;
        for (int i{0}; i < v; ++i) {
            ss << tr3[i].get_x() << " " << tr3[i].get_y() << " ";
        }
        ss << std::endl;
        EXPECT_NO_THROW(arr.read_all(ss));
        EXPECT_NO_THROW(arr.print(std::cout));
        EXPECT_NO_THROW(arr.print_centres(std::cout));
        EXPECT_NO_THROW(arr.print_squares(std::cout));
        EXPECT_NO_THROW(arr.remove(1));
        EXPECT_NO_THROW(arr.print(std::cout));
    }
    {
        constexpr int v{6};
        std::vector<Point<double>> hexagon1 = gen_regular_polygon_points<double>(v, 4, 4, 0, 3.3);
        std::vector<Point<double>> hexagon2 = gen_regular_polygon_points<double>(v, 1.5, 2.5, pi, 10);
        std::vector<Point<double>> hexagon3 = gen_regular_polygon_points<double>(v, 0, 0, pi/2, 1);
        MyArray<RegularPolygon<double, v>> arr(3);
        std::stringstream ss;
        for (int i{0}; i < v; ++i) {
            ss << hexagon1[i].get_x() << " " << hexagon1[i].get_y() << " ";
        }
        ss << std::endl;
        for (int i{0}; i < v; ++i) {
            ss << hexagon2[i].get_x() << " " << hexagon2[i].get_y() << " ";
        }
        ss << std::endl;
        for (int i{0}; i < v; ++i) {
            ss << hexagon3[i].get_x() << " " << hexagon3[i].get_y() << " ";
        }
        ss << std::endl;
        EXPECT_NO_THROW(arr.read_all(ss));
        EXPECT_NO_THROW(arr.print(std::cout));
        EXPECT_NO_THROW(arr.print_centres(std::cout));
        EXPECT_NO_THROW(arr.print_squares(std::cout));
        EXPECT_NO_THROW(arr.remove(1));
        EXPECT_NO_THROW(arr.print(std::cout));
    }
    {
        constexpr int v{8};
        std::vector<Point<double>> octagon1 = gen_regular_polygon_points<double>(v, 4, 4, 0, 3.3);
        std::vector<Point<double>> octagon2 = gen_regular_polygon_points<double>(v, 1.5, 2.5, pi, 10);
        std::vector<Point<double>> octagon3 = gen_regular_polygon_points<double>(v, 0, 0, pi/2, 1);
        MyArray<RegularPolygon<double, v>> arr(3);
        std::stringstream ss;
        for (int i{0}; i < v; ++i) {
            ss << octagon1[i].get_x() << " " << octagon1[i].get_y() << " ";
        }
        ss << std::endl;
        for (int i{0}; i < v; ++i) {
            ss << octagon2[i].get_x() << " " << octagon2[i].get_y() << " ";
        }
        ss << std::endl;
        for (int i{0}; i < v; ++i) {
            ss << octagon3[i].get_x() << " " << octagon3[i].get_y() << " ";
        }
        ss << std::endl;
        EXPECT_NO_THROW(arr.read_all(ss));
        EXPECT_NO_THROW(arr.print(std::cout));
        EXPECT_NO_THROW(arr.print_centres(std::cout));
        EXPECT_NO_THROW(arr.print_squares(std::cout));
        EXPECT_NO_THROW(arr.remove(1));
        EXPECT_NO_THROW(arr.print(std::cout));
    }
    {
        RegularPolygon<double, 3> tr1(gen_regular_polygon_points<double>(3, 4, 4, 0, 3.3));
        RegularPolygon<double, 6> hexagon1 = gen_regular_polygon_points<double>(6, 4, 4, 0, 3.3);
        RegularPolygon<double, 8> octagon1 = gen_regular_polygon_points<double>(8, 4, 4, 0, 3.3);
        MyArray<Figure<double>*> arr{ &tr1, &hexagon1, &octagon1 };
        EXPECT_NO_THROW(arr.print(std::cout));
        EXPECT_NO_THROW(arr.print_centres(std::cout));
        EXPECT_NO_THROW(arr.print_squares(std::cout));
        EXPECT_NO_THROW(arr.remove(1));
        EXPECT_NO_THROW(arr.print(std::cout));
    }
}

TEST(FigureTest, OperatorEquals) {
    EXPECT_TRUE((RegularPolygon<double, 3>(gen_regular_polygon_points<double>(3, 0, 0, pi, 5.5))) ==
                (RegularPolygon<double, 3>(gen_regular_polygon_points<double>(3, 0.4, 10, pi/2, 5.5))));
    EXPECT_TRUE((RegularPolygon<double, 6>(gen_regular_polygon_points<double>(6, 0, 0, pi, 5.5))) ==
                (RegularPolygon<double, 6>(gen_regular_polygon_points<double>(6, 0.4, 10, pi/2, 5.5))));
    EXPECT_TRUE((RegularPolygon<double, 8>(gen_regular_polygon_points<double>(8, 0, 0, pi, 5.5))) ==
                (RegularPolygon<double, 8>(gen_regular_polygon_points<double>(8, 0.4, 10, pi/2, 5.5))));
    EXPECT_FALSE((RegularPolygon<double, 3>(gen_regular_polygon_points<double>(3, 0, 0, pi, 5.5))) ==
                (RegularPolygon<double, 3>(gen_regular_polygon_points<double>(3, 0, 0, pi, 6))));
    EXPECT_FALSE((RegularPolygon<double, 6>(gen_regular_polygon_points<double>(6, 0, 0, pi, 8))) ==
                (RegularPolygon<double, 6>(gen_regular_polygon_points<double>(6, 0.4, 10, pi/2, 10))));
    EXPECT_FALSE((RegularPolygon<double, 8>(gen_regular_polygon_points<double>(8, 0, 0, pi, 7))) ==
                (RegularPolygon<double, 8>(gen_regular_polygon_points<double>(8, 0.4, 10, pi/2, 2))));
}

TEST(FigureTest, OperatorIStream) {
    {
        RegularPolygon<double, 3> tr;
        std::stringstream ss("0 0 0 1 1 1");
        EXPECT_ANY_THROW(ss >> tr);
    }
    {
        RegularPolygon<double, 6> h;
        std::stringstream ss("0 0 0 1 1 1 2 0.5 2 0 1 -1");
        EXPECT_ANY_THROW(ss >> h);
    }
    {
        RegularPolygon<double, 8> oc;
        std::stringstream ss("0 0 0 1 1 1 2 0.5 2 0 1 -1 0.9 -0.5 0.5 -0.2");
        EXPECT_ANY_THROW(ss >> oc);
    }
}

TEST(FigureTest, CalcCentre) {
    for (const auto &x : x_points) {
        for (const auto &y : y_points) {
            for (const auto &angle : angles) {
                for (const auto &side : sides) {
                    std::vector<Point<double>> points8 = gen_regular_polygon_points(8, x, y, angle, side);
                    EXPECT_TRUE((RegularPolygon<double, 8>(points8).calc_centre() == mean<double>(points8)));
                    std::vector<Point<double>> points6 = gen_regular_polygon_points(6, x, y, angle, side);
                    EXPECT_TRUE((RegularPolygon<double, 6>(points6).calc_centre() == mean<double>(points6)));
                    std::vector<Point<double>> points3 = gen_regular_polygon_points(3, x, y, angle, side);
                    EXPECT_TRUE((RegularPolygon<double, 3>(points3).calc_centre() == mean<double>(points3)));
                }
            }
        }
    }
}