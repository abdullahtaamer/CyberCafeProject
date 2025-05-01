#include <iostream>
#include <string>
#include <conio.h>


#define Availablereservations 100
#define users 100
#define buses 100
using namespace std;
struct bus
{
    int busid = 0;
    string routefrom;
    string routeto;
    string departuretime;
    string arrivaltime;
    int availabeleseats = 0; // number of available seats only//
    float price = 0;
    string date;
}B[buses];struct reservation
{
    int reservationsid;
    int userid;
    int busid;
    int seatnumber;
    string date;
    bus BB;
    string status;
} Reserve[Availablereservations];

struct user
{
    int res = 0; // Counter for every reservation the user had made
    int Userid = 0;
    string name;
    string mail;
    long long int phone;
    bool role; // True = admin false = passenger
    string password;
    reservation R[Availablereservations];
} U[users];



struct request
{
    int reservationid;
    bool check = false;
    reservation req; // The requested bust
} REQUEST[Availablereservations];

int id = 0;
int buscount = 0;
int reservations = 0; // Total number of reservations
int requests = 0;     // Total number of requests
int usercount = 0;    // Total number of users
int constant;         // The id of the logged in user
void addbuses()//admin
{
    if (buscount >= buses)
    {
        cout << "cannot add more buses, maximum limit reached.\n";
        return;
    }
    cout << "enter route from\n";
    cin >> B[buscount].routefrom;
    cout << "enter route to\n";
    cin >> B[buscount].routeto;
    cout << "enter the departue time \n";
    cin >> B[buscount].departuretime;
    cout << "enter the arrival time\n";
    cin >> B[buscount].arrivaltime;
    cout << "enter the number of  availabe seats\n";
    cin >> B[buscount].availabeleseats;
    cout << "enter the price of ticket\n";
    cin >> B[buscount].price;
    B[buscount].busid = id;
    cout << "\nYour bus id is " << id++;
    buscount++;
}
void editbuses()//admin
{
    int id;
    cout << "please enter the bus id you want to edit\n";
    cin >> id;
    bool found = false;
    for (int i = 0; i < buscount; i++)
    {
        if (id == B[i].busid)
        {
            found = true;
            cout << "edit route from\n";
            cin >> B[i].routefrom;
            cout << "edit route to\n";
            cin >> B[i].routeto;
            cout << "edit the departue time \n";
            cin >> B[i].departuretime;
            cout << "edit the arrival time\n";
            cin >> B[i].arrivaltime;
            cout << "edit number of availabe seats\n";
            cin >> B[i].availabeleseats;
            cout << "edit the price of the ticket\n";
            cin >> B[i].price;
            break;
        }
    }
    if (!found)
        cout << "bus not found\n";
}
void listbuses()//Admin
{
    if (buscount == 0)
    {
        cout << "No Buses Available.\n";
        return;
    }
    for (int i = 0; i < buscount; i++)
    {
        cout << "bus no:" << (i + 1) << endl;
        cout << "ID:" << B[i].busid << endl;
        cout << "from:" << B[i].routefrom << endl;
        cout << "to:" << B[i].routeto << endl;
        cout << "Departure time:" << B[i].departuretime << endl;
        cout << "arrival time:" << B[i].arrivaltime << endl;
        cout << "available seats:" << B[i].availabeleseats << endl;
        cout << "ticket price:" << B[i].price << endl;
    }
}
void deletebuses()//admin
{
    int id;
    cout << "please enter bus id to delete:";
    cin >> id;
    bool found = false;
    for (int i = 0; i < buscount; i++)
    {
        if (id == B[i].busid)
        {
            found = true;
            for (int j = i; j < buscount - 1; j++)
            {
                B[j] = B[j + 1];
            }
            buscount--;
            cout << "bus deleted\n";
            break;
        }
    }
    if (!found)
    {
        cout << "bus not found\n";
    }
}

void Requests() //passenger
{
    int id; // Reservation ID
    cout << "Please enter the reservation id";
    cin >> id;
    for (int i = 0; i < reservations; i++)
    {
        if (id == Reserve[i].reservationsid)
        {
            REQUEST[requests].check = true;
            REQUEST[requests].req = Reserve[id];
        }
    }
}

void registr()
{
    int i;               // Admin or passenger
    string reenter_Pass; // Let the user reenter his password to check it.
Addeger:
    cout << "You are a " << endl
        << "1: Admin  \t 2: Passenger \n";
    cin >> i;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n"
            << endl;
        goto Addeger;
    }
    if (i == 1)
    {
        cout << "Please enter your information: " << endl;

    Username:
        cout << "Username: ";
        cin >> U[usercount].name;
        if (cin.peek() == ' ')
        {
            cout << "Your username can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Username;
        }
    phoning:
        cout << "Please enter your phone number: ";
        while (true) {
            cin >> U[usercount].phone;
            if (cin.peek() == ' ') {
                cout << "Your phone cant include spaces\n";
                cin.clear();
                cin.ignore(1000, '\n');
                goto phoning;
            }
            if (cin.fail()) {
                cout << "Invalid number \n";
                cin.clear();
                cin.ignore(1000, '\n');
                goto phoning;
            }
            break;
        }
    Email:
        cout << "Please enter your email: ";
        while (true) {
            cin >> U[usercount].mail;
            if (cin.peek() == ' ') {
                cout << "Your mail cant contatin spaces ";
                cin.clear();
                cin.ignore(1000, '\n');
                goto Email;
            }
            break;
        }
    PasswordMaking:
        cout << "Please enter your password: ";
        string password1;
        char ch55;
        while (true)
        {
            ch55 = _getch();
            if (ch55 == '\r')
            {
                break;
            }
            if (ch55 == '\b')
            {
                password1.pop_back();
                cout << "\b \b";
            }
            if (ch55 != '\b')
            {
                password1 += ch55;
                cout
                    << "*";
            }
        }
        cout << endl;

        U[usercount].password = password1;

        if (cin.peek() == ' ')
        {
            cout << "Your password can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto PasswordMaking;
        }
        cout << "Please re-enter your password: ";

        string password2;
        char ch66;
        while (true)
        {
            ch66 = _getch();
            if (ch66 == '\r')
            {
                break;
            }
            if (ch66 == '\b')
            {
                password2.pop_back();
                cout << "\b \b";
            }
            if (ch66 != '\b')
            {
                password2 += ch66;
                cout << "*";
            }
        }
        cout << endl;
        reenter_Pass = password2;

        if (U[usercount].password != reenter_Pass || cin.peek() == ' ')
        {
            cout << endl
                << "///Passwords don't match please double check it///" << endl
                << endl;
            goto PasswordMaking;
        }
        cout << endl
            << "Account created successfully!" << endl
            << endl;
        U[usercount].Userid = id;
        cout << "Your ID is " << id++ << endl
            << endl;
        usercount++;
    }
}

void search() { // For passnengers  MUST CREATE ATLEAST 1  BUS
    string WD;
    string MF;
    bool found = false;
    cout << "Where is your bus going to? \n";
    cin >> WD;
    cout << "Moving from?";
    cin >> MF;
    for (int i = 0; i < buscount; i++) {
        if (WD == B[i].routeto || MF == B[i].routefrom) {
            cout << "Your bus ID is :" << B[i].busid;
            cout << "\n Your departure is " << B[i].routefrom;
            cout << "\n Your destination is " << B[i].routeto;
            cout << "\nBus is leaving at:" << B[i].departuretime << "\narriving at:" << B[i].arrivaltime;
            found = true;
        }
        if (!found) {
            cout << "Couldn't find ur bus";
        }
    }



}
int logIn() //Admin or passenger
{
    int ID;
    bool logIn = false;
    int choice;
    cout << "Login to your account" << endl;
Oblak:
    while (logIn == false)
    {
        cout << "You're a\n1.Admin\n2.Passenger\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "ID: ";
        cin >> ID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            goto Oblak;
        }
        cout << "Password: ";
        string password1;
        char ch55;
        while (true)
        {
            ch55 = _getch();
            if (ch55 == '\r')
            {
                break;
            }
            if (ch55 == '\b')
            {
                password1.pop_back();
                cout << "\b \b";
            }
            if (ch55 != '\b')
            {
                password1 += ch55;
                cout
                    << "*";
            }
        }
        cout << endl;
        if (choice == 1)
        {
            for (int i = 0; i < usercount; i++)
            {
                if (ID == U[i].Userid && password1 == U[i].password)
                {
                    cout << endl
                        << "Login successfull !" << endl
                        << endl;
                    logIn = true;
                    constant = i;
                    return constant;
                }
            }
        }
        else if (choice == 2)
        {
            for (int i = 0; i < usercount; i++)
            {
                if (ID == U[i].Userid && password1 == U[i].password)
                {
                    cout << endl
                        << "Login successfull !" << endl
                        << endl;
                    logIn = true;
                    constant = i;
                    return constant;
                }
            }
        }
        else
        {
            cout << endl
                << "Wrong choice,Try again" << endl
                << endl;
            continue;
        }
        cout
            << endl
            << "Wrong ID or Password,Try again" << endl
            << endl;
        goto Oblak;
    }
}
void seat_booking()//User function
{
    int  busID;
    cout << "please enter the bus id\n";
    cin >> busID;
    for (int i = 0; i < buscount; i++)
    {
        if (busID == B[i].busid)
        {
            if (B[i].availabeleseats == 0)
            {
                cout << "You can't reserve in this bus\n";
            }
            else
            {
                B[i].availabeleseats--;
                U[constant].R[U[constant].res].busid = busID;
                U[constant].R[U[constant].res].userid = U[constant].Userid;
                U[constant].R[U[constant].res].seatnumber = B[i].availabeleseats;
                U[constant].R[U[constant].res].date = B[i].date;
                U[constant].R[U[constant].res].status = "Confirmed";
                U[constant].R[U[constant].res].reservationsid = reservations;
                U[constant].R[U[constant].res].BB = B[i];
                B[i].availabeleseats--;
                cout << "Your seat has been booked successfully \n";
            }
        }
    }
}
void cancelreservation() { //admin function MUST CREATE ATLEAST 1 RESERVATION
    int id;
    bool found = false;
    cout << "Enter the reservation id :  ";
    cin >> id;

    for (int i = 0; i < reservations; i++) {
        if (id == Reserve[i].reservationsid) {
            found = true;
            Reserve[i].status = "Cancelled";
            for (int j = i;j < reservations - 1;j++) {
                Reserve[j] = Reserve[j + 1];
            }
            reservations--;
            B[i].availabeleseats++;
            cout << "\nYour reservation has been cancelled";
            break;
        }
    }if (!found)
        cout << "\n Couldnt find your reservation";
}
void answer() {      //admin
    int i;
    cout << "\nRequests are:\n";
    for (int i = 0; i < Availablereservations; i++)
    {
        if (REQUEST[requests].check = true) {
            cout << "From user: " << REQUEST[i].req.userid;
            cout << "\nBus: " << REQUEST[i].req.busid;
            cout << "\nReservation: " << REQUEST[i].req.reservationsid;
            cout << endl << endl;
        Answer:
            cout << "\nAccept?" << "1: Yes \t 2:No";
            cin >> i;
            if (i == 1) {
                cancelreservation();
                cout << "Cancel is done";
            }
            else if (i == 2) {
                cout << "Rejected";
            }
            else {
                cout << "\nWrong answer";
                goto Answer;
            }

        }
        else if (!REQUEST[requests].check && i == Availablereservations - 1) {
            cout << "No requests found";
        }
    }
}

void Tracking() {      //passenger
    cout << "\n Here are your reservations:\n";
    for (int i = 0; i < U[constant].res;i++) {
        cout << "Reservation ID:" << U[constant].R[i].reservationsid;
        cout << "\nSeat number:" << U[constant].R[i].seatnumber;
        cout << "\nBus id: " << U[constant].R[i].BB.busid;
        cout << "\nMoved from: " << U[constant].R[i].BB.routefrom;
        cout << "\nMoved to: " << U[constant].R[i].BB.routeto;
        cout << "\nArrived at: " << U[constant].R[i].BB.arrivaltime;
        cout << "\nLeft at: " << U[constant].R[i].BB.departuretime;
        cout << "\nTicket costed: " << U[constant].R[i].BB.price;
        cout << endl << endl;
    }







}
int main()
{
    int i;
    /*Start:
    while (true) {
        cout << "What do u want to do \n" << "1:Register \t 2:Login \n";
        cin >> i;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        if (i == 1) {
            registr();
            goto Start;
        }
        else if (i == 2) {
            logIn();
        
        }
        else if (i > 2 || i < 0) {
            cout << "Invalid answer";
            goto Start;
        }
        break;
    }*/
    cin >> i;
    int choice;
    Mainadmin:
    {
        if (i == 1)
         {
            cout << "\n            admin bus system          \n";
            cout << "for add bus enter no:1\n";
            cout << "for edit bus enter no:2\n";
            cout << "for delete bus enter no:3\n";
            cout << "for list buses enter no:4\n";
            cout << "for checking requests enter no:5\n";
            cout << "for requests enter no:6\n";
            cout << "for cancelling reservations enter no:7\n";
            cout << "for exit enter no:8\n";
        }
        cout << "please enter your choice\n";
        cin.ignore();
        cin >> choice;
        switch (choice)
        {
        case 1:
            addbuses();
            break;
        case 2:
            editbuses();
            break;
        case 3:
            deletebuses();
            break;
        case 4:
            listbuses();
            break;
        case 5:
            answer();
            break;
        case 6:
            Requests();
            break;
        case 7:
            cancelreservation();
            break;
        case 8:
            return 0;
        default:
            cout << "invalid choice\n please read the choices again\n ";
            break;
        }
    }goto Mainadmin;

}