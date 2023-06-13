#include <iostream>

using namespace std;

void test1(int[]);

void test2(int*);

void test1(int arr[]) {
    cout << "arr1" << arr << endl;
    arr[1] = 9;
}

void test2(int *arr) {
    cout << "arr2:" << arr << endl;
    arr[1] = 12;
}

int main() {
    int arr[10];
    arr[1] = 10;
    cout << "arr:" << arr[1] << endl;
    test1(arr);
    cout << "v1:" << arr[1] << endl;
    test2(arr);
    cout << "v1:" << arr[1] << endl;
}