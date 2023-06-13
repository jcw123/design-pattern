#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;

template <typename T> inline T const& Max(T const& a, T const& b) {
    return a < b ? b : a;
}

template <class T> class Stack {
    private:
        vector<T>  eles;
    public:
        void push(T const& e);
        void pop();
        T top() const;
        bool empty() const {
            return eles.empty();
        }

};

template <class T> void Stack<T>::push(T const& e) {
    eles.push_back(e);
}

template <class T> void Stack<T>::pop() {
    if(eles.empty()) {
        throw out_of_range("Stack<>.pop():empty stack");
    }
    eles.pop_back();
}

template <class T> T Stack<T>::top() const {
    if(eles.empty()) {
        throw out_of_range("Stack<>.top():empty stack");
    }
    return eles.back();
}

int main() {
    cout << "max(3, 4):" << Max(3, 4) << endl;
    cout << "max('abc', 'def'):" << Max("abc", "def") << endl;

    Stack<string> stack;
    stack.push("1");
    stack.push("2");
    while(!stack.empty()) {
        cout << "v:" << stack.top() << endl;
        stack.pop();
    }
    return 0;
}