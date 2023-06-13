#include <iostream>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int nums[] = {2, 3, 4};
int& setV(int idx) {
    return nums[idx];
}

int main() {
    int i;
    double b;
    cout << "i:" << &i << ",v:" << i << endl;
    cout << "b:" << &b << ",v:" << b << endl;

    int &ii = i;
    double &bb = b;
    i = 10;
    cout << "ii address:" << &ii << ", v:" << ii << endl;

    int c = 1;
    int d = 2;

    swap(c, d);
    cout << "c:" << c << ", d:" << d << endl;
    setV(1) = 10;
    cout << "idx:1" << nums[1] << endl;
    return 0;
}