#include <iostream>
#include <string>

using namespace std;

int main() {
    char s1[10] = "1234";
    char s2[10] = "3456";
    char s3[9];
    strcpy(s3, s1);
    cout << "s3:" << s3 << endl;
    strcat(s1, s2);
    cout << "s1:" << s1 << endl;
    cout << "s1 len:" << strlen(s1) << endl;

    string s4 = "123";
    string s5 = "2345";
    cout << "s4.charAt(2):" << s4[2] << endl;
    cout << "s5 len:" << s5.size() << endl;
    return 0;
}