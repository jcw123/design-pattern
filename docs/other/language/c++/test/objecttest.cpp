#include <iostream>

using namespace std;

class A {
    public:
        int a;
        int b;
        void set(int a, int b);
        int getA();
};

void A::set(int a, int b) {
    this->a = a;
    this->b = b;
}

int A::getA() {
    return this->a;
}

class B: public A {
    public:
        int* getAll() {
            static int all[2];
            all[0] = a;
            all[1] = b;
            return all;
        }
};

class C {
    private:
        int a;
        int b;
    public:
        C();
        C(int, int);
        ~C();
        int getA() {
            return a;
        }
};

C::C() {
    cout << "i am C class default constructor" << endl;
}

C::C(int a, int b) {
    this->a = a;
    cout << "i am C class two param constructor" << endl;
}

C::~C() {
    cout << "i am ~c" << endl;
}

class D {
    public:
        D();
        D(const D &obj);
        ~D();
        void setPtr(int* p) {
            ptr = p;
        }
        int getPtrV() {
            return *ptr;
        }

    private:
        int* ptr;
};

D::D() {
    cout << "调用D的构造函数" << endl;
}

D::D(const D &obj) {
    cout << "调用D的拷贝构造函数" << endl;
    ptr = new int;
    *ptr = *obj.ptr;
}

D::~D() {
    cout << "调用D的析构函数" << endl;
    delete ptr;
}

class E {
    private:
        int a;
    public:
        friend int visitA(E &d);
        E(int a) {
            this->a = a;
        }
};

int visitA(E & d) {
    return d.a;
}

class FF {
    private:
        int a;
    public:
        static int b;
        static void visit() {
            cout << "b:" << FF::b << endl;
        }
 };

int FF::b = 0;
int main() {
    A a1;
    cout << "a1.a:" << a1.a << endl;

    a1.a = 2;
    cout << "a1.a:" << a1.a << endl;

    a1.set(1, 2);
    cout << "a1.a:" << a1.a << endl;

    B b;
    b.a = 1;
    b.b = 2;
    int* c = b.getAll();
    cout << "a:" << c[0] << ", b:" << c[1] << endl;

    C c1;
    C c2(2, 3);
    cout << "c1.a:" << c1.getA() << endl;
    cout << "c2.a:" << c2.getA() << endl;

    D d1;
    int a = 10;
    d1.setPtr(&a);
    D d2(d1);
    cout << "d2.ptrV:" << d2.getPtrV() << endl;

    E e(1);
    cout << "e.a:" << visitA(e) << endl; 

    FF f;
    cout << "b:" << FF::b << endl;
    FF::visit();

    return 0;

}