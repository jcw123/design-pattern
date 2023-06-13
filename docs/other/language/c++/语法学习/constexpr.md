# constexpr
常量表达式

## const和constexpr的区别
const表达的是只读的语义，不能通过其修改值，而constexpr表达的是常量的语义

## 基本使用
```cpp
#include <iostream>

using namespace std;

// constexpr int getA(int x) {
//     return x + 1;
// }

class People {
    private:
        int a;
    public:
        constexpr People(int a): a(a) {}
        int getA() {
            return a;
        }
};

int main() {
    int a = 1;
    People p(a);
    cout << "p.a" << p.getA() << endl;

    const int& b = a;
    cout << "b:" << b << endl;
    a = 10;
    cout << "b:" << b << endl;

    // 右值a必须是一个常量表达式，这里会直接报错
    constexpr int c = 1;
    cout << "c:" << c << endl;
    return 0;
}
```

## 参考文档
[常量表达式介绍](http://c.biancheng.net/view/7781.html)