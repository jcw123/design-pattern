#include <iostream>

using namespace std;

void test();

void test2();

void test3();

void func(int *p);

int main() {
    int a = 1;
    int b = a;
    int &c = a;
    int* d = &a;
    int *e;
    int *f = NULL;
    cout << "a地址：" << &a << endl;
    cout << "b地址：" << &b << endl;
    cout << "c地址：" << &c << endl;
    cout << "d地址：" << &d << ", d标识的值：" << d << ", d地址指向的值：" << *d << endl;
    cout << "e的值：" << e << endl;
    cout << "f的值：" << f << endl;
    if(e) {
        cout << "SUCCESS" << endl;
    }
    test();
    test2();
    test3();
    return 0;
}

void test() {
    const int max = 3;
    int arr[max] = {100, 10, 20};
    for(int i = 0; i < max; i++) {
        *arr = i;
        cout << i << ":" << arr << ", " << arr[0] << endl;
    }
}

void test2() {
    char *p = "hello world";
    // while(p) {
    //     cout << *p << endl;
    //     p++;
    // }
}

void test3() {
    int a = 1;
    func(&a);
}

void func(int *p) {
    cout << "p地址：" << &p << endl;
    cout << "p的值：" << p << endl;
    cout << "p指向的值" << *p << endl;
    cout << "p指向的值" << p[0] << endl;
}