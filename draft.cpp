#include <iostream>
#include <iomanip>
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
} Custs[50];


void viewinfo(char);

int main() {
    //Testing some database

    Custs[0] = { 1, "Abdo", "Abdullah Tamer Mohamed", {"01095407507", "01501589484", "01009895000"} };
    char ans;
    cout << " Hello there! do you want to view your own information\n ?" << endl; // Asking the cust to view his info
    cout << "If YES please enter y\n" << " else if NO please enter n\n";
    cin >> ans;
    cin.ignore();
    if (ans == 'y' || ans == 'Y') {

        viewinfo(ans);
    }
    else
        cout << " Your information will not be viewed";

}

void viewinfo(char answer) { //Displaying all the information
    cout << "\t";
    cout << setw(15) << left << "Name";
    cout << setw(12) << left << " ";
    cout << setw(15) << left << "ID";
    cout << setw(1) << left << " ";
    cout << setw(15) << left << "Password";
    cout << setw(12) << left << " ";
    cout << setw(15) << left << "Phone number";
    cout << endl;
    cout << setw(15) << left << Custs[0].name;
    cout << setw(14) << left << " ";
    cout << setw(15) << left << Custs[0].ID;
    cout << setw(1) << left << " ";
    cout << setw(15) << left << Custs[0].password;
    cout << setw(1) << left << " ";
    cout << setw(15) << right << Custs[0].phoneNumbers[0] << " " << Custs[0].phoneNumbers[1] << " " << Custs[0].phoneNumbers[2];


    system("pause");






}