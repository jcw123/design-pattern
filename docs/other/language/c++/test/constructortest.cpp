#include <iostream>
#include <vector>

using namespace std;

class A {
    private:
        int a;
    public:
        A(){}
        A(int a):a(a){}
        A(const A& o) {
            this->a = o.a;
            cout << "copy constructor" << endl;
        }
        A(A&& o) {
            cout << "move consturctor" << endl;
            this->a = 10;
        }
        int getA() {
            return a;
        }
};

int main() {
    A o(1);
    // cout << "1:" << &o << endl;
    A t1(o);
    cout << "t1:" << &t1 << endl;
    // A t2 = move(o);
    // cout << "t2:" << &t2 << endl;
    // // t2 = t1;
    // // cout << "t2:" << &t2 << endl;
    // A t3(o);
    // cout << "t3:" << &t3 << endl;
    // // A t4 = move(o);
    // // cout << "t4:" << &t4 << endl;
    // // cout << "1:" << &o << endl;
    // // cout << "1.a:" << o.getA() << endl;

    // string str = "Hello";//这里假设我们只需要将str的内容放到vector中，完成以后永远都不需要再用到str
	// vector<string> v;
	// //调用常规的拷贝构造函数，新建字符数组，拷贝数据
	// v.push_back(str);
	// cout << "After copy, str is :" << str << endl;
	// //先把str转为右值引用，然后调用移动构造函数转交所有权
	// v.push_back(move(str));
	// cout << "After move, str is:" << str << endl;
	// cout << "The contents of the vector are:{" << v[0]
	// 	<< "," << v[1] << "}"<<endl;
    return 0;
}