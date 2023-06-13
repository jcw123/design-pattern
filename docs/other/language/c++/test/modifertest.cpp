#include <iostream>

using namespace std;

void staticTest();

int main() {
    for(int i = 0; i < 2; i++) {
        staticTest();
    }
    return 0;
}

void staticTest() {
    static int a = 0;
    a++;
    cout << "a:" << a << endl;
}