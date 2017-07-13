#ifndef TESTS_H
#define TESTS_H

#include "array.h"

#include <iostream>

inline int runTests() {
  using namespace std;

  // print
  cout << "print" << endl;
  cout << (Array::randomize(Array(2, 2), 0, 1) * 2) + -1 << endl;

  // sum
  {
    cout << "sum" << endl;
    Array one({{2, 2},
               {2, 2}});
    Array two({{3, 4},
               {5, 6}});
    cout << one + -1 << endl;

    cout << "sum 2" << endl;
    cout << one + -1 << endl;
  }

  // dev
  {
    cout << "devide" << endl;
    Array one({{2, 2},
               {2, 2}});
    Array two({{0.5, 0.5},
               {2, 2}});
    cout << one / two << endl;

    cout << "devide 2" << endl;
    Array three({{0.5, 0.5},
               {2, 2}});
    cout << 1 / one << endl;
  }

  {
    cout << "multiply" << endl;
    Array one({{2, 2},
               {2, 2}});
    Array two({{0.5, 0.5},
               {2, 2}});
    cout << one * two << endl;

    cout << "multiply 2" << endl;
    Array three({{2, 2},
               {2, 2}});
    cout << one * 2 << endl;
  }

  // sum
  {
    cout << "dot" << endl;
    Array one({{1, 2, 3},
               {4, 5, 6}});
    Array two({{7, 8},
               {9, 10},
              {11, 12}});
    cout << one.dot(two) << endl;
  }

  {
    cout << "substract" << endl;
    Array one({{2, 2},
               {2, 2}});
    Array two({{3, 4},
               {5, 6}});
    cout << one - two << endl;

  }

  return 0;
}

#define TEST_MAIN int main() { return runTests(); }

#endif // TESTS_H
