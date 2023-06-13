#include <iostream>

using namespace std;

int g = 20;

int main() {
    cout << "g:" << g << endl;
    int g = 10;
    {
        int g = 22;
        cout << "g:" << g << endl;
    }
    cout << "g:" << g << endl;
    return 0;
}