#include <iostream>
using namespace std;

int main()
{
    int radius;
    double volume;

    cout << "Enter Radius:" << endl;
    cin >> radius;
    radius = radius * radius * radius;
    volume = radius * 3.14;
    cout << "The volume is: " << volume;
    return 0;
}
