#include <iostream>

using namespace std;

class PTest {
    private:
        int a;
    public:
        PTest(int a): a(a){}
};

int* aa(int*);

PTest&& testP();

int main() {
    int v = 10;
    cout << "v:" << v << ", v address:" << &v << endl;

    int *p;
    p = &v;
    cout << "p:" << p << ", p address:" << &p << endl;

    int* *q;
    q = &p;
    cout << "q:" << q << ", q address:" << &q << endl;

    cout << "v:" << **q << ", v address:" << *q << endl;

    int *t;
    cout << "t:" << t << endl;

    int *u = NULL;
    cout << "u:" << u << endl;

    int arr1[] = {3, 20, 200};
    int *pp = arr1;
    int i = 0;
    while(pp <= &arr1[2]) {
        cout << "arr[" << i << "]==";
        cout << *pp << endl;
        i++;
        pp++; 
    }

    int arr2[] = {2, 3, 4};
    *arr2 = 5;

    *(arr2 + 2) = 7;

    for(int i = 0; i < 3; i++) {
        cout << "i:" << i << ", v:" << *(arr2 + i) << endl;
    }

    int a = 1, b = 3, c = 2;
    int* arr3[] = {&a, &b , &c};
    for (int i = 0; i < 3; i++) {
        cout << "i:" << i << "address:" << arr3[i] << ", v:" << *arr3[i] << endl;
    }

    char * arr4[] = {"test1", "test2"};
    for(int i = 0; i < 2; i++) {
        cout << "i:" << i << ", v:" << arr4[i] << endl;
    }

    int tt = 2;
    int *z;
    z = aa(&tt);
    cout << "z address:" << z << endl;

    PTest&& pTest2 = testP();
    cout << "another p address:" << &pTest2 << endl;
    return 0;
}

PTest&& testP() {
    PTest p(1);
    cout << "p address:" << &p << endl;
    return move(p);
}

int* aa(int* v) {
    int t = 2;
    int *p = &t;
    return p;
}