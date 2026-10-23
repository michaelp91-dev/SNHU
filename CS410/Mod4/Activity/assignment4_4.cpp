#include <iostream>
using namespace std;

int main()
{
    long n, hex = 0, place = 1, rem;

    cout << "Enter the binary number: " << endl;
    cin >> n;
    while (n != 0) {
        rem = n % 10;
        hex += rem * place;
        place *= 2;
        n /= 10;
    }
    cout << "Equivalent hexadecimal value: " << hex << endl;
    return 0;
}
