// main.cpp
#include "head.h"
#include "test.cpp"
#include <iostream>
using namespace std;
int main(int argc, char** argv){
    // test template function
    cout << func(10) << endl;
    cout << func(10,1) << endl;
    cout << func(10.) << endl;
    cout << func(10., 1.) << endl;

    // test template class
    Test<int> a(13);
    Test<double> b(14);
    cout << a._a << endl;
    cout << b._a << endl;
    return EXIT_SUCCESS;
}