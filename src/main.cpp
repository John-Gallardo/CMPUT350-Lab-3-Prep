#include "UniquePtr.h"
#include <cassert>

int main() {
    // UniquePtr<int> ptr(new int(5));
    // they test all methods here...

    // 1. test default-initialize & raw pointer constructor
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptr2;



    return 0;
}
