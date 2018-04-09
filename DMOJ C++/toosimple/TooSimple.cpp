#include <bits/stdc++.h>
using namespace std;

int main() {
    char one; one++;
    char two = one + one;
    char four = two * two;
    char eight = four * two;
    char sixteen = eight * two;
    char thirtytwo = sixteen * two;
    char sixtyfour = thirtytwo * two;
    cout << (char) (sixtyfour + eight); // H
    cout << (char) (sixtyfour + thirtytwo + four + one); // d
    cout << (char) (sixtyfour + thirtytwo + eight + four); // l
    cout << (char) (sixtyfour + thirtytwo + eight + four); // l
    cout << (char) (sixtyfour + thirtytwo + eight + four + two + one); // o
    cout << (char) (thirtytwo + eight + four); // ,
    cout << (char) (thirtytwo);
    cout << (char) (sixtyfour + sixteen + four + two + one); // W
    cout << (char) (sixtyfour + thirtytwo + eight + four + two + one); // o
    cout << (char) (sixtyfour + thirtytwo + sixteen + two); // r
    cout << (char) (sixtyfour + thirtytwo + eight + four); // l
    cout << (char) (sixtyfour + thirtytwo + four); // d
    cout << (char) (thirtytwo + one); // !
    cout << endl;
}
