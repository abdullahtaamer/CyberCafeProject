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
int Nfood = 13, Ndrinks = 14;

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

food f[14] = { {"Cheese", 123, 30}, {"Smoked Turky", 222, 40}, {"Chicken", 144, 60}, {"Croissant", 555, 40}, {"Puff pastry", 333, 30}, {"Danish Pastry", 125, 60}, {"Cinnamon Roll", 111, 80}, {"Biscuits or Cookies", 226, 30}, {"Chips or Snacks", 771, 30}, {"Instant Noodless", 126, 40}, {"Mini Pizza", 199, 50}, {"Pan Cakes", 772, 40}, {"Light Burger", 334, 70} };
drinks d[15] = { {"Pepsi", 661, 20}, {"Cocacola", 557, 20}, {"Sprite", 993, 20}, {"Black Tea", 441, 20}, {"Green Tea", 777, 25}, {"Mint Tea", 116, 30}, {"Lemon Tea", 447, 30}, {"Espresso", 221, 40}, {"Amreicano", 551, 50}, {"Cappiccino", 141, 650}, {"Latte", 503, 50}, {"Orange Juice", 460, 30}, {"Mango Juice", 668, 40}, {"Strawberry Juice", 334, 40}, {"Bottelet Water", 445, 15} };

vector<customer> Custs;  //tf is this bro ~sarah
float cafeMenu(int, int);
void Reservations();
void editReservation();
void login();
void registr();

int main()
{
    // cafeMenu(Nfood, Ndrinks); //m7dsh yfok l comment dahh aw ymsa7o
    registr();
}

float cafeMenu(int Nf, int Nd)
{
    // display the title first
    cout << "\t\t\t\t\t\t The Cafe Menu\n"
        << "\t\t\t\t\t\t" << endl;

    int type, code, quantity;
    float Totalcost = 0;
    char ans;
    // Step 1 on displaying the food menu
    food f[14] = { {"Cheese", 123, 30}, {"Smoked Turky", 222, 40}, {"Chicken", 144, 60}, {"Croissant", 555, 40}, {"Puff pastry", 333, 30}, {"Danish Pastry", 125, 60}, {"Cinnamon Roll", 111, 80}, {"Biscuits or Cookies", 226, 30}, {"Chips or Snacks", 771, 30}, {"Instant Noodless", 126, 40}, {"Mini Pizza", 199, 50}, {"Pan Cakes", 772, 40}, {"Light Burger", 312, 70} };
    drinks d[15] = { {"Pepsi", 661, 20}, {"Cocacola", 557, 20}, {"Sprite", 993, 20}, {"Black Tea", 441, 20}, {"Green Tea", 777, 25}, {"Mint Tea", 116, 30}, {"Lemon Tea", 447, 30}, {"Espresso", 221, 40}, {"Amreicano", 551, 50}, {"Cappiccino", 141, 650}, {"Latte", 503, 50}, {"Orange Juice", 460, 30}, {"Mango Juice", 668, 40}, {"Strawberry Juice", 334, 40}, {"Bottelet Water", 445, 15} };
    while (true)
    {
        cout << " Food menu" << "\n"
            << " *********" << endl;
        cout << "For light sandwiches press 1" << endl;
        cout << "For Pastry press 2" << endl;
        cout << "For other options press 3" << endl;
        cin >> type;
        cin.ignore();
        if (type == 1)
        {
            for (int i = 0; i < light; i++)
            {
                cout << endl
                    << f[i].name << "\nCode: " << f[i].code << "\nPrice: " << f[i].price << endl;
            }
        }
        else if (type == 2)
        {
            for (int i = light; i < pastry; i++)
            {
                cout << endl
                    << f[i].name << "\nCode: " << f[i].code << "\nPrice: " << f[i].price << endl;
            }
        }
        else
        {
            for (int i = 7; i < Nf; i++)
            {
                cout << endl
                    << f[i].name << "\nCode: " << f[i].code << "\nPrice: " << f[i].price << endl;
            }
        }

        cout << "\nWould you like to show another food category ?" << endl;
        cout << " If yes enter y\n"
            << " If no enter n\n";
        cin >> ans;
        if (ans == 'n' || ans == 'N')
        {
            break;
        }
    }
    while (true)
    {
        cout << "\nDrinks menu" << "\n " << "" << endl;
        cout << "For Soft Drinks press 1" << endl;
        cout << "For Tea press 2" << endl;
        cout << "For Coffee press 3" << endl;
        cout << "For Fresh Juices press 4" << endl;
        cout << "For Botteled Water press 5" << endl;
        cin >> type;
        cin.ignore();

        if (type == 1)
        {
            for (int i = 0; i < light; i++)
            {
                cout << endl
                    << d[i].name << "\nCode: " << d[i].code << "\nPrice: " << d[i].price << endl;
            }
        }
        else if (type == 2)
        {
            for (int i = 3; i < pastry; i++)
            {
                cout << endl
                    << d[i].name << "\nCode: " << d[i].code << "\nPrice: " << d[i].price << endl;
            }
        }
        else if (type == 3)
        {
            for (int i = pastry; i < 11; i++)
            {
                cout << endl
                    << d[i].name << "\nCode: " << d[i].code << "\nPrice: " << d[i].price << endl;
            }
        }
        else if (type == 4)
        {
            for (int i = 11; i < Nd; i++)
            {
                cout << endl
                    << d[i].name << "\nCode: " << d[i].code << "\nPrice: " << d[i].price << endl;
            }
        }
        else
        {
            for (int i = 14; i <= Nd; i++)
            {
                cout << endl
                    << d[i].name << "\nCode: " << d[i].code << "\nPrice: " << d[i].price << endl;
            }
        }
        cout << "\nWould you like to show another drink category ?" << endl;
        cout << " If yes enter y\n"
            << " If no enter n\n";
        cin >> ans;
        if (ans == 'n' || ans == 'N')
        {
            break;
        }
    }

    do
    {
        cout << "Please Enter the code of the product you want: ";
        cin >> code;
        cin.ignore();
        cout << endl;
        cout << "Please Enter the quantity of this product you want: ";
        cin >> quantity;
        cin.ignore();
        cout << endl;
        for (int i = 0; i <= Nf + Nd; i++)
        {
            if (code == f[i].code)
            {
                Totalcost += (f[i].price * quantity);
                break;
            }
            else if (code == d[i].code)
            {
                Totalcost += (d[i].price * quantity);
                break;
            }
            else if (i == Nf + Nd && code != f[i].code && code != d[i].code)
            {
                cout << "Invalid code" << endl;
            }
        }
        cout << "Would you like to add another product to your cart?" << endl;
        cout << " If yes enter y\n"
            << " If no enter n\n";
        cin >> ans;
        cin.ignore();

    } while (ans == 'y' || ans == 'Y');
    cout << "Your Total cost is: " << Totalcost << endl;
    cout << "Enjoy your meal!^_^" << endl;
    return Totalcost;
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
    } while (ans == 'y' || ans == 'Y');
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
