#include "shared_ptr.hpp"

int main() {
    shared_ptr<int> b;
    shared_ptr<int> a{new int(5)};
    std::cout << *a << " \n";
    std::cout << "A - refs: " << a.useCount() << " \n";
    std::cout << "B - refs: " << b.useCount() << " \n";
    b = a;
    std::cout << "A - refs: " << a.useCount() << " \n";
    std::cout << "B - refs: " << b.useCount() << " \n";
    a = new int(6);
    std::cout << *a << " \n";
    std::cout << "A - refs: " << a.useCount() << " \n";
    std::cout << "B - refs: " << b.useCount() << " \n";
    shared_ptr<int> c{new int(7)};
    a = c;
    std::cout << *a << " \n";
    std::cout << "A - refs: " << a.useCount() << " \n";
    std::cout << "B - refs: " << b.useCount() << " \n";
    std::cout << "C - refs: " << c.useCount() << " \n";
    shared_ptr<int> d(c);
    std::cout << "C - refs: " << c.useCount() << " \n";
    std::cout << "D - refs: " << d.useCount() << " \n";
    int* ptrTmp = new int{9};
    d.reset(ptrTmp);
    std::cout << *d;
    return 0;
}