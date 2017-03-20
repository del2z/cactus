//------------------------------------------------------------------------------
// Unit test of Data matrix
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/data_vector.h"
#include "core/data_matrix.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;
using namespace cactus;

TEST(Entry_test, All) {
    Entry entry = Entry();//   Entry(3, -36.0);
    cout << entry.index() << ", " << entry.value() << endl;
    entry.set(0, 18.5);
    cout << entry.index() << ", " << entry.value() << endl;
    entry.set(Entry(4, 3));
    cout << entry.index() << ", " << entry.value() << endl;
}

TEST(DVector_test, All) {
    DVector dvec = DVector();
    cout << dvec.size() << endl;
    dvec.append(1, 12);
    dvec.append(3, 36);
    dvec.append(8, 21);
    dvec.append(6, 42);
    dvec.append(Entry(15, 24));
    cout << dvec.size() << endl;
    print(dvec);
    DVector uvec = DVector(dvec, 32);
    cout << uvec.size() << endl;
    print(uvec);
    cout << uvec.getValue(11) << ", " << uvec.getValue(8) << endl;
    SMatrix smat = SMatrix();
    smat.append(dvec);
    print(smat);
    DMatrix dmat = DMatrix();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv); 
    
    // Runs all tests using Google Test.
    return RUN_ALL_TESTS(); 
}
