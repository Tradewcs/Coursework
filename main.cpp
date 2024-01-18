#include <iostream>

// #include "List.cpp"
#include "LongInteger.cpp"
using namespace std;

void printList(List<int> lst) {
    for (List<int>::Iterator it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main1() {
    LongInteger lint("-14");

    cout << lint << endl;

    List<int> l1;
    l1.insertBack(1);
    l1.insertBack(2);
    l1.insertBack(3);
    

    for (int num : l1) {
        cout << num << " ";
    }
    cout << endl;


    return 0;
}


int main2() {
    LongInteger a(24);
    LongInteger b = 57;
    LongInteger c = 14;

    // cout << LongInteger::abs(a) << endl;
    // cout << a << endl;

    // a.foo(b);
    // a.remove_heading_zeros();

    a += b;
    // b += a;

    // ++a;

    cout << a << " | " << b << endl;

    return 0;
}

int main() {
    LongInteger a(21);
    LongInteger b(9);

    cout << a << " " << b << endl;

    a += b;

    cout << a << endl;

    return 0;
}