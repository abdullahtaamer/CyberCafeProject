#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;



int bill = 1;
int constant;

struct food {
    int code;
    string name;
    int price;
};

struct drinks {
    int code;
    string name;
    int price;
};

struct Reservation {
    string date;
    int billNumber;
    vector<food> F;
    vector<drinks> D;
    char type;
    int time; //Duration
    float total;
};

struct customer {
    long long ID;
    string password;
    string name;
    string phoneNumbers[3];
    vector<Reservation> reservations;
    int size = sizeof(reservations) / sizeof(reservations[0]); //Total number of reservations of a specific customer
};vector <customer> Custs;
customer un, pw, id, pn;


void login()
{
    customer check;
    check.ID = -1;
    bool lamba = true;
    while (lamba) {
        cout << "please enter the following data:" << endl;
        cout << "username:";
        cin >> check.name;
        cout << endl << "ID:";
        cin >> check.ID;
        if (cin.fail()) {
            cin.clear();
            cin.ignore( 1000,'\n');
        }
       
        cout << endl << "password:";
        cin >> check.password;
        if (check.ID==-1|| check.ID > Custs.size())
            cout << "invalid id"<<endl;
        else {
            if (check.name == Custs[check.ID - 1].name && check.password == Custs[check.ID - 1].password) {
                cout << "you have logged in successfully!";
                lamba = false;
            }
            else cout << "Wrong Credentials!";
        }
    }
    
}
void registr()
{
    
    customer newCustomer;
    cout << "enter username: ";
    cin >> newCustomer.name;
    cout << endl << "enter password: ";
    cin >> newCustomer.password;
    //cout << endl << "enter phone number: ";
    // Use index 0 instead of 3
    //cin >> newCustomer.phoneNumbers[0];

    // Assign ID as current size (assuming no deletions)
    newCustomer.ID = Custs.size() + 1;
    Custs.push_back(newCustomer);

    cout << "your id is: " << newCustomer.ID << endl;

}

/*void forgot()
{
    int n;
    cout << "forgot password or username?" << endl << "1.username" << endl << "2.password" << endl;
    cin >> n;
    if (n ==1)
    {
        cout << "new username:";
        cin >> un.name;
    }
    else if (n == 2)
    {
        cout << "new password:";
        cin >> pw.password;
    }
    else
        cout << "error";

}*/





int main()
{
    int pick;
    long long index = 0;
    tany:
    cout << "WELCOME" << endl << "1:login" << endl << "2:register" << endl << "3:forgot username or password" << endl << "4:exit" << endl;
    cin >> pick;

    if (pick == 1)
    {
         login();

    }
    else if (pick == 2)
    {
       registr();
       goto tany;

    }
    /*else if (pick == 3)
    {
         forgot();
    }*/
    else
        cout << "thank you for visiting!";


    return 0;

}