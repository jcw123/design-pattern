#include <iostream>

using namespace std;

class A {
    public:
        virtual void testA() {
            cout << "i am A testA" << endl;
        }

        virtual void testB() = 0;

        void testC() {
            cout << "i am A testC" << endl;
        }
};

class B : public A {
    public:
        void testA() {
            cout << "i am B testA" << endl;
        }

        void testB() {
            cout << "i am B testB" << endl;
        }

        void testC() {
            cout << "i am B testC" << endl;
        }
};

int main() {
    B b;
    b.testA();
    b.testB();
    A* a = &b;
    a ->testC();
    return 0;
}