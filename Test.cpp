#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;
using namespace std;


TEST_CASE("valid input") {

//test all the operators on 3*3 square matrices
    std::vector<double> a = {1, 2, 3,
                             4, 5, 6,
                             7, 8, 9};

    std::vector<double> b = {2,0, -5,
                             6, -3, 4,
                             -6, 0, 9};


    Matrix aS{a, 3, 3};
    Matrix bS{b, 3, 3};

    CHECK((-bS).toString()=="[-2 0 5]\n"
                            "[-6 3 -4]\n"
                            "[6 0 -9]\n");

    CHECK((aS+bS).toString()=="[3 2 -2]\n"
                            "[10 2 10]\n"
                            "[1 8 18]\n");
    Matrix aT=+aS;
    aT+=bS;
    CHECK(aT.toString()=="[3 2 -2]\n"
                         "[10 2 10]\n"
                         "[1 8 18]\n");

    CHECK((aS-bS).toString()=="[-1 2 8]\n"
                            "[-2 8 2]\n"
                            "[13 8 0]\n");
    aT=+aS;
    aT-=bS;
    CHECK(aT.toString()=="[-1 2 8]\n"
                         "[-2 8 2]\n"
                         "[13 8 0]\n");

    CHECK((aS*bS).toString()=="[-4 -6 30]\n"
                            "[2 -15 54]\n"
                            "[8 -24 78]\n");

    CHECK((-3*aS).toString()=="[-3 -6 -9]\n"
                              "[-12 -15 -18]\n"
                              "[-21 -24 -27]\n");

    aT=+aS;
    aT*=-3;
    CHECK((aT).toString()=="[-3 -6 -9]\n"
                           "[-12 -15 -18]\n"
                           "[-21 -24 -27]\n");

    CHECK((bS*4).toString()=="[8 0 -20]\n"
                             "[24 -12 16]\n"
                             "[-24 0 36]\n");

    CHECK((aS++).toString()=="[1 2 3]\n"
                            "[4 5 6]\n"
                            "[7 8 9]\n");

    CHECK((aS).toString()=="[2 3 4]\n"
                          "[5 6 7]\n"
                          "[8 9 10]\n");

    CHECK((++aS).toString()=="[3 4 5]\n"
                            "[6 7 8]\n"
                            "[9 10 11]\n");

    //check comparison operators on 3*3 square matrices
    aT=+aS;
    CHECK(aT==aS);
    CHECK(aT!=bS);
    CHECK(aS>bS);
    CHECK(aS>=bS);
    CHECK(bS<aS);
    CHECK(bS<=aS);

    CHECK_FALSE(aT!=aS);
    CHECK_FALSE(aT==bS);
    CHECK_FALSE(aS<bS);
    CHECK_FALSE(aS<=bS);
    CHECK_FALSE(bS>aS);
    CHECK_FALSE(bS>=aS);


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
    Matrix cC{c, 3, 4};
    Matrix cC2{c2, 3, 4};
    Matrix dR{d, 4, 3};

    CHECK((-dR).toString()=="[-1 -4 -7]\n"
                            "[-3 1 8]\n"
                            "[0 -4 6]\n"
                            "[0 -2 7]\n");

    CHECK((cC+cC2).toString()=="[7 6 4 2]\n"
                               "[4 12 -3 0]\n"
                               "[0 -1 -11 9]\n");

    Matrix cT=+cC;
    cT+=cC2;
            CHECK(cT.toString()=="[7 6 4 2]\n"
                                 "[4 12 -3 0]\n"
                                 "[0 -1 -11 9]\n");


    CHECK((cC-cC2).toString()=="[-3 4 -10 10]\n"
                               "[-2 0 -1 -14]\n"
                               "[0 5 -1 7]\n");


    cT=+cC;
    cT-=cC2;
    CHECK(cT.toString()=="[-3 4 -10 10]\n"
                         "[-2 0 -1 -14]\n"
                         "[0 5 -1 7]\n");


    CHECK((cC*dR).toString()=="[17 3 -50]\n"
                              "[19 -24 20]\n"
                              "[6 -10 -36]\n");

    CHECK((-5*cC2).toString()=="[-25 -5 -35 20]\n"
                               "[-15 -30 5 -35]\n"
                               "[0 15 25 -5]\n");

    cT=+cC2;
    cT*=-5;
    CHECK((cT).toString()=="[-25 -5 -35 20]\n"
                           "[-15 -30 5 -35]\n"
                           "[0 15 25 -5]\n");

    CHECK((dR*6).toString()=="[6 24 42]\n"
                             "[18 -6 -48]\n"
                             "[0 24 -36]\n"
                             "[0 12 -42]\n");

    CHECK((cC--).toString()=="[2 5 -3 6]\n"
                             "[1 6 -2 -7]\n"
                             "[0 2 -6 8]\n");

    CHECK((cC).toString()=="[1 4 -4 5]\n"
                           "[0 5 -3 -8]\n"
                           "[-1 1 -7 7]\n");

    CHECK((--cC).toString()=="[0 3 -5 4]\n"
                             "[-1 4 -4 -9]\n"
                             "[-2 0 -8 6]\n");


    //check comparison operators on non-square matrices 3*4 and 4*3

    cT=+cC;
    CHECK(cT==cC);
    CHECK(cC!=cC2);
    CHECK(cC2>cC);
    CHECK(cC2>=cC);
    CHECK(cC<cC2);
    CHECK(cC<=cC2);

    CHECK_FALSE(cT!=cC);
    CHECK_FALSE(cC==cC2);
    CHECK_FALSE(cC2<cC);
    CHECK_FALSE(cC2<=cC);
    CHECK_FALSE(cC>cC2);
    CHECK_FALSE(cC>=cC2);

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

    Matrix aS{a, 3, 3};
    Matrix cC{c, 3, 4};
    Matrix dR{d, 4, 3};

//    create matrices with wrong size of row\column
    CHECK_THROWS(Matrix* t=new Matrix(a,3,4));
    CHECK_THROWS(Matrix* t=new Matrix(a,4,3));
    CHECK_THROWS(Matrix* t=new Matrix(a,4,4));
    CHECK_THROWS(Matrix* t=new Matrix(c,4,4));
    CHECK_THROWS(Matrix* t=new Matrix(c,3,5));

//check operators on matrices with different size
    CHECK_THROWS(cC+dR);
    CHECK_THROWS(cC-dR);
    CHECK_THROWS(cC-=dR);
    CHECK_THROWS(cC+=dR);
    CHECK_THROWS(aS*dR);
    CHECK_THROWS(cC*aS);

    CHECK_THROWS(dR+cC);
    CHECK_THROWS(dR+=cC);
    CHECK_THROWS(dR-cC);
    CHECK_THROWS(dR-=cC);

//check comparison operators on matrices with different size
    CHECK_THROWS(bool ans=cC==dR);
    CHECK_THROWS(bool ans=cC!=dR);
    CHECK_THROWS(bool ans=cC>dR);
    CHECK_THROWS(bool ans=cC>=dR);
    CHECK_THROWS(bool ans=cC<dR);
    CHECK_THROWS(bool ans=cC<=dR);

    CHECK_THROWS(bool ans=aS==dR);
    CHECK_THROWS(bool ans=aS!=dR);
    CHECK_THROWS(bool ans=aS>dR);
    CHECK_THROWS(bool ans=aS>=dR);
    CHECK_THROWS(bool ans=aS<dR);
    CHECK_THROWS(bool ans=aS<=dR);

}
