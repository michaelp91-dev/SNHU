#include <cstring>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

char name1[] = "Bob Jones";
char name2[] = "Sarah Davis";
char name3[] = "Amy Friendly";
char name4[] = "Johnny Smith";
char name5[] = "Carol Spears";

int num1 = 1;
int num2 = 2;
int num3 = 1;
int num4 = 1;
int num5 = 2;

char username[20];
// Vulnerability: password[] is initialized with "123" and never read.
// The check below compares against the same literal. Both copies are
// plaintext in the binary. Not fixed. This file has no credential store,
// and swapping in a different literal would leave the same flaw.
char password[] = "123";
int choice = 0;
int changechoice = 0;
int newservice = 0;
int answer = 0;

void resetCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int CheckUserPermissionAccess() {
    string entered;
    string nameInput;
    cout << "Enter your username: \n";
    // Vulnerability: the original read was cin >> username into char[20].
    // That extraction does not stop at 19 characters. In Project1.o, username
    // is the first object in .bss (size 0x14) and choice starts at the next
    // byte, then changechoice, newservice, and answer. A long name writes
    // into those ints. password[] is in .data, so the overflow does not land
    // on it.
    // Fix: read into a string, then copy at most 19 characters and add the null.
    if (!(cin >> nameInput)) {
        resetCin();
        return 2;
    }
    strncpy(username, nameInput.c_str(), 19);
    username[19] = '\0';

    cout << "Enter your password: \n";
    if (!(cin >> entered)) {
        resetCin();
        return 2;
    }
    // Vulnerability: username was stored above and is never compared.
    // Any name is accepted. Not fixed. There is no account list in this file,
    // and hard-coding one next to "123" would repeat the password flaw.
    // Vulnerability: success is entered.compare("123") == 0. The secret is in
    // the source. Not fixed, for the reason on password[] above.
    if (entered.compare("123") == 0)
        return 1;
    else
        return 2;
}

void DisplayInfo() {
    cout << "  Client's Name    Service Selected (1 = Brokerage, 2 = Retirement)" << endl;
    cout << "1. " << name1 << " selected option " << num1 << endl;
    cout << "2. " << name2 << " selected option " << num2 << endl;
    cout << "3. " << name3 << " selected option " << num3 << endl;
    cout << "4. " << name4 << " selected option " << num4 << endl;
    cout << "5. " << name5 << " selected option " << num5 << endl;
}

void ChangeCustomerChoice() {
    cout << "Enter the number of the client that you wish to change\n";
    if (!(cin >> changechoice)) {
        resetCin();
        cout << "Enter a client number from 1 to 5.\n";
        return;
    }
    cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)\n";
    if (!(cin >> newservice)) {
        resetCin();
        cout << "Enter 1 or 2.\n";
        return;
    }
    // Vulnerability: any int was assigned to num1 through num5. The prompt
    // only defines 1 and 2, and the five clients start at 1, 2, 1, 1, 2.
    // A failed read also left the old newservice in place and set failbit.
    // Fix: require a successful read of 1 or 2 before storing. A client
    // number outside 1 through 5 still does not write.
    if (newservice != 1 && newservice != 2) {
        cout << "Enter 1 or 2.\n";
        return;
    }
    if (changechoice == 1)
        num1 = newservice;
    else if (changechoice == 2)
        num2 = newservice;
    else if (changechoice == 3)
        num3 = newservice;
    else if (changechoice == 4)
        num4 = newservice;
    else if (changechoice == 5)
        num5 = newservice;
    else
        cout << "Enter a client number from 1 to 5.\n";
}

int main() {
    cout << "Created by Michael Puckett" << endl;

    cout << "Hello! Welcome to our Investment Company\n";
    int attempts = 0;
    answer = CheckUserPermissionAccess();
    // Vulnerability: the original loop was while (answer != 1), with another
    // call and no counter. The password is three digits, so the loop is an
    // online guess, and a bad token can also leave the stream failed.
    // Fix: three tries, then leave. The compare against "123" is unchanged.
    while (answer != 1 && attempts < 2) {
        cout << "Invalid Password. Please try again\n";
        attempts++;
        answer = CheckUserPermissionAccess();
    }
    if (answer != 1) {
        cout << "Too many attempts.\n";
        return 1;
    }

    while (choice != 3) {
        cout << "What would you like to do?\n";
        cout << "DISPLAY the client list (enter 1)\n";
        cout << "CHANGE a client's choice (enter 2)\n";
        cout << "Exit the program.. (enter 3)\n";
        // Vulnerability: cin >> choice with no test. A letter sets failbit
        // and leaves choice unchanged, so while (choice != 3) never ends.
        // Fix: clear the stream and ask again. Reject a number that is not
        // 1, 2, or 3 instead of treating it as a command.
        if (!(cin >> choice)) {
            resetCin();
            cout << "Enter 1, 2, or 3.\n";
            choice = 0;
            continue;
        }
        cout << "You chose " << choice << endl;
        if (choice == 1)
            DisplayInfo();
        else if (choice == 2)
            ChangeCustomerChoice();
        else if (choice != 3)
            cout << "Enter 1, 2, or 3.\n";
    }
    return 0;
}
