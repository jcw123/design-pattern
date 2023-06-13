#include <iostream>

using namespace std;

const int SIZE = 10;

class A {
    private:
        int count;
        int arr[SIZE];
    public:
        A() {

        }
        A(int c) {
            this->count = c;
        }
        friend int getA(A& a);
        A operator-() {
            A a;
            a.count = -count;
            return a;
        }

        A operator++() {
            count++;
            return *this;
        }

        A operator++(int) {
            A tmp = *this;
            ++*this;
            return tmp;
        }

        A operator+(const A& a);

        A operator+(const int b);

        friend A operator+(const int b, A a);

        bool operator ==(const A& a);

        friend ostream &operator<<(ostream &output, A& d) {
            output << "A.count:" << d.count << endl;
            return output;
        }

        friend istream &operator>>(istream &input, A& d) {
            input >> d.count;
            return input;
        }

        // 重载函数调用运算符
        A operator()(int a, int b, int c) {
            A a1;
            a1.count = a + b + c;
            return a1;
        }

        // 下标运算符重载
        int& operator[](int i) {
            if(i >= SIZE) {
                cout << "i操作数组最大索引" << endl;
                return arr[0];
            }   
            return arr[i];
        }

        // 重载类成员访问运算符
        A* operator ->() {
            return this;
        }

};

// 逻辑运算符重载
bool A::operator==(const A& a) {
    return this->count == a.count;
}

A A::operator+(const A& a) {
    return this->count + a.count;
}

A A::operator+(const int b) {
    return this->count + b;
}

// 加法运算符重载
A operator+(const int b, A a) {
    return a + b;
}

int getA(A& a) {
    return a.count;
}

int main() {
    A a(10);
    A b = -a;
    
    cout << "a:" << getA(a) << endl;
    cout << "b:" << getA(b) << endl;
    A c = ++a;
    cout << "c:" << getA(c) << endl;
    A d = a++;
    cout << "d:" << getA(d) << endl;

    A e1(1);
    A e2(2);
    A f1 = e1 + e2;
    A f2 = e1 + 3;
    A f3 = 3 + e1;
    cout << "f1:" << getA(f1) << endl;
    cout << "f2:" << getA(f2) << endl;
    cout << "f3:" << getA(f3) << endl;  

    A g1(1);
    A g2(1);
    cout << "g1 == g2:" << (g1 == 1) << endl;
    cout << g1 << endl;
    A g3;
    cin >> g3;
    cout << g3 << endl;
    A g4 = g3(1, 2, 3);
    cout << "g4.count:" << getA(g4) << endl;
    cout << "i:" << 0 << ", v:" << g4[0] << endl;
    cout << "i" << 10 << ", v:" << g4[10] << endl;
    return 0;
}