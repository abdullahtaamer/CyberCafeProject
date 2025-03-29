#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <bits/stdc++.h>
#define light 3
#define pastry 7
#define foodCount 40  // max number of food in one reservation
#define drinkCount 40 // max number of drink in one reservation
#define resCount 40   // max number of reservations for one customer
using namespace std;
int bill = 0;
int constant;
int custCount = 0;
long long ID = 0;
int Nfood = 13, Ndrinks = 14;

struct food
{
    string name;
    int code;
    int price;
    int quantity;
};

struct drinks
{
    string name;
    int code;
    int price;
    int quantity;
};

struct Reservation
{
    string date; //
    int billNumber;
    int foodOrderCount;   // How many f the user had ordered
    int drinksOrderCount; // How many drinks the user had ordered
    food F[foodCount];
    drinks D[foodCount];
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
    Reservation reservations[resCount];                        // Array of reservations for each customer
    int size = sizeof(reservations) / sizeof(reservations[0]); // Total number of reservations of a specific customer
} Custs[40];

food f[14] = {{"Cheese", 123, 30}, {"Smoked Turky", 222, 40}, {"Chicken", 144, 60}, {"Croissant", 555, 40}, {"Puff pastry", 333, 30}, {"Danish Pastry", 125, 60}, {"Cinnamon Roll", 111, 80}, {"Biscuits or Cookies", 226, 30}, {"Chips or Snacks", 771, 30}, {"Instant Noodless", 126, 40}, {"Mini Pizza", 199, 50}, {"Pan Cakes", 772, 40}, {"Light Burger", 334, 70}};
drinks d[15] = {{"Pepsi", 661, 20}, {"Cocacola", 557, 20}, {"Sprite", 993, 20}, {"Black Tea", 441, 20}, {"Green Tea", 777, 25}, {"Mint Tea", 116, 30}, {"Lemon Tea", 447, 30}, {"Espresso", 221, 40}, {"Amreicano", 551, 50}, {"Cappiccino", 141, 650}, {"Latte", 503, 50}, {"Orange Juice", 460, 30}, {"Mango Juice", 668, 40}, {"Strawberry Juice", 334, 40}, {"Bottelet Water", 445, 15}};

// vector<customer> Custs;  //tf is this bro ~sarah
float cafeMenu(int, int);
void billing_system_customer(Reservation res, float tax);
void Reservations();
void editReservation();
int login();
void registr();

int main()
{
    // Jimmy's test data////

    // Reservation res;

    // // Test data
    // res.time = 2; // Hours spent playing
    // res.total = 200; // Price of PlayStation rent (should be based on the time spent playing)

    // res.foodOrderCount = 6;
    // // Food test data { code, name, price, quantity }
    // res.F[0] = { 0, "Kofta", 20, 2 };
    // res.F[1] = { 1, "Shawarma", 50, 1 };
    // res.F[2] = { 2, "Pizza", 80, 3 };
    // res.F[3] = { 3, "Ta3meya", 30, 4 };
    // res.F[4] = { 4, "Burger", 45, 1 };
    // res.F[5] = { 5, "Fried Chicken", 60, 2 };

    // res.drinksOrderCount = 5;
    // // Drinks test data { code, name, price, quantity }
    // res.D[0] = { 0, "Sobya", 10, 1 };
    // res.D[1] = { 1, "Coca-Cola", 25, 2 };
    // res.D[2] = { 2, "Fanta", 20, 3 };
    // res.D[3] = { 3, "Sprite", 22, 3 };
    // res.D[4] = { 4, "Water", 10, 5 };

    float tax = 14; // Tax of 14%

    // Function call
    // billing_system_customer(res, tax);

    // Hana///
    // cafeMenu(Nfood, Ndrinks); //m7dsh yfok el comment dahh aw ymsa7o ~Sarah .... Mtz3a'ish ~Abdullah
    registr();
    login();
    Reservations();
    billing_system_customer(Custs[constant].reservations[Custs[constant].size], tax); // Call the billing system function with the reservation and tax
    return 0;
}

float cafeMenu(int Nf, int Nd)
{
    // display the title first
    cout << "\t\t\t\t\t\t The Cafe Menu\n"
    << "\t\t\t\t\t\t" << endl;

    int type, code;
    float Totalcost = 0;
    char ans;
    // Step 1 on displaying the food menu
    // food f[14] = {{"Cheese", 123, 30}, {"Smoked Turky", 222, 40}, {"Chicken", 144, 60}, {"Croissant", 555, 40}, {"Puff pastry", 333, 30}, {"Danish Pastry", 125, 60}, {"Cinnamon Roll", 111, 80}, {"Biscuits or Cookies", 226, 30}, {"Chips or Snacks", 771, 30}, {"Instant Noodless", 126, 40}, {"Mini Pizza", 199, 50}, {"Pan Cakes", 772, 40}, {"Light Burger", 312, 70}};
    // drinks d[15] = {{"Pepsi", 661, 20}, {"Cocacola", 557, 20}, {"Sprite", 993, 20}, {"Black Tea", 441, 20}, {"Green Tea", 777, 25}, {"Mint Tea", 116, 30}, {"Lemon Tea", 447, 30}, {"Espresso", 221, 40}, {"Amreicano", 551, 50}, {"Cappiccino", 141, 650}, {"Latte", 503, 50}, {"Orange Juice", 460, 30}, {"Mango Juice", 668, 40}, {"Strawberry Juice", 334, 40}, {"Bottelet Water", 445, 15}};
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
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input";
            continue;
        }
        int i = 0;
        for (; i < foodCount + drinkCount; i++)
        {
            if (code == f[i].code)
            {
                Custs[constant].reservations[Custs[constant].size].F[i].code = f[i].code;
                Custs[constant].reservations[Custs[constant].size].F[i].name = f[i].name;
                Custs[constant].reservations[Custs[constant].size].F[i].price = f[i].price;

                cin.ignore();
                cout << endl;
                cout << "Please Enter the quantity of this product you want: ";
                cin >> Custs[constant].reservations[Custs[constant].size].F[i].quantity;
                break;
            }
            else if (code == d[i].code)
            {
                Custs[constant].reservations[Custs[constant].size].D[i].code = d[i].code;
                Custs[constant].reservations[Custs[constant].size].D[i].name = d[i].name;
                Custs[constant].reservations[Custs[constant].size].D[i].price = d[i].price;

                cin.ignore();
                cout << endl;
                cout << "Please Enter the quantity of this product you want: ";
                cin >> Custs[constant].reservations[Custs[constant].size].D[i].quantity;
                break;
            }
        }

        cin.ignore();
        cout << endl;
        cout << "Please Enter the quantity of this product you want: ";
        cin >> Custs[constant].reservations[Custs[constant].size].F[i].quantity;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input";
            continue;
        }
        cout << "Would you like to add another product to your cart?" << endl;
        cout << " If yes enter y\n"
            << " If no enter n\n";
        cin >> ans;
        cin.ignore();

    } while (ans == 'y' || ans == 'Y');
    // cout << "Your Total cost is: " << Totalcost << endl;
    cout << "Enjoy your meal!^_^" << endl;
    return Totalcost;
}

// --My function-- Billing System function for customers, takes a reservation from the user & the tax as parameters
void billing_system_customer(Reservation res, float tax) {
    cout << "Hi there! Hope you had a great time with us. Here is your bill:" << "\n\n";

    cout << setw(37) << left << "PlayStation for " + to_string(res.time) + " hours" // Time spent playing
        << setw(10) << left << to_string(int(round(res.total))) + " EGP" << "\n\n"; // PlayStation rent price

    cout << "Food & Drinks:" << "\n\n";
    cout << setw(7) << left << "QTY" // Quantity column header of the food/drink
        << setw(30) << left << "Description" // Name column header of the food/drink
        << setw(10) << left << "Price" << "\n"; // Price column header of the food/drink

    int totalFoodPrice = 0;
    // Displaying and calculating the total price of the current food using a for loop
    for (int i = 0; i < res.foodOrderCount; i++) { // Loop n times the number of the f ordered
        cout << setw(7) << left << res.F[i].quantity // Display quantity
            << setw(30) << left << res.F[i].name // Display name
            << setw(10) << left << to_string(res.F[i].price * res.F[i].quantity) + " EGP" << "\n"; // Display and calculate price (food price * quantity)
        totalFoodPrice = totalFoodPrice + (res.F[i].price * res.F[i].quantity); // Add the current food price to the total price of f
    }

    int totalDrinksPrice = 0;
    // Displaying and calculating the total price of the current drink using a for loop
    for (int j = 0; j < res.drinksOrderCount; j++) { // Loop n times the number of the drinks ordered
        cout << setw(7) << left << res.D[j].quantity // Display quantity
            << setw(30) << left << res.D[j].name // Display name
            << setw(10) << left << to_string(res.D[j].price * res.D[j].quantity) + " EGP" << "\n"; // Display and calculate price (drink price * quantity)
        totalDrinksPrice = totalDrinksPrice + (res.D[j].price * res.D[j].quantity); // Add the current drink price to the total price of drinks
    }

    float subtotal = res.total + totalFoodPrice + totalDrinksPrice; // Calculate subtotal
    float total_price = subtotal + ((tax / 100) * subtotal); // Calculate total (subtotal + tax)

    cout << "\n"
        << setw(37) << left << "Subtotal"
        << setw(10) << left << to_string(int(round(subtotal))) + " EGP" << "\n"; // Display subtotal (total price without the tax)
    cout << setw(37) << left << "Total (including " + to_string(int(round(tax))) + "% tax)"
        << setw(10) << left << to_string(int(round(total_price))) + " EGP"; // Display total (total price WITH the tax)
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
            cafeMenu(Nfood, Ndrinks);
        }
        cout << "Enter date of reservation (DD/MM/YYYY) Ex.: 02/03/2025";
        getline(cin, Custs[constant].reservations[Custs[constant].size].date);
        if (Custs[constant].reservations[Custs[constant].size].date[2] != '/' ||
            Custs[constant].reservations[Custs[constant].size].date[5] != '/')
        {
            cout << "\ninvalid input";
            continue;
        }
        Custs[constant].reservations[Custs[constant].size].billNumber = bill++;
        cout << "Your reservation has been made successfully!" << endl;
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
        else if (choice == 'T' || choice == 't') // edit time
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
        else if (choice == 'd' || choice == 'D') // edit date
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
        cout << endl
             << "Do you want to edit your more info ?      press Y for yes || N for no\n"; // repetition
        char ans;
    } while (ans == 'y' || ans == 'Y');
}

int login()
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
                constant = check.ID - 1;
            }
            else
                cout << "Wrong Credentials!";
        }
    }
    return constant;
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
