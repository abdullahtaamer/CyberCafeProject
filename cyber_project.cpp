#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <bits/stdc++.h>
using namespace std;
int bill=1;
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
    string date; //
    int billNumber;
    vector<food> F;
    vector<drinks> D;
    char type; //
    int time; //Duration
    float total;
};

struct customer {
    long long ID;
    string password;
    string name;
    string phoneNumbers[3];
    vector<Reservation> reservations;
    int size = sizeof(reservations)/sizeof(reservations[0]); //Total number of reservations of a specific customer
};vector <customer> Custs;

void Reservations();

int main()
{
    cout <<"testtttt";
    cout <<"bgarabb";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
    cout <<"jnbjkmncvbfjkdvn ";
}

void Reservations()
{
    while (true)
    {
        char snacks;
        cout <<"Welcome at our reservation page :)\n";
        cout<<"\nPlease press M for Multiplayer or S for Single";
        Custs[constant].reservations[Custs[constant].size].type=_getch();
        cout <<"How much time will you stay (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )";
        cin>>Custs[constant].reservations[Custs[constant].size].time;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"\nInvalid input";
            continue;
        }
        cout<<"Press Y if you need any snacks (If not press any button)";
        snacks=_getch();
        if (snacks == 'Y' ||snacks == 'y')
        {
            // Lma hana te3mel function el Cafe Menu hne3m3lo show hena
        }
        cout<<"Enter date of reservation (DD/MM/YYYY) Ex.: 02/03/2025";
        getline (cin,Custs[constant].reservations[Custs[constant].size].date);
        if (Custs[constant].reservations[Custs[constant].size].date[2]!='/' || 
            Custs[constant].reservations[Custs[constant].size].date[5]!='/')
        {
            cout <<"\ninvalid input";
            continue;
        }
        
        
        
    }
        
        
        
    
}