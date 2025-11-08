#include <gtest/gtest.h>
#include "../include/point.h"
#include "./test.h"
#include <sstream>
#include <cmath>

TEST(PointTest, ConstructorDefault) {
    Point<double> v;
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 0.0));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), 0.0));
}

TEST(PointTest, ConstructorWithValues) {
    Point<double> v1(1.0, 2.0);
    EXPECT_TRUE(scalar_eq<double>(v1.get_x(), 1.0));
    EXPECT_TRUE(scalar_eq<double>(v1.get_y(), 2.0));

    Point<double> v2(-3.5, 4.1);
    EXPECT_TRUE(scalar_eq<double>(v2.get_x(), -3.5));
    EXPECT_TRUE(scalar_eq<double>(v2.get_y(), 4.1));

    Point<double> v3(0.0, 0.0);
    EXPECT_TRUE(scalar_eq<double>(v3.get_x(), 0.0));
    EXPECT_TRUE(scalar_eq<double>(v3.get_y(), 0.0));

    Point<double> v4(1e9, -1e9);
    EXPECT_TRUE(scalar_eq<double>(v4.get_x(), 1e9));
    EXPECT_TRUE(scalar_eq<double>(v4.get_y(), -1e9));

    Point<double> v5(0.123, -0.456);
    EXPECT_TRUE(scalar_eq<double>(v5.get_x(), 0.123));
    EXPECT_TRUE(scalar_eq<double>(v5.get_y(), -0.456));
}

TEST(PointTest, ConstructorCopy) {
    Point<double> original(5.0, -7.0);
    Point<double> copy(original);

    EXPECT_TRUE(scalar_eq<double>(copy.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(copy.get_y(), -7.0));
    EXPECT_NE(&original, &copy);
}

TEST(PointTest, OperatorPlusEqual) {
    Point<double> vA(1, 1);
    Point<double> vB(1, 1);
    vA += vB;
    EXPECT_TRUE(scalar_eq<double>(vA.get_x(), 2.0));
    EXPECT_TRUE(scalar_eq<double>(vA.get_y(), 2.0));

    Point<double> vC(-2, 3);
    Point<double> vD(4, -5);
    vC += vD;
    EXPECT_TRUE(scalar_eq<double>(vC.get_x(), 2.0));
    EXPECT_TRUE(scalar_eq<double>(vC.get_y(), -2.0));

    Point<double> vE(0, 0);
    Point<double> vF(5, 6);
    vE += vF;
    EXPECT_TRUE(scalar_eq<double>(vE.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(vE.get_y(), 6.0));

    Point<double> vG(7, 8);
    Point<double> vH(0, 0);
    vG += vH;
    EXPECT_TRUE(scalar_eq<double>(vG.get_x(), 7.0));
    EXPECT_TRUE(scalar_eq<double>(vG.get_y(), 8.0));

    Point<double> vI(-10, -20);
    Point<double> vJ(-30, -40);
    vI += vJ;
    EXPECT_TRUE(scalar_eq<double>(vI.get_x(), -40.0));
    EXPECT_TRUE(scalar_eq<double>(vI.get_y(), -60.0));
}

TEST(PointTest, OperatorMinusEqual) {
    Point<double> vA(5, 5);
    Point<double> vB(2, 2);
    vA -= vB;
    EXPECT_TRUE(scalar_eq<double>(vA.get_x(), 3.0));
    EXPECT_TRUE(scalar_eq<double>(vA.get_y(), 3.0));

    Point<double> vC(-2, 3);
    Point<double> vD(4, -5);
    vC -= vD;
    EXPECT_TRUE(scalar_eq<double>(vC.get_x(), -6.0));
    EXPECT_TRUE(scalar_eq<double>(vC.get_y(), 8.0));

    Point<double> vE(0, 0);
    Point<double> vF(5, 6);
    vE -= vF;
    EXPECT_TRUE(scalar_eq<double>(vE.get_x(), -5.0));
    EXPECT_TRUE(scalar_eq<double>(vE.get_y(), -6.0));

    Point<double> vG(7, 8);
    Point<double> vH(0, 0);
    vG -= vH;
    EXPECT_TRUE(scalar_eq<double>(vG.get_x(), 7.0));
    EXPECT_TRUE(scalar_eq<double>(vG.get_y(), 8.0));

    Point<double> vI(-10, -20);
    Point<double> vJ(-30, -40);
    vI -= vJ;
    EXPECT_TRUE(scalar_eq<double>(vI.get_x(), 20.0));
    EXPECT_TRUE(scalar_eq<double>(vI.get_y(), 20.0));
}

TEST(PointTest, OperatorPlus) {
    Point<double> v1(1.0, 2.0);
    Point<double> v2(3.0, 4.0);
    Point<double> result = v1 + v2;
    EXPECT_TRUE(scalar_eq<double>(result.get_x(), 4.0));
    EXPECT_TRUE(scalar_eq<double>(result.get_y(), 6.0));
    EXPECT_TRUE(scalar_eq<double>(v1.get_x(), 1.0));
    EXPECT_TRUE(scalar_eq<double>(v1.get_y(), 2.0));
    EXPECT_TRUE(scalar_eq<double>(v2.get_x(), 3.0));
    EXPECT_TRUE(scalar_eq<double>(v2.get_y(), 4.0));
}

TEST(PointTest, OperatorMinus) {
    Point<double> v1(5.0, 6.0);
    Point<double> v2(2.0, 3.0);
    Point<double> result = v1 - v2;
    EXPECT_TRUE(scalar_eq<double>(result.get_x(), 3.0));
    EXPECT_TRUE(scalar_eq<double>(result.get_y(), 3.0));
    EXPECT_TRUE(scalar_eq<double>(v1.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(v1.get_y(), 6.0));
    EXPECT_TRUE(scalar_eq<double>(v2.get_x(), 2.0));
    EXPECT_TRUE(scalar_eq<double>(v2.get_y(), 3.0));
}

TEST(PointTest, OperatorMultiplyScalar) {
    Point<double> v(2.0, 3.0);
    double k = 2.5;
    Point<double> result = k * v;
    EXPECT_TRUE(scalar_eq<double>(result.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(result.get_y(), 7.5));
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 2.0));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), 3.0));

    Point<double> vA(1, 2);
    double kA = 3;
    Point<double> resA = kA * vA;
    EXPECT_TRUE(scalar_eq<double>(resA.get_x(), 3.0));
    EXPECT_TRUE(scalar_eq<double>(resA.get_y(), 6.0));

    Point<double> vB(-3, 4);
    double kB = -0.5;
    Point<double> resB = kB * vB;
    EXPECT_TRUE(scalar_eq<double>(resB.get_x(), 1.5));
    EXPECT_TRUE(scalar_eq<double>(resB.get_y(), -2.0));

    Point<double> vC(0, 0);
    double kC = 100;
    Point<double> resC = kC * vC;
    EXPECT_TRUE(scalar_eq<double>(resC.get_x(), 0.0));
    EXPECT_TRUE(scalar_eq<double>(resC.get_y(), 0.0));

    Point<double> vD(5, 6);
    double kD = 0;
    Point<double> resD = kD * vD;
    EXPECT_TRUE(scalar_eq<double>(resD.get_x(), 0.0));
    EXPECT_TRUE(scalar_eq<double>(resD.get_y(), 0.0));

    Point<double> vE(1e6, 1e-6);
    double kE = 1e-3;
    Point<double> resE = kE * vE;
    EXPECT_TRUE(scalar_eq<double>(resE.get_x(), 1e3));
    EXPECT_TRUE(scalar_eq<double>(resE.get_y(), 1e-9));
}

TEST(PointTest, OperatorEqual) {
    Point<double> v1(1.0, 2.0);
    Point<double> v2(1.0, 2.0);
    Point<double> v3(1.0, 3.0);
    Point<double> v4(2.0, 2.0);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 == v4);

    Point<double> vA(5, 5); Point<double> vB(5, 5); EXPECT_TRUE(vA == vB);
    Point<double> vC(5, 5); Point<double> vD(5, 6); EXPECT_FALSE(vC == vD);
    Point<double> vE(5, 5); Point<double> vF(6, 5); EXPECT_FALSE(vE == vF);
    Point<double> vG(0, 0); Point<double> vH(0, 0); EXPECT_TRUE(vG == vH);
    Point<double> vI(-1.23, 4.56); Point<double> vJ(-1.23, 4.56); EXPECT_TRUE(vI == vJ);
}

TEST(PointTest, OperatorNotEqual) {
    Point<double> v1(1.0, 2.0);
    Point<double> v2(1.0, 2.0);
    Point<double> v3(1.0, 3.0);
    Point<double> v4(2.0, 2.0);

    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 != v4);

    Point<double> vA(5, 5); Point<double> vB(5, 5); EXPECT_FALSE(vA != vB);
    Point<double> vC(5, 5); Point<double> vD(5, 6); EXPECT_TRUE(vC != vD);
    Point<double> vE(5, 5); Point<double> vF(6, 5); EXPECT_TRUE(vE != vF);
    Point<double> vG(0, 0); Point<double> vH(0, 0); EXPECT_FALSE(vG != vH);
    Point<double> vI(-1.23, 4.56); Point<double> vJ(-1.23, 4.56); EXPECT_FALSE(vI != vJ);
}

TEST(PointTest, OperatorStreamOutput) {
    Point<double> v(1.5, -2.5);
    std::stringstream ss;
    ss << v;
    std::string output = ss.str();
    EXPECT_EQ(output, "(1.5, -2.5)");

    Point<double> vA(1, 2); std::stringstream ssA; ssA << vA;
    EXPECT_EQ(ssA.str(), "(1, 2)");

    Point<double> vB(-3, 4); std::stringstream ssB; ssB << vB;
    EXPECT_EQ(ssB.str(), "(-3, 4)");

    Point<double> vC(0, 0); std::stringstream ssC; ssC << vC;
    EXPECT_EQ(ssC.str(), "(0, 0)");

    Point<double> vD(0.123, -0.456); std::stringstream ssD; ssD << vD;
    EXPECT_EQ(ssD.str(), "(0.123, -0.456)");
}

TEST(PointTest, OperatorStreamInput) {
    Point<double> v;
    std::stringstream ss("10.5 -5.2");
    ss >> v;
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 10.5));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), -5.2));

    Point<double> vA; std::stringstream ssA("5 10"); ssA >> vA;
    EXPECT_TRUE(scalar_eq<double>(vA.get_x(), 5.0)); EXPECT_TRUE(scalar_eq<double>(vA.get_y(), 10.0));

    Point<double> vB; std::stringstream ssB("-2 8"); ssB >> vB;
    EXPECT_TRUE(scalar_eq<double>(vB.get_x(), -2.0)); EXPECT_TRUE(scalar_eq<double>(vB.get_y(), 8.0));

    Point<double> vC; std::stringstream ssC("0 0"); ssC >> vC;
    EXPECT_TRUE(scalar_eq<double>(vC.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(vC.get_y(), 0.0));

    Point<double> vD; std::stringstream ssD("0.789 -0.123"); ssD >> vD;
    EXPECT_TRUE(scalar_eq<double>(vD.get_x(), 0.789)); EXPECT_TRUE(scalar_eq<double>(vD.get_y(), -0.123));

    Point<double> vE; std::stringstream ssE("1000000 -2000000"); ssE >> vE;
    EXPECT_TRUE(scalar_eq<double>(vE.get_x(), 1e6)); EXPECT_TRUE(scalar_eq<double>(vE.get_y(), -2e6));
}

TEST(PointTest, VectorProductFactor) {
    Point<double> v1(1.0, 0.0);
    Point<double> v2(0.0, 1.0);
    EXPECT_TRUE(scalar_eq<double>(vector_product_factor(v1, v2), 1.0));

    Point<double> v3(0.0, 1.0);
    Point<double> v4(1.0, 0.0);
    EXPECT_TRUE(scalar_eq<double>(vector_product_factor(v3, v4), -1.0));

    Point<double> vA(2, 3); Point<double> vB(4, 5);
    EXPECT_TRUE(scalar_eq<double>(vector_product_factor(vA, vB), -2.0));

    Point<double> vC(1, 0); Point<double> vD(1, 0);
    EXPECT_TRUE(scalar_eq<double>(vector_product_factor(vC, vD), 0.0));

    Point<double> vE(0, 1); Point<double> vF(0, 1);
    EXPECT_TRUE(scalar_eq<double>(vector_product_factor(vE, vF), 0.0));

    Point<double> vG(1, 1); Point<double> vH(-1, 1);
    EXPECT_TRUE(scalar_eq<double>(vector_product_factor(vG, vH), 2.0));

    Point<double> vI(3, -2); Point<double> vJ(-1, 4);
    EXPECT_TRUE(scalar_eq<double>(vector_product_factor(vI, vJ), 10.0));
}

TEST(PointTest, ScalarProduct) {
    Point<double> v1(1.0, 2.0);
    Point<double> v2(3.0, 4.0);
    EXPECT_TRUE(scalar_eq<double>(scalar_product(v1, v2), 11.0));

    Point<double> vA(2, 3); Point<double> vB(4, 5);
    EXPECT_TRUE(scalar_eq<double>(scalar_product(vA, vB), 23.0));

    Point<double> vC(1, 0); Point<double> vD(0, 1);
    EXPECT_TRUE(scalar_eq<double>(scalar_product(vC, vD), 0.0));

    Point<double> vE(-1, -2); Point<double> vF(-3, -4);
    EXPECT_TRUE(scalar_eq<double>(scalar_product(vE, vF), 11.0));

    Point<double> vG(0, 0); Point<double> vH(5, 6);
    EXPECT_TRUE(scalar_eq<double>(scalar_product(vG, vH), 0.0));

    Point<double> vI(10, 20); Point<double> vJ(0.1, 0.2);
    EXPECT_TRUE(scalar_eq<double>(scalar_product(vI, vJ), 5.0));
}

TEST(PointTest, OperatorMultiplyScalarMember) {
    Point<double> v(2.0, 3.0);
    double k = 2.5;
    Point<double> result = v * k;
    EXPECT_TRUE(scalar_eq<double>(result.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(result.get_y(), 7.5));
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 2.0));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), 3.0));

    Point<double> vA(1, 2); double kA = 3; Point<double> resA = vA * kA;
    EXPECT_TRUE(scalar_eq<double>(resA.get_x(), 3.0)); EXPECT_TRUE(scalar_eq<double>(resA.get_y(), 6.0));

    Point<double> vB(-3, 4); double kB = -0.5; Point<double> resB = vB * kB;
    EXPECT_TRUE(scalar_eq<double>(resB.get_x(), 1.5)); EXPECT_TRUE(scalar_eq<double>(resB.get_y(), -2.0));

    Point<double> vC(0, 0); double kC = 100; Point<double> resC = vC * kC;
    EXPECT_TRUE(scalar_eq<double>(resC.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(resC.get_y(), 0.0));

    Point<double> vD(5, 6); double kD = 0; Point<double> resD = vD * kD;
    EXPECT_TRUE(scalar_eq<double>(resD.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(resD.get_y(), 0.0));

    Point<double> vE(1e6, 1e-6); double kE = 1e-3; Point<double> resE = vE * kE;
    EXPECT_TRUE(scalar_eq<double>(resE.get_x(), 1e3)); EXPECT_TRUE(scalar_eq<double>(resE.get_y(), 1e-9));
}

TEST(PointTest, OperatorDivideScalar) {
    Point<double> v(10.0, -4.0);
    double k = 2.0;
    Point<double> result = v / k;
    EXPECT_TRUE(scalar_eq<double>(result.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(result.get_y(), -2.0));
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 10.0));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), -4.0));

    Point<double> vA(6, 8); double kA = 2; Point<double> resA = vA / kA;
    EXPECT_TRUE(scalar_eq<double>(resA.get_x(), 3.0)); EXPECT_TRUE(scalar_eq<double>(resA.get_y(), 4.0));

    Point<double> vB(-5, 10); double kB = -5; Point<double> resB = vB / kB;
    EXPECT_TRUE(scalar_eq<double>(resB.get_x(), 1.0)); EXPECT_TRUE(scalar_eq<double>(resB.get_y(), -2.0));

    Point<double> vC(0, 0); double kC = 10; Point<double> resC = vC / kC;
    EXPECT_TRUE(scalar_eq<double>(resC.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(resC.get_y(), 0.0));

    Point<double> vD(7, 9); double kD = 1; Point<double> resD = vD / kD;
    EXPECT_TRUE(scalar_eq<double>(resD.get_x(), 7.0)); EXPECT_TRUE(scalar_eq<double>(resD.get_y(), 9.0));

    Point<double> vE(1e6, 1e-6); double kE = 1e3; Point<double> resE = vE / kE;
    EXPECT_TRUE(scalar_eq<double>(resE.get_x(), 1e3)); EXPECT_TRUE(scalar_eq<double>(resE.get_y(), 1e-9));
}

TEST(PointTest, OperatorMultiplyEqualScalar) {
    Point<double> v(2.0, 3.0);
    double k = 2.5;
    v *= k;
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), 7.5));

    Point<double> vA(1, 2); double kA = 3; vA *= kA;
    EXPECT_TRUE(scalar_eq<double>(vA.get_x(), 3.0)); EXPECT_TRUE(scalar_eq<double>(vA.get_y(), 6.0));

    Point<double> vB(-3, 4); double kB = -0.5; vB *= kB;
    EXPECT_TRUE(scalar_eq<double>(vB.get_x(), 1.5)); EXPECT_TRUE(scalar_eq<double>(vB.get_y(), -2.0));

    Point<double> vC(0, 0); double kC = 100; vC *= kC;
    EXPECT_TRUE(scalar_eq<double>(vC.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(vC.get_y(), 0.0));

    Point<double> vD(5, 6); double kD = 0; vD *= kD;
    EXPECT_TRUE(scalar_eq<double>(vD.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(vD.get_y(), 0.0));

    Point<double> vE(1e6, 1e-6); double kE = 1e-3; vE *= kE;
    EXPECT_TRUE(scalar_eq<double>(vE.get_x(), 1e3)); EXPECT_TRUE(scalar_eq<double>(vE.get_y(), 1e-9));
}

TEST(PointTest, OperatorDivideEqualScalar) {
    Point<double> v(10.0, -4.0);
    double k = 2.0;
    v /= k;
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 5.0));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), -2.0));

    Point<double> vA(6, 8); double kA = 2; vA /= kA;
    EXPECT_TRUE(scalar_eq<double>(vA.get_x(), 3.0)); EXPECT_TRUE(scalar_eq<double>(vA.get_y(), 4.0));

    Point<double> vB(-5, 10); double kB = -5; vB /= kB;
    EXPECT_TRUE(scalar_eq<double>(vB.get_x(), 1.0)); EXPECT_TRUE(scalar_eq<double>(vB.get_y(), -2.0));

    Point<double> vC(0, 0); double kC = 10; vC /= kC;
    EXPECT_TRUE(scalar_eq<double>(vC.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(vC.get_y(), 0.0));

    Point<double> vD(7, 9); double kD = 1; vD /= kD;
    EXPECT_TRUE(scalar_eq<double>(vD.get_x(), 7.0)); EXPECT_TRUE(scalar_eq<double>(vD.get_y(), 9.0));

    Point<double> vE(1e6, 1e-6); double kE = 1e3; vE /= kE;
    EXPECT_TRUE(scalar_eq<double>(vE.get_x(), 1e3)); EXPECT_TRUE(scalar_eq<double>(vE.get_y(), 1e-9));
}

TEST(PointTest, Length) {
    Point<double> v(3.0, 4.0);
    EXPECT_TRUE(scalar_eq<double>(v.length(), 5.0));

    Point<double> vA(0, 0);
    EXPECT_TRUE(scalar_eq<double>(vA.length(), 0.0));

    Point<double> vB(1, 0);
    EXPECT_TRUE(scalar_eq<double>(vB.length(), 1.0));

    Point<double> vC(0, -1);
    EXPECT_TRUE(scalar_eq<double>(vC.length(), 1.0));

    Point<double> vD(5, 12);
    EXPECT_TRUE(scalar_eq<double>(vD.length(), 13.0));

    Point<double> vE(-6, -8);
    EXPECT_TRUE(scalar_eq<double>(vE.length(), 10.0));
}

TEST(PointTest, AbsEq) {
    Point<double> v1(1.0, 2.0);
    Point<double> v2(1.0, 2.0);
    EXPECT_TRUE(v1.abs_eq(v2));

    Point<double> v3(1.0, 0.0);
    Point<double> v4(1.0 + Point<double>::eps / 2.0, 0.0);
    EXPECT_TRUE(v3.abs_eq(v4));

    Point<double> v5(1.0 + Point<double>::eps * 2.0, 0.0);
    EXPECT_FALSE(v3.abs_eq(v5));
}

TEST(PointTest, AngleTo) {
    Point<double> v1(1.0, 0.0);
    Point<double> v2(0.0, 1.0);
    EXPECT_TRUE(scalar_eq<double>(v1.angle_to(v2), M_PI / 2.0));

    Point<double> v3(1.0, 0.0);
    Point<double> v4(1.0, 0.0);
    EXPECT_TRUE(scalar_eq<double>(v3.angle_to(v4), 0.0));

    Point<double> vA(1, 0); Point<double> vB(0, 1);
    EXPECT_TRUE(scalar_eq<double>(vA.angle_to(vB), M_PI / 2.0));

    Point<double> vC(1, 0); Point<double> vD(-1, 0);
    EXPECT_TRUE(scalar_eq<double>(vC.angle_to(vD), M_PI));

    Point<double> vE(1, 1); Point<double> vF(1, 0);
    EXPECT_TRUE(scalar_eq<double>(vE.angle_to(vF), M_PI / 4.0));

    Point<double> vG(0, 0); Point<double> vH(1, 0);
    EXPECT_ANY_THROW(vG.angle_to(vH));

    Point<double> vI(1, 0); Point<double> vJ(0, -1);
    EXPECT_TRUE(scalar_eq<double>(vI.angle_to(vJ), M_PI / 2.0));
}

TEST(PointTest, Print) {
    Point<double> v(3.14, -2.71);
    std::stringstream ss;
    v.print(ss);
    EXPECT_EQ(ss.str(), "(3.14, -2.71)");

    Point<double> vA(1, 2); std::stringstream ssA; vA.print(ssA);
    EXPECT_EQ(ssA.str(), "(1, 2)");

    Point<double> vB(-5, 0); std::stringstream ssB; vB.print(ssB);
    EXPECT_EQ(ssB.str(), "(-5, 0)");

    Point<double> vC(0, 0); std::stringstream ssC; vC.print(ssC);
    EXPECT_EQ(ssC.str(), "(0, 0)");

    Point<double> vD(0.123, 0.456); std::stringstream ssD; vD.print(ssD);
    EXPECT_EQ(ssD.str(), "(0.123, 0.456)");
}

TEST(PointTest, Read) {
    Point<double> v;
    std::stringstream ss("15.7 -9.3");
    v.read(ss);
    EXPECT_TRUE(scalar_eq<double>(v.get_x(), 15.7));
    EXPECT_TRUE(scalar_eq<double>(v.get_y(), -9.3));

    Point<double> vA; std::stringstream ssA("10 20"); vA.read(ssA);
    EXPECT_TRUE(scalar_eq<double>(vA.get_x(), 10.0)); EXPECT_TRUE(scalar_eq<double>(vA.get_y(), 20.0));

    Point<double> vB; std::stringstream ssB("-30 40"); vB.read(ssB);
    EXPECT_TRUE(scalar_eq<double>(vB.get_x(), -30.0)); EXPECT_TRUE(scalar_eq<double>(vB.get_y(), 40.0));

    Point<double> vC; std::stringstream ssC("0 0"); vC.read(ssC);
    EXPECT_TRUE(scalar_eq<double>(vC.get_x(), 0.0)); EXPECT_TRUE(scalar_eq<double>(vC.get_y(), 0.0));

    Point<double> vD; std::stringstream ssD("0.987 -0.654"); vD.read(ssD);
    EXPECT_TRUE(scalar_eq<double>(vD.get_x(), 0.987)); EXPECT_TRUE(scalar_eq<double>(vD.get_y(), -0.654));

    Point<double> vE; std::stringstream ssE("500000 -700000"); vE.read(ssE);
    EXPECT_TRUE(scalar_eq<double>(vE.get_x(), 5e5)); EXPECT_TRUE(scalar_eq<double>(vE.get_y(), -7e5));
}