#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <bits/stdc++.h>
using namespace std;
int bill = 1;
int constant;
int custCount = 0;
long long ID = 100;

struct food
{
    int code;
    string name;
    int price;
};

struct drinks
{
    int code;
    string name;
    int price;
};

struct Reservation
{
    string date; //
    int billNumber;
    vector<food> F;
    vector<drinks> D;
    char type; //
    int time;  // Duration
    float total;
};

struct customer
{
    long long ID;
    string password;
    string name;
    string phoneNumbers[3];
    Reservation reservations[10];
    int size = sizeof(reservations) / sizeof(reservations[0]); // Total number of reservations of a specific customer
} Custs[40];

void Reservations();
void editReservation();
void login();
void registr();

int main()
{
    registr();
}

void Reservations()
{
    while (true)
    {
        char snacks;
        cout << "Welcome at our reservation page :)\n";
        cout << "\nPlease press M for Multiplayer or S for Single";
        cin >> Custs[constant].reservations[Custs[constant].size].type;
        cout << "How much time will you stay (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )";
        cin >> Custs[constant].reservations[Custs[constant].size].time;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input";
            continue;
        }
        cout << "Press Y if you need any snacks (If not press any button)";
        cin >> snacks;
        cin.ignore();
        if (snacks == 'Y' || snacks == 'y')
        {
            // Lma hana te3mel function el Cafe Menu hne3m3lo show hena
        }
        cout << "Enter date of reservation (DD/MM/YYYY) Ex.: 02/03/2025";
        getline(cin, Custs[constant].reservations[Custs[constant].size].date);
        if (Custs[constant].reservations[Custs[constant].size].date[2] != '/' ||
            Custs[constant].reservations[Custs[constant].size].date[5] != '/')
        {
            cout << "\ninvalid input";
            continue;
        }
    }
}

void editReservation()
{
    do
    {
        cout << "press H to edit time || T to edit type || D to edit date \n";
        char choice;
        cin >> choice;
        if (choice == 'H' || choice == 'h') // edit time // hours
        {
            cout << "How much time will you stay (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )";
            cin >> Custs[constant].reservations[Custs[constant].size].time;
        }
        else if (choice == 'T' || choice == 't')  //edit time
        {
            while (true)
            {
                cout << "\nPlease press M for Multiplayer or S for Single";
                cin >> Custs[constant].reservations[Custs[constant].size].type;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\nInvalid input";
                    continue;
                }
                else
                    break;
            }
        }
        else if (choice == 'd' || choice == 'D')  //edit date
        {
            while (true)
            {
                cout << "Enter new date of reservation (DD/MM/YYYY) Ex.: 02/03/2025";
                getline(cin, Custs[constant].reservations[Custs[constant].size].date);
                if (Custs[constant].reservations[Custs[constant].size].date[2] != '/' ||
                    Custs[constant].reservations[Custs[constant].size].date[5] != '/')
                {
                    cout << "\ninvalid input";
                    continue;
                }
                else
                    break;
            }
        }

        // leave this part right where it issss 
        cout << endl << "Do you want to edit your more info ?      press Y for yes || N for no\n";  //repetition
        char ans;
    }while (ans == 'y' || ans == 'Y');
}

void login()
{
    customer check;
    check.ID = -1;
    bool lamba = true;
    while (lamba)
    {
        cout << "please enter the following data:" << endl;
        cout << "username:";
        cin >> check.name;
        cout << endl
             << "ID:";
        cin >> check.ID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << endl
             << "password:";
        cin >> check.password;
        if (check.ID == -1 || check.ID > Custs.size())
            cout << "invalid id" << endl;
        else
        {
            if (check.name == Custs[check.ID - 1].name && check.password == Custs[check.ID - 1].password)
            {
                cout << "you have logged in successfully!";
                lamba = false;
            }
            else
                cout << "Wrong Credentials!";
        }
    }
}
void registr()
{
    int nums;
    string reenter_Pass;
    cout << "Please enter your information:" << endl;
    cout << "Name:";
    getline(cin, Custs[custCount].name);
    cout << "How many phone numbers do you have?";
    cin >> nums;
    for (int i = 0; i < nums; i++)
    {
        cout << "Phone number:";
        getline(cin, Custs[custCount].phoneNumbers[i]);
    }

    while (true)
    {
        cout << "Please enter your password:";
        getline(cin, Custs[custCount].password);
        cout << "Please re-enter your password:";
        getline(cin, reenter_Pass);
        if (Custs[custCount].password != reenter_Pass)
        {
            cout << endl
                 << "///Passwords don't match please double check it///" << endl
                 << endl;
        }
        else
        {
            break;
        }
    }
    cout << endl
         << "Account created successfully!" << endl
         << endl;
    Custs[custCount].ID = ID;
    cout << "Your ID is " << ID++ << endl
         << endl;
    custCount++;
}