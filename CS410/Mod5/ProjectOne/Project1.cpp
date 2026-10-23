#include <iostream>
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
char password[] = "123";
int choice = 0;
int changechoice = 0;
int newservice = 0;
int answer = 0;

int CheckUserPermissionAccess() {
    string entered;
    cout << "Enter your username: \n";
    cin >> username;
    cout << "Enter your password: \n";
    cin >> entered;
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
    cin >> changechoice;
    cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)\n";
    cin >> newservice;
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
}

int main() {
    cout << "Created by Michael Puckett" << endl;

    cout << "Hello! Welcome to our Investment Company\n";
    answer = CheckUserPermissionAccess();
    while (answer != 1) {
        cout << "Invalid Password. Please try again\n";
        answer = CheckUserPermissionAccess();
    }

    while (choice != 3) {
        cout << "What would you like to do?\n";
        cout << "DISPLAY the client list (enter 1)\n";
        cout << "CHANGE a client's choice (enter 2)\n";
        cout << "Exit the program.. (enter 3)\n";
        cin >> choice;
        cout << "You chose " << choice << endl;
        if (choice == 1)
            DisplayInfo();
        else if (choice == 2)
            ChangeCustomerChoice();
    }
    return 0;
}
