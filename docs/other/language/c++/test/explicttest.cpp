#include <iostream>

using namespace std;

class P {
    public:
        int a, b;
    public:
        explicit P(int a = 1, int b = 2):a(a), b(b) {
            cout << "first" << endl;
        }
        // P(int a):a(a){
        //     cout << "second" << endl;
        // }
};

int main() {
    P p(1);
    cout << "p.a" << p.a << endl;
    return 0;
}