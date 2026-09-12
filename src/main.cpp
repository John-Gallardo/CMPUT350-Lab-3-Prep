#include "UniquePtr.h"
#include <cassert>
#include <utility>
#include <iostream>

// for testing ->
struct Foo{
    void test() {
        std::cout << "Foo\n";
    }
};

int main() {
    // UniquePtr<int> ptr(new int(5));
    // they test all methods here...

    // 1. test default-initialize & raw pointer constructor
    UniquePtr<int> ptr{new int(5)};
    UniquePtr<int> ptr2;
    assert(ptr2.get() == nullptr);

    // 2. test copy semantics
    // NOTE: I commented them out because the compiler doesn't allow using deleted functions
    //UniquePtr<int> ptr3{ptr2};
    //UniquePtr<int> ptr4{};
    //ptr4 = ptr2;

    // 3. test move semantics
    UniquePtr<int> ptr5{std::move(ptr)};
    assert(ptr.get() == nullptr);
    ptr5 = std::move(ptr2);
    assert(ptr2.get() == nullptr);

    // 4. test dereferencing, ->, .get()
    UniquePtr<int> ptr6{new int(10)};
    UniquePtr<Foo> ptr7;
    assert(*ptr6 == 10);
    assert(ptr6.get() != nullptr);
    ptr7->test(); // should print 'Foo' to terminal

    // 5. test equality, reset, and release
    UniquePtr<int> ptr8{new int(10)};
    assert(!(ptr6 == ptr8));
    ptr6.reset(ptr8.get());  // Valgrind should detect 0 leaks
    assert(ptr6 == ptr8);
    ptr6.release();          // also prevents double free
    assert(ptr6 == nullptr);
    
    // 6. test swap & operator bool()
    UniquePtr<int> ptr9{new int(10)};
    UniquePtr<int> ptr10{new int(20)};
    ptr9.swap(ptr10);
    assert(*ptr10 == 10);
    assert(*ptr9 == 20);
    UniquePtr<int> ptr11{};
    assert(ptr11 == false);
    assert(ptr10 == true);

    // 7. test makeUnique
    UniquePtr<int> uniquePtr1{makeUnique<int>(5)};
    auto uniquePtr2{makeUnique<int>(5)};
    assert(*uniquePtr1 == 5);
    assert(*uniquePtr2 == 5);

    return 0;
}
