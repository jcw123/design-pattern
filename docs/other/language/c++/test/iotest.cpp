#include <iostream>

using namespace std;

int main() {
    int a;
    string b;
    cin >> a >> b;
    cout << "a:" << a << ", b:" << b << endl;

    cerr << "err:" << "i am error" << endl;

    clog << "log:" << "print ok" << endl;
    return 0;
}