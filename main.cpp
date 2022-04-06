#include <iostream>
#include "Matrix.hpp"
using namespace zich;

int main() {

    std::cout << "Hello, World!" << std::endl;
    std::vector<double> a = {1, 2, 3,
                             4, 5, 6,
                             7, 8, 9};
    Matrix m{a,3,3};
    try {
        cin >>m;
    }
    catch (const invalid_argument& e){
        cout << e.what() << endl;
        cout << "try a different input\n" << endl;
    }
    return 0;
}
