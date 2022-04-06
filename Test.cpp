#include "doctest.h"
#include "Matrix.hpp"
#include <string>
#include <sstream>

using namespace zich;
using namespace std;


TEST_CASE("valid input") {

    stringstream stream;
//test all the operators on 3*3 square matrices
    std::vector<double> a = {1, 2, 3,
                             4, 5, 6,
                             7, 8, 9};

    std::vector<double> b = {2,0, -5,
                             6, -3, 4,
                             -6, 0, 9};


    Matrix aSquare{a, 3, 3};
    Matrix bSquare{b, 3, 3};
    stream <<-bSquare;
    CHECK((stream.str())=="[-2 0 5]\n"
                          "[-6 3 -4]\n"
                          "[6 0 -9]\n");
    stream.str("");
    stream <<aSquare+bSquare;
    CHECK(stream.str()=="[3 2 -2]\n"
                        "[10 2 10]\n"
                        "[1 8 18]\n");
    Matrix aTemp=+aSquare;
    aTemp+=bSquare;
    stream.str("");
    stream <<aTemp;
    CHECK(stream.str()=="[3 2 -2]\n"
                         "[10 2 10]\n"
                         "[1 8 18]\n");
    stream.str("");
    stream <<aSquare-bSquare;
    CHECK(stream.str()=="[-1 2 8]\n"
                        "[-2 8 2]\n"
                        "[13 8 0]\n");
    aTemp=+aSquare;
    aTemp-=bSquare;
    stream.str("");
    stream <<aTemp;
    CHECK(stream.str()=="[-1 2 8]\n"
                         "[-2 8 2]\n"
                         "[13 8 0]\n");
    stream.str("");
    stream <<aSquare*bSquare;
    CHECK(stream.str()=="[-4 -6 30]\n"
                        "[2 -15 54]\n"
                        "[8 -24 78]\n");
    stream.str("");
    stream <<-3*aSquare;
    CHECK(stream.str()=="[-3 -6 -9]\n"
                        "[-12 -15 -18]\n"
                        "[-21 -24 -27]\n");

    aTemp=+aSquare;
    aTemp*=-3;
    stream.str("");
    stream <<aTemp;
    CHECK(stream.str()=="[-3 -6 -9]\n"
                        "[-12 -15 -18]\n"
                        "[-21 -24 -27]\n");
    stream.str("");
    stream <<bSquare*4;
    CHECK(stream.str()=="[8 0 -20]\n"
                        "[24 -12 16]\n"
                        "[-24 0 36]\n");
    stream.str("");
    stream <<aSquare++;
    CHECK(stream.str()=="[1 2 3]\n"
                        "[4 5 6]\n"
                        "[7 8 9]\n");
    stream.str("");
    stream <<aSquare;
    CHECK(stream.str()=="[2 3 4]\n"
                        "[5 6 7]\n"
                        "[8 9 10]\n");
    stream.str("");
    stream <<++aSquare;
    CHECK(stream.str()=="[3 4 5]\n"
                        "[6 7 8]\n"
                        "[9 10 11]\n");

    //check comparison operators on 3*3 square matrices
    aTemp=+aSquare;
    CHECK(aTemp==aSquare);
    CHECK(aTemp!=bSquare);
    CHECK(aSquare>bSquare);
    CHECK(aSquare>=bSquare);
    CHECK(bSquare<aSquare);
    CHECK(bSquare<=aSquare);

    CHECK_FALSE(aTemp!=aSquare);
    CHECK_FALSE(aTemp==bSquare);
    CHECK_FALSE(aSquare<bSquare);
    CHECK_FALSE(aSquare<=bSquare);
    CHECK_FALSE(bSquare>aSquare);
    CHECK_FALSE(bSquare>=aSquare);


//test all the operators on non-square matrices 3*4 and 4*3
    std::vector<double> c = {2,5,-3,6,
                             1,6,-2,-7,
                             0,2,-6,8};

    std::vector<double> c2 = {5,1,7,-4,
                              3,6,-1,7,
                              0,-3,-5,1};

    std::vector<double> d = {1,4,7,
                             3,-1,-8,
                             0,4,-6,
                             0,2,-7};
    Matrix cColums{c, 3, 4};
    Matrix cColums2{c2, 3, 4};
    Matrix dRows{d, 4, 3};

    stream.str("");
    stream <<-dRows;
    CHECK(stream.str()=="[-1 -4 -7]\n"
                        "[-3 1 8]\n"
                        "[0 -4 6]\n"
                        "[0 -2 7]\n");
    stream.str("");
    stream <<cColums+cColums2;
    CHECK(stream.str()=="[7 6 4 2]\n"
                        "[4 12 -3 0]\n"
                        "[0 -1 -11 9]\n");

    Matrix cTemp=+cColums;
    cTemp+=cColums2;
    stream.str("");
    stream <<cTemp;
    CHECK(stream.str()=="[7 6 4 2]\n"
                         "[4 12 -3 0]\n"
                         "[0 -1 -11 9]\n");

    stream.str("");
    stream <<cColums-cColums2;
    CHECK(stream.str()=="[-3 4 -10 10]\n"
                        "[-2 0 -1 -14]\n"
                        "[0 5 -1 7]\n");


    cTemp=+cColums;
    cTemp-=cColums2;
    stream.str("");
    stream <<cTemp;
    CHECK(stream.str()=="[-3 4 -10 10]\n"
                         "[-2 0 -1 -14]\n"
                         "[0 5 -1 7]\n");

    stream.str("");
    stream <<cColums*dRows;
    CHECK(stream.str()=="[17 3 -50]\n"
                        "[19 -24 20]\n"
                        "[6 -10 -36]\n");
    stream.str("");
    stream <<-5*cColums2;
    CHECK(stream.str()=="[-25 -5 -35 20]\n"
                        "[-15 -30 5 -35]\n"
                        "[0 15 25 -5]\n");

    cTemp=+cColums2;
    cTemp*=-5;
    stream.str("");
    stream <<cTemp;
    CHECK(stream.str()=="[-25 -5 -35 20]\n"
                        "[-15 -30 5 -35]\n"
                        "[0 15 25 -5]\n");
    stream.str("");
    stream <<dRows*6;
    CHECK(stream.str()=="[6 24 42]\n"
                        "[18 -6 -48]\n"
                        "[0 24 -36]\n"
                        "[0 12 -42]\n");
    stream.str("");
    stream <<cColums--;
    CHECK(stream.str()=="[2 5 -3 6]\n"
                        "[1 6 -2 -7]\n"
                        "[0 2 -6 8]\n");
    stream.str("");
    stream <<cColums;
    CHECK(stream.str()=="[1 4 -4 5]\n"
                        "[0 5 -3 -8]\n"
                        "[-1 1 -7 7]\n");
    stream.str("");
    stream <<--cColums;
    CHECK(stream.str()=="[0 3 -5 4]\n"
                       "[-1 4 -4 -9]\n"
                       "[-2 0 -8 6]\n");


    //check comparison operators on non-square matrices 3*4 and 4*3

    cTemp=+cColums;
    CHECK(cTemp==cColums);
    CHECK(cColums!=cColums2);
    CHECK(cColums2>cColums);
    CHECK(cColums2>=cColums);
    CHECK(cColums<cColums2);
    CHECK(cColums<=cColums2);

    CHECK_FALSE(cTemp!=cColums);
    CHECK_FALSE(cColums==cColums2);
    CHECK_FALSE(cColums2<cColums);
    CHECK_FALSE(cColums2<=cColums);
    CHECK_FALSE(cColums>cColums2);
    CHECK_FALSE(cColums>=cColums2);

}

TEST_CASE("exceptions check") {
    std::vector<double> c = {2,5,-3,6,
                             1,6,-2,-7,
                             0,2,-6,8};

    std::vector<double> d = {1,4,7,
                             3,-1,-8,
                             0,4,-6,
                             0,2,-7};
    std::vector<double> a = {1, 2, 3,
                             4, 5, 6,
                             7, 8, 9};

    Matrix aSquare{a, 3, 3};
    Matrix cColums{c, 3, 4};
    Matrix dRows{d, 4, 3};

//    create matrices with wrong size of row\column
    CHECK_THROWS(Matrix(a,3,4));
    CHECK_THROWS(Matrix(a,4,3));
    CHECK_THROWS(Matrix(a,4,4));
    CHECK_THROWS(Matrix(c,4,4));
    CHECK_THROWS(Matrix(c,3,5));

//check operators on matrices with different size
    CHECK_THROWS(cColums+dRows);
    CHECK_THROWS(cColums-dRows);
    CHECK_THROWS(cColums-=dRows);
    CHECK_THROWS(cColums+=dRows);
    CHECK_THROWS(aSquare*dRows);
    CHECK_THROWS(cColums*aSquare);

    CHECK_THROWS(dRows+cColums);
    CHECK_THROWS(dRows+=cColums);
    CHECK_THROWS(dRows-cColums);
    CHECK_THROWS(dRows-=cColums);

//check comparison operators on matrices with different size
    CHECK_THROWS(bool ans=cColums==dRows);
    CHECK_THROWS(bool ans=cColums!=dRows);
    CHECK_THROWS(bool ans=cColums>dRows);
    CHECK_THROWS(bool ans=cColums>=dRows);
    CHECK_THROWS(bool ans=cColums<dRows);
    CHECK_THROWS(bool ans=cColums<=dRows);

    CHECK_THROWS(bool ans=aSquare==dRows);
    CHECK_THROWS(bool ans=aSquare!=dRows);
    CHECK_THROWS(bool ans=aSquare>dRows);
    CHECK_THROWS(bool ans=aSquare>=dRows);
    CHECK_THROWS(bool ans=aSquare<dRows);
    CHECK_THROWS(bool ans=aSquare<=dRows);

}
