#include <iostream>

using namespace std;

void swap1(int, int);
void swap2(int&, int&);
void swap3(int*, int*);

int main() {
    int a = 1, b = 2;
    swap1(a, b);
    cout << "a:" << a << ", b:" << b << endl;
    swap2(a, b);
    cout << "a:" << a << ", b:" << b << endl;
    swap3(&a, &b);
    cout << "a:" << a << ", b:" << b << endl;
}

void swap1(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap2(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap3(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}