# explict关键字

构造函数使用时，默认会支持隐式类型转换，通过加入explict关键字，可以禁止隐式类型转换

## 使用说明
```cpp
#include <iostream>

using namespace std;

class P {
    public:
        int a, b;
    public:
        // 使用
        explicit P(int a = 1, int b = 2):a(a), b(b) {
            cout << "first" << endl;
        }
        // P(int a):a(a){
        //     cout << "second" << endl;
        // }
};

int main() {
    // P p = 2; 如果不用explicit生成构造函数，可以这样使用
    P p(1);
    cout << "p.a" << p.a << endl;
    return 0;
}
```