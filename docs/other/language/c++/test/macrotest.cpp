#include <iostream>

using namespace std;

#define DEBUG

#define M 0
#define L 1

int main() {
    #ifdef DEBUG
        cout << "debug something" << endl;
    #endif

    #if M
        cout << "test" << endl;
    #else 
        cout << "test3" << endl;
    #endif
    
    return 0;
}