#include <iostream>
#include <limits>
using namespace std;

// DisplayMenu is in the binary, but main never calls it.
// Its six strings have no newline, so a call would print one long line.
// The menu the user actually sees is printed from main, and those copies end in '\n'.
void DisplayMenu() {
    cout << "----------------" << endl;
    cout << "- 1)Add -" << endl;
    cout << "- 2)Subtract -" << endl;
    cout << "- 3)Multiply -" << endl;
    cout << "- 4)Exit -" << endl;
    cout << "----------------" << endl;
}

// Read one int. The original cin >> int does not check the stream.
// A letter sets failbit and leaves the variable unchanged, so the loop never ends.
// Fix: on failure, clear the stream, drop the rest of the line, and return false.
bool readInt(int &value) {
    if (cin >> value) {
        return true;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

int main() {
    // choice is the int at -0x14(%rbp). The binary sets it to 0.
    // num1 (-0x10) and num2 (-0xc) are not initialized in the binary.
    // A failed read would then add, subtract, or divide stack garbage.
    // Fix: give both a value before any read.
    int choice = 0;
    int num1 = 0;
    int num2 = 0;

    // Vulnerability: the loop is cmpl $5. The menu string says Exit is 4.
    // Choosing 4 fails every compare and jumps back. Only 5, which is not
    // on the menu, reaches the return. Fix: leave when choice is 4.
    while (choice != 4) {
        DisplayMenu();

        if (!readInt(choice)) {
            cout << "Enter a number from 1 to 4." << endl;
            choice = 0;
            continue;
        }

        if (choice < 1 || choice > 4) {
            cout << "Enter a number from 1 to 4." << endl;
            choice = 0;
            continue;
        }

        if (choice == 4) {
            break;
        }

        if (!readInt(num1) || !readInt(num2)) {
            cout << "Enter two integers." << endl;
            continue;
        }

        // Each original operation loads both ints into registers first.
        // x86 cannot sub, add, or idiv directly between two memory locations.
        // The print path always uses the .rodata string " - ", even for add and divide.
        long long wide = 0;
        char op = '?';

        if (choice == 1) {
            // Vulnerability: this block is subl, so menu item "Add" subtracts.
            // Fix: add, and do it in a wider type so a 32-bit overflow is caught.
            op = '+';
            wide = (long long)num1 + (long long)num2;
        } else if (choice == 2) {
            // Vulnerability: this block is addl, so menu item "Subtract" adds.
            op = '-';
            wide = (long long)num1 - (long long)num2;
        } else {
            // Vulnerability: this block is cltd / idivl, so "Multiply" divides.
            // idivl by 0 faults the process. INT_MIN / -1 faults it too.
            // Fix: multiply, which is what the menu string promises, and reject
            // a product that does not fit in a 32-bit int.
            op = '*';
            wide = (long long)num1 * (long long)num2;
        }

        if (wide > numeric_limits<int>::max() || wide < numeric_limits<int>::min()) {
            cout << "Result does not fit in an int." << endl;
            continue;
        }

        cout << num1 << " " << op << " " << num2 << " = " << (int)wide << endl;
    }

    return 0;
}
