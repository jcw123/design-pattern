#include <iostream>

using namespace std;

// 变量的声明
extern int a, b;

int test();

int main() {
    // 变量的定义
    int a = 1;
    int b = 2;
    cout << "a:" << a << ", b:" << b << endl;
    test();
    return 0;
}

int test() {
    cout << "i am test" << endl;
}