#include <iostream>
#include <ctime>

using namespace std;

int main() {
    time_t t = time(0);
    cout << "cur time:" << t << endl;

    char* dt = ctime(&t);
    cout << "dt:" << dt << endl;
    return 0;
}