#include <iostream>

using namespace std;

thread_local int x;

class X {
    static thread_local std::string s;
};

int main() {
    return 0;
}