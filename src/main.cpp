#include "UniquePtr.h"
#include <cassert>
#include <utility>

int main() {
    // UniquePtr<int> ptr(new int(5));
    // they test all methods here...

    // 1. test default-initialize & raw pointer constructor
    UniquePtr<int> ptr{new int(5)};
    UniquePtr<int> ptr2;

    // 2. test copy semantics
    //UniquePtr<int> ptr3{ptr2};
    //UniquePtr<int> ptr4{};
    //ptr4 = ptr2;

    // 3. test move semantics
    UniquePtr<int> ptr5{std::move(ptr)};
    assert(ptr.get() == nullptr);
    ptr5 = std::move(ptr2);
    assert(ptr2.get() == nullptr);

    return 0;
}
