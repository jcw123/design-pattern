#include <iostream>
#include <cstring>

using namespace std;

struct People {
    char name[10];
    int age;
};

typedef People P;

int main() {
    P p1;
    P p2;
    strcpy(p1.name, "test");
    p1.age = 100;
    cout << "p1.name:" << p1.name << endl;
    cout << "p1.age" << p1.age << endl;
    return 0;
}