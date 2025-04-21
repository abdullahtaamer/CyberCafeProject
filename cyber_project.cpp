#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <bits/stdc++.h>
#include <ctime>
#define light 3
#define pastry 7
#define foodCount 40     // Max number of food in one reservation
#define drinkCount 40    // Max number of drink in one reservation
#define resCount 40      // Max number of reservations for one customer
#define customers_num 40 // Number of customers we can have
#define workers_num 40     // Number of workers we can have
#define game_count 6     // sarahss
using namespace std;
int bill = 0;
int constant;
int custCount = 0;        // Lw la'etha b ay rakam gher 0 khaliha 0
int workCount = 0;        // Lw la'etha b ay rakam gher 0 khaliha 0
int reserved_devices = 0; // Number of reserved devices in a single period
long long ID = 1;
const int Nfood = 13, Ndrinks = 15, available_Devices = 10;
float tax = 14;        // Tax of 14%
int Custsize = 1;      // Ziad hatetha
int worksize = 1;      // Ziad hatetha
bool loggedIn = false; // True if the user logged in successfully
int i;                 // If = 1 The logged in person is a customer , if = 2 The logged in person is a worker
int Most_playedCount = 0;

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
    drinks D[drinkCount];
    char type; //
    int time;  // Duration
    float total;
    int game;     // //fifa , pes, mortal, gta, cod, fall guys
    string clock; // from char : 5 to char : 10
    int StartTime;
    int EndTime;
};

struct security
{
    int no;
    string ans;
};

// Struct for employee earnings
struct employee
{
    bool shift; // True if an employee is logged in
    float weeklyEarnings;
    float monthlyEarnings;
    float yearlyEarnings;
};

struct customer
{
    long long ID;
    string password;
    string name;
    int nums; // Number of phone numbers
    string phoneNumbers[3];
    Reservation reservations[resCount]; // Array of reservations for each customer
    security question;
    int res = 0; // Total number of reservations of a specific customer

    employee emp;
} Custs[customers_num], works[workers_num];

struct game
{
    int game_tag;
    int Mostfrequency;
    string game_name;
};
game Final_most[game_count] = {{1, 0, "FIFA"}, {2, 0, "PES"}, {3, 0, "MORTAL KOMBAT"}, {4, 0, "GTA V"}, {5, 0, "COD"}, {6, 0, "FALL GUYS"}};

food f[Nfood] = {{"Cheese", 123, 30, 0}, {"Smoked Turkey", 222, 40, 0}, {"Chicken", 144, 60, 0}, {"Croissant", 555, 40, 0}, {"Puff Pastry", 333, 30, 0}, {"Danish Pastry", 125, 60, 0}, {"Cinnamon Roll", 111, 80, 0}, {"Biscuits or Cookies", 226, 30, 0}, {"Chips or Snacks", 771, 30, 0}, {"Instant Noodles", 126, 40, 0}, {"Mini Pizza", 199, 50, 0}, {"Pan Cakes", 772, 40, 0}, {"Light Burger", 312, 70, 0}};
drinks d[Ndrinks] = {{"Pepsi", 661, 20, 0}, {"Cocacola", 557, 20, 0}, {"Sprite", 993, 20, 0}, {"Black Tea", 441, 20, 0}, {"Green Tea", 777, 25, 0}, {"Mint Tea", 116, 30, 0}, {"Lemon Tea", 447, 30, 0}, {"Espresso", 221, 40, 0}, {"Amreicano", 551, 50, 0}, {"Cappiccino", 141, 650, 0}, {"Latte", 503, 50, 0}, {"Orange Juice", 460, 30, 0}, {"Mango Juice", 668, 40, 0}, {"Strawberry Juice", 334, 40, 0}, {"Bottelet Water", 445, 15, 0}};
// vector<customer> Custs;  //tf is this bro ~sarah
float cafeMenu(int, int);
void billingSystemCustomer(Reservation res, float tax);
void Reservations();
void editReservation();
int login();
void registr();
void forgot();
void getTopEmployee(customer works[], int shiftIndex);
void viewInformation();
void viewInformationEmployee();
void viewReservation();
void mostPlayed();

int main()
{
    // cafeMenu(Nfood, Ndrinks); //m7dsh yfok el comment dahh aw ymsa7o ~Sarah .... Mtz3a'ish ~Abdullah

    int question; //  What does the user want to do
    cout << "Welcome at our paradise :)\n\n";
Menu:
    cout << "\n\nTo log in Press 1\nTo create a new account Press 2\n";
    cin >> question;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto Menu;
    }
    if (question == 1)
        login();
    else
    {
        registr();
        goto Menu;
    }
LogedIn:
    if (loggedIn && i != 2)
    {
        cout << "\n\nTo make a new reservation Press 1\nTo edit your reservation Press 2\nTo view your information Press 3\nTo log out Press 4\n";
        cin >> question;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            goto LogedIn;
        }
        if (question == 1)
        {
            Reservations();
            goto LogedIn;
        }
        else if (question == 2)
        {
            editReservation();
            goto LogedIn;
        }
        else if (question == 3)
        {
            viewInformation();
            goto LogedIn;
        }
        else if (question == 4)
            goto Menu;
    }
    else
    {
        cout << "\n\nTo make a new reservation Press 1\nTo edit your reservation Press 2\nTo view the employee of the week/month/year press 3\nTo view your information Press 4\nTo view a customer's information Press 5\nTo log out Press 6\n";
        cin >> question;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            goto LogedIn;
        }
        if (question == 1)
        {
            Reservations();
            goto LogedIn;
        }
        else if (question == 2)
        {
            editReservation();
            goto LogedIn;
        }
        else if (question == 3)
        {
            getTopEmployee(works, constant);
            goto LogedIn;
        }
        else if (question == 4)
        {
            viewInformation();
            goto LogedIn;
        }
        else if (question == 5)
        {
            viewInformationEmployee();
            goto LogedIn;
        }
        else if (question == 6)
            goto Menu;
    }

    // getTopEmployee(works, shiftIndex);  // Call getTopEmployee with employees array (works[]) & the array index of the currently logged in employee
    return 0;
}

float cafeMenu(int Nf, int Nd)
{
    // display the title first
    cout << "\n\n\t\t\t\t\t\t The Cafe Menu\n"
         << "\t\t\t\t\t\t" << endl;

    int type, code;
    float Totalcost = 0;
    char ans;
    // Step 1 on displaying the food menu
    while (true)
    {
        cout << " Food menu" << "\n"
             << " *********" << endl;
        cout << "For light sandwiches press 1" << endl;
        cout << "For Pastry press 2" << endl;
        cout << "For other options press 3" << endl;
        cin >> type;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            continue;
        }
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
        while (true)
        {

            cout << "\nWould you like to show another food category ?" << endl;
            cout << " If yes enter y or anything except n\n"
                 << " If no enter n\n";
            cin.ignore();
            cin.get(ans);
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n\n";
                continue;
            }
            else
                break;
        }
        if (ans == 'n' || ans == 'N')
        {
            break;
        }
    }
    cout << endl
         << "\nDrinks menu" << "\n " << "" << endl;
    while (true)
    {
        cout << "For Soft Drinks press 1" << endl;
        cout << "For Tea press 2" << endl;
        cout << "For Coffee press 3" << endl;
        cout << "For Fresh Juices press 4" << endl;
        cout << "For Botteled Water press 5" << endl;
        cin >> type;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            continue;
        }

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
        while (true)
        {
            cout << "\nWould you like to show another drink category ?" << endl;
            cout << " If yes press y or any button\n"
                 << " If no enter press n\n";
            cin >> ans;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n\n";
                continue;
            }
            else
                break;
        }
        if (ans == 'n' || ans == 'N')
        {
            break;
        }
    }
    int j = 0;
    int k = 0;
    do
    {
        while (true)
        {
            cout << endl
                 << "Please Enter the code of the product you want: ";
            cin >> code;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n\n";
                continue;
            }
            else
                break;
        }

        int i = 0;
        for (; i < Nfood + Ndrinks; i++) // Matensash tzabatha ya abdo
        {
            if (code == f[i].code)
            {
                Custs[constant].reservations[Custs[constant].res].F[j].code = f[i].code;
                Custs[constant].reservations[Custs[constant].res].F[j].name = f[i].name;
                Custs[constant].reservations[Custs[constant].res].F[j].price = f[i].price;
                cout << "You ordered: " << f[i].name << endl;
                cout << "Code: " << f[i].code << endl;
                cout << "Price: " << f[i].price << "EGP" << endl;

                cout << endl;
                cout << "Please Enter the quantity of this product you want: ";
                cin >> Custs[constant].reservations[Custs[constant].res].F[j].quantity;
                Custs[constant].reservations[Custs[constant].res].foodOrderCount++;
                j++;
                break;
            }
            else if (code == d[i].code)
            {
                Custs[constant].reservations[Custs[constant].res].D[k].code = d[i].code;
                Custs[constant].reservations[Custs[constant].res].D[k].name = d[i].name;
                Custs[constant].reservations[Custs[constant].res].D[k].price = d[i].price;
                cout << "You ordered: " << d[i].name << endl;
                cout << "Code: " << d[i].code << endl;
                cout << "Price: " << d[i].price << "EGP" << endl;

                cout << endl;
                cout << "Please Enter the quantity of this product you want: ";
                cin >> Custs[constant].reservations[Custs[constant].res].D[k].quantity;
                Custs[constant].reservations[Custs[constant].res].drinksOrderCount++;
                k++;
                break;
            }
            else if (i == Nfood + Ndrinks && code != d[i].code && code != f[i].code) // w di kman ya abdo mtensash
            {
                cout << "Invalid code, please try again.\n"
                     << endl;
            }
        }
        while (true)
        {
            cout << "\n\nWould you like to add another product to your cart?" << endl;
            cout << " If yes enter y\n"
                 << " If no enter n or anything except y\n";
            cin.ignore();
            cin.get(ans);
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n\n";
                continue;
            }
            else
                break;
        }
        cin.ignore();

    } while (ans == 'y' || ans == 'Y');
    // cout << "Your Total cost is: " << Totalcost << endl;
    cout << "\n\nEnjoy your meal!^_^\n\n"
         << endl;

    return Totalcost;
}

// Some variables to get the employee of the week/month/year
const int day_in_seconds = 24 * 60 * 60;
time_t lastWeekReset = time(0);  // El wa2t el hybda2 fih el program w nbda2 n7seb el arba7 mn awl el osbo3 (Should be stored in the database file)
time_t lastMonthReset = time(0); // El wa2t el hybda2 fih el program w nbda2 n7seb el arba7 mn awl el shahr (Should be stored in the database file)
time_t lastYearReset = time(0);  // El wa2t el hybda2 fih el program w nbda2 n7seb el arba7 mn awl el sana (Should be stored in the database file)

float earnings;            // This will store the price the user pays for later use in the getTopEmployee function
bool shift = true;         // ********** Byb2a true lma ay employee y3ml login **********
int shiftIndex = constant; // ********** El index bta3 el employee el 3amal login fel array bta3 el works (For example: works[5]) 3shan el earnings htedaf lel employee da **********

int employeeOfWeekIndex;
int employeeOfMonthIndex;
int employeeOfYearIndex;

// --Jimmy's function-- Billing System function for customers, takes a reservation from the user & the tax as parameters
void billingSystemCustomer(Reservation res, float tax)
{
    cout << "Hi there! Hope you had a great time with us. Here is your bill:" << "\n\n";

    cout << setw(37) << left << "PlayStation for " + to_string(res.time) + " hours"  // Time spent playing
         << setw(10) << left << to_string(int(round(res.total))) + " EGP" << "\n\n"; // PlayStation rent price

    cout << "Food & Drinks:" << "\n\n";
    cout << setw(7) << left << "QTY"             // Quantity column header of the food/drink
         << setw(30) << left << "Description"    // Name column header of the food/drink
         << setw(10) << left << "Price" << "\n"; // Price column header of the food/drink

    int totalFoodPrice = 0;
    // Displaying and calculating the total price of the current food using a for loop
    for (int i = 0; i < res.foodOrderCount; i++)
    {                                                                                               // Loop n times the number of the foods ordered
        cout << setw(7) << left << res.F[i].quantity                                                // Display quantity
             << setw(30) << left << res.F[i].name                                                   // Display name
             << setw(10) << left << to_string(res.F[i].price * res.F[i].quantity) + " EGP" << "\n"; // Display and calculate price (food price * quantity)
        totalFoodPrice = totalFoodPrice + (res.F[i].price * res.F[i].quantity);                     // Add the current food price to the total price of foods
    }

    int totalDrinksPrice = 0;
    // Displaying and calculating the total price of the current drink using a for loop
    for (int j = 0; j < res.drinksOrderCount; j++)
    {                                                                                               // Loop n times the number of the drinks ordered
        cout << setw(7) << left << res.D[j].quantity                                                // Display quantity
             << setw(30) << left << res.D[j].name                                                   // Display name
             << setw(10) << left << to_string(res.D[j].price * res.D[j].quantity) + " EGP" << "\n"; // Display and calculate price (drink price * quantity)
        totalDrinksPrice = totalDrinksPrice + (res.D[j].price * res.D[j].quantity);                 // Add the current drink price to the total price of drinks
    }

    float subtotal = res.total + totalFoodPrice + totalDrinksPrice; // Calculate subtotal
    float total_price = subtotal + ((tax / 100) * subtotal);        // Calculate total (subtotal + tax)

    cout << "\n"
         << setw(37) << left << "Subtotal"
         << setw(10) << left << to_string(int(round(subtotal))) + " EGP" << "\n"; // Display subtotal (total price without the tax)
    cout << setw(37) << left << "Total (including " + to_string(int(round(tax))) + "% tax)"
         << setw(10) << left << to_string(int(round(total_price))) + " EGP"; // Display total (total price WITH the tax)

    earnings = total_price;
}

// --Jimmy's function-- Display employee of the week/month/year function, takes the employees array (works[]) & the array index of the currently logged in employee
void getTopEmployee(customer works[], int shiftIndex)
{
    time_t currentTime = time(0); // Time in seconds since 1970 (El wa2t mn awl ma el function di yt3melaha run)

    if (shift)
    {
        works[shiftIndex].emp.weeklyEarnings += earnings;  // Add weekly earnings to the currently logged in employee (Should be stored in the database file)
        works[shiftIndex].emp.monthlyEarnings += earnings; // Add monthly earnings to the currently logged in employee (Should be stored in the database file)
        works[shiftIndex].emp.yearlyEarnings += earnings;  // Add yearly earnings to the currently logged in employee (Should be stored in the database file)
    }

    float weeklyMax = works[0].emp.weeklyEarnings;
    float monthlyMax = works[0].emp.monthlyEarnings;
    float yearlyMax = works[0].emp.yearlyEarnings;
    employeeOfWeekIndex = 0;
    employeeOfMonthIndex = 0;
    employeeOfYearIndex = 0;

    for (int i = 0; i < workers_num; i++)
    { // Loop over all employees
        // Get employee of the week
        if (works[i].emp.weeklyEarnings > weeklyMax)
        { // Get the employee with the most earnings the past week by their index
            weeklyMax = works[i].emp.weeklyEarnings;
            employeeOfWeekIndex = i; // Save the employee's index
        }

        // Get employee of the month
        if (works[i].emp.monthlyEarnings > monthlyMax)
        { // Get the employee with the most earnings the past month by their index
            monthlyMax = works[i].emp.monthlyEarnings;
            employeeOfMonthIndex = i; // Save the employee's index
        }

        // Get employee of the year
        if (works[i].emp.yearlyEarnings > yearlyMax)
        { // Get the employee with the most earnings the past year by their index
            yearlyMax = works[i].emp.yearlyEarnings;
            employeeOfYearIndex = i; // Save the employee's index
        }
    }

    cout << "Employee of the week: " << works[employeeOfWeekIndex].name << ", Earnings: " << weeklyMax << " EGP\n";    // Display employee of the week
    cout << "Employee of the month: " << works[employeeOfMonthIndex].name << ", Earnings: " << monthlyMax << " EGP\n"; // Display employee of the month
    cout << "Employee of the year: " << works[employeeOfYearIndex].name << ", Earnings: " << yearlyMax << " EGP\n";    // Display employee of the year

    // Check if 7 days have passed to reset the earnings
    if (difftime(currentTime, lastWeekReset) >= 7 * day_in_seconds)
    { // Check hal el wa2t mn awl el osbo3 l7ad dlw2ti (in seconds) = 7 ayam (in seconds)?
        for (int i = 0; i < workers_num; i++)
        {                                    // Loop over all employees
            works[i].emp.weeklyEarnings = 0; // Reset all of the employees earnings by the end of this week
        }
        lastWeekReset = currentTime; // Reset the current week to start calculting new earnings from employees and display the employee of the week
    }

    // Check if 30 days have passed to reset the earnings
    if (difftime(currentTime, lastMonthReset) >= 30 * day_in_seconds)
    { // Check hal el wa2t mn awl el shahr l7ad dlw2ti (in seconds) = 30 yom (in seconds)?
        for (int i = 0; i < workers_num; i++)
        {                                     // Loop over all employees
            works[i].emp.monthlyEarnings = 0; // Reset all of the employees earnings by the end of this month
        }
        lastMonthReset = currentTime; // Reset the current month to start calculting new earnings from employees and display the employee of the month
    }

    // Check if 365 days have passed to reset the earnings
    if (difftime(currentTime, lastYearReset) >= 365 * day_in_seconds)
    { // Check hal el wa2t mn awl el sana l7ad dlw2ti (in seconds) = 365 yom (in seconds)?
        for (int i = 0; i < workers_num; i++)
        {                                    // Loop over all employees
            works[i].emp.yearlyEarnings = 0; // Reset all of the employees earnings by the end of this year
        }
        lastYearReset = currentTime; // Reset the current year to start calculting new earnings from employees and display the employee of the year
    }
}

void Reservations()
{
    char snacks;
    cout << "\nWelcome at our reservation page :)\n";
    cout << "\nPlease press M for Multiplayer or S for Single   ";
TypeChoice:
    cin >> Custs[constant].reservations[Custs[constant].res].type; // The user chooses the type of reservation
    if (cin.fail() ||
        (Custs[constant].reservations[Custs[constant].res].type != 'M' &&
         Custs[constant].reservations[Custs[constant].res].type != 'S' &&
         Custs[constant].reservations[Custs[constant].res].type != 'm' &&
         Custs[constant].reservations[Custs[constant].res].type != 's')) // Validation to avoid error and unpredictable behaviour
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n";
        goto TypeChoice;
    }
GameChoice:
    cout << "What game are you going to play ? (1 = Fifa, 2 = PES, 3 = Mortal Kombat, 4 = Fortnite) ";
    cin >> Custs[constant].reservations[Custs[constant].res].game;
    if (cin.fail())
    {
        cout << "Invalid input\n\n"
             << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto GameChoice;
    }
Duration:
    cout << "How much time will you stay (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )   ";
    cin >> Custs[constant].reservations[Custs[constant].res].time;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto Duration;
    }
EnterCafe:
    cout << "Press Y if you need any snacks (If not press any button)  ";
    cin.ignore();
    cin >> snacks;
    cin.ignore();
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto EnterCafe;
    }
    if (snacks == 'Y' || snacks == 'y')
        cafeMenu(Nfood, Ndrinks);
DateAndTime:
    cout << "Enter date of reservation (DD/MM/YYYY) Ex.: 02/03/2025\n";
    getline(cin, Custs[constant].reservations[Custs[constant].res].date);
    if (Custs[constant].reservations[Custs[constant].res].date[2] != '/' ||
        Custs[constant].reservations[Custs[constant].res].date[5] != '/') // Date validation
    {
        cout << "\n<<Invalid input>>\n\n";
        goto DateAndTime;
    }

    bool date_exists = false; // Checks if the reservation is made in the same date of another reservation
    for (int i = 0; i < customers_num; i++)
    {
        for (int j = 0; j < resCount; j++)
        {
            if (Custs[constant].reservations[Custs[constant].res].date == Custs[i].reservations[j].date)
            {
                date_exists = true;
            }
        }
    }

    cout << "\nEnter the start time of the reservation in the following form ( hh:00 ) " << endl;

    getline(cin, Custs[constant].reservations[Custs[constant].res].clock);
    if (Custs[constant].reservations[Custs[constant].res].clock[2] != ':' ||
        (Custs[constant].reservations[Custs[constant].res].clock[0] != '0' &&
         Custs[constant].reservations[Custs[constant].res].clock[0] != '1')) // Time validation
    {
        cout << "\nInvalid input, try again\n\n";
        goto DateAndTime;
    }
    Custs[constant].reservations[Custs[constant].res].StartTime = stoi(Custs[constant].reservations[Custs[constant].res].clock.substr(0, 2));                                                        // The start time of the reservation
    Custs[constant].reservations[Custs[constant].res].EndTime = stoi(Custs[constant].reservations[Custs[constant].res].clock.substr(0, 2)) + Custs[constant].reservations[Custs[constant].res].time; // The end time of the reservation

    bool time_exists = false; // Checks if the reservation is made in the same time of another reservation
    for (int i = 0; i < customers_num; i++)
    {
        for (int j = 0; j < resCount; j++)
        {
            if (Custs[constant].reservations[Custs[constant].res].StartTime >= Custs[i].reservations[resCount].StartTime &&
                Custs[constant].reservations[Custs[constant].res].StartTime < Custs[i].reservations[resCount].EndTime)
            {
                time_exists = true;
            }
        }
    }
    if (date_exists && time_exists) // Increases the number of reserved devices
    {
        reserved_devices++;
    }

    Custs[constant].reservations[Custs[constant].res].billNumber = bill++;
    cout << "\nYour reservation has been made successfully!\n\n";
    cout << "\nYour reservation number is: " << Custs[constant].reservations[Custs[constant].res].billNumber << endl;
    cout << "Date : "
         << Custs[constant].reservations[Custs[constant].res].date << endl;
    cout << "Time : From " << Custs[constant].reservations[Custs[constant].res].clock << " to " << Custs[constant].reservations[Custs[constant].res].EndTime << ":00" << endl
         << endl;
    Custs[constant].res++;
}
void viewInformation()
{
    char ask;               // The user wants to change his password or not
    string currentPassword; // Compares the passwords
    cout << "\n\nHere are your personal information :\n";
    cout << "Username : " << Custs[constant].name << endl;
    cout << "ID : " << Custs[constant].ID << endl;
    cout << "Phone numbers :\n";
    for (int i = 0; i < Custs[constant].nums; i++)
    {
        cout << Custs[constant].phoneNumbers[i] << endl;
    }
Asking:
    cout << "To edit your password Press Y\nIf not Press any other button ";
    cin >> ask; // y
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n"
             << endl;
        goto Asking;
    }
Passwordo:
    if (ask == 'y' || ask == 'Y')
    {
        cout << "Enter your current password :";
        cin >> currentPassword;
        if (cin.peek() == ' ' || currentPassword != Custs[constant].password)
        {
            cout << "\nWrong password\n"
                 << endl;
        Askos:
            cout << "To reset your password Press Y\nTo try again press any other button ";
            cin >> ask;     // n
            if (cin.fail()) // Error checking
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n"
                     << endl;
                goto Askos;
            }
            if (ask == 'Y' || ask == 'y')
            {
                forgot();
                return;
            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
                ask = 'y';
                goto Passwordo;
            }
        }
        else
        PasswordMakingV:
            cout << "Please enter your password: ";
        cin >> Custs[constant].password;
        if (cin.peek() == ' ')
        {
            cout << "Your password can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto PasswordMakingV;
        }
        cout << "Please re-enter your password: ";
        cin >> currentPassword;
        if (Custs[constant].password != currentPassword || cin.peek() == ' ')
        {
            cout << endl
                 << "///Passwords don't match please double check it///" << endl
                 << endl;
            goto PasswordMakingV;
        }
        else
            cout << "\nPassword changed successfully\n";
        return;
    }
    else
        return;
}
void viewInformationEmployee()
{
    char ask;               // The user wants to change his password or not
    string currentPassword; // Compares the passwords
    int IDD;                // Takes the ID of the user he wants to view
TakingIDVE:
    cout << "Enter the ID of the customer : ";
    cin >> IDD;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n"
             << endl;
        goto TakingIDVE;
    }
    for (int i = 0; i < customers_num; i++)
    {
        if (IDD != Custs[i].ID && i == customers_num - 1)
        {
            cout << "\nWrong ID, try again\n";
            goto TakingIDVE;
        }
    }

    cout << "Here are the information :\n";
    cout << "Username : " << Custs[IDD - 1].name << endl;
    cout << "ID : " << Custs[IDD - 1].ID << endl;
    cout << "Phone numbers :\n";
    for (int i = 0; i < Custs[IDD - 1].nums; i++)
    {
        cout << Custs[IDD - 1].phoneNumbers[i] << endl;
    }
AskingVE:
    cout << "To edit your password Press Y\nIf not Press any other button ";
    cin >> ask; // y
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n"
             << endl;
        goto AskingVE;
    }
PasswordoVE:
    if (ask == 'y' || ask == 'Y')
    {
        cout << "Enter the current password :";
        cin >> currentPassword;
        if (cin.peek() == ' ' || currentPassword != Custs[IDD - 1].password)
        {
            cout << "\nWrong password\n"
                 << endl;
        AskosVE:
            cout << "To reset the password Press Y\nTo try again press any other button ";
            cin >> ask;     // n
            if (cin.fail()) // Error checking
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n"
                     << endl;
                goto AskosVE;
            }
            if (ask == 'Y' || ask == 'y')
            {
                forgot();
                return;
            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
                ask = 'y';
                goto PasswordoVE;
            }
        }
        else
        PasswordMakingVE:
            cout << "Please enter the password: ";
        cin >> Custs[IDD - 1].password;
        if (cin.peek() == ' ')
        {
            cout << "The password can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto PasswordMakingVE;
        }
        cout << "Please re-enter your password: ";
        cin >> currentPassword;
        if (Custs[IDD - 1].password != currentPassword || cin.peek() == ' ')
        {
            cout << endl
                 << "///Passwords don't match please double check it///" << endl
                 << endl;
            goto PasswordMakingVE;
        }
        else
            cout << "\nPassword changed successfully\n";
        return;
    }
    else
        return;
}
void viewReservation()
{
    int billy; // Bill number
Bill:
    cout << "Enter the bill number : ";
    cin >> billy;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto Bill;
    }
    for (int i = 0; i < Custs[constant].res; i++)
    {
        if (billy != Custs[constant].reservations[i].billNumber && i == Custs[constant].res - 1)
        {
            cout << "\nWrong bill number, try again\n\n";
            goto Bill;
        }
    }
    cout << "Type of reservation : " << Custs[constant].reservations[billy].type << endl;
    cout << "Game : " << Custs[constant].reservations[billy].game << endl;
    cout << "Duration : " << Custs[constant].reservations[billy].time << endl;
    cout << "Date : " << Custs[constant].reservations[billy].date << endl;
    cout << "From " << Custs[constant].reservations[billy].StartTime << " : 00" << endl;
    cout << "To " << Custs[constant].reservations[billy].EndTime << " : 00" << endl
         << endl
         << endl;
    cout << "Cafe orders :" << endl
         << endl;
         
}
char ans;
void editReservation()
{
    do
    {
        cout << "Press H to edit your reservation's duration\nPress T to edit the game and the reservation's type (Single or Multi)\nPress D to edit date and time \n";
        char choice;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            continue;
        }
        else if (choice == 'H' || choice == 'h') // edit time // hours
        {
            cout << "\nHow much time will you stay (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )\n";
            cin >> Custs[constant].reservations[Custs[constant].res].time;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n";
                goto DurationE;
            }
        }
        else if (choice == 'T' || choice == 't') // edit time
        {
            cout << "\nPlease press M for Multiplayer or S for Single   ";
        TypeChoiceE:
            cin >> Custs[constant].reservations[Custs[constant].res].type; // The user chooses the type of reservation
            if (cin.fail() ||
                (Custs[constant].reservations[Custs[constant].res].type != 'M' &&
                 Custs[constant].reservations[Custs[constant].res].type != 'S' &&
                 Custs[constant].reservations[Custs[constant].res].type != 'm' &&
                 Custs[constant].reservations[Custs[constant].res].type != 's')) // Validation to avoid error and unpredictable behaviour
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n";
                goto TypeChoiceE;
            }
        GameChoiceE:
            cout << "What game are you going to play ? (1 = Fifa, 2 = PES, 3 = Mortal Kombat, 4 = Fortnite) ";
            cin >> Custs[constant].reservations[Custs[constant].res].game;
            if (cin.fail())
            {
                cout << "Invalid input" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto GameChoiceE;
            }
        }
        else if (choice == 'd' || choice == 'D') // edit date and time
        {
        DateAndTime:
            cout << "Enter date of reservation (DD/MM/YYYY) Ex.: 02/03/2025\n";
            getline(cin, Custs[constant].reservations[Custs[constant].res].date);
            if (Custs[constant].reservations[Custs[constant].res].date[2] != '/' ||
                Custs[constant].reservations[Custs[constant].res].date[5] != '/') // Date validation
            {
                cout << "\n<<Invalid input>>\n\n";
                goto DateAndTime;
            }

            bool date_exists = false; // Checks if the reservation is made in the same date of another reservation
            for (int i = 0; i < customers_num; i++)
            {
                for (int j = 0; j < resCount; j++)
                {
                    if (Custs[constant].reservations[Custs[constant].res].date == Custs[i].reservations[j].date)
                    {
                        date_exists = true;
                    }
                }
            }

            cout << "Enter the start time of the reservation in the following form ( hh:00 ) " << endl;

            getline(cin, Custs[constant].reservations[Custs[constant].res].clock);
            if (Custs[constant].reservations[Custs[constant].res].clock[2] != ':' ||
                (Custs[constant].reservations[Custs[constant].res].clock[0] != '0' &&
                 Custs[constant].reservations[Custs[constant].res].clock[0] != '1')) // Time validation
            {
                cout << "\n\nInvalid input, try again\n\n";
                goto DateAndTime;
            }
            Custs[constant].reservations[Custs[constant].res].StartTime = stoi(Custs[constant].reservations[Custs[constant].res].clock.substr(0, 2));                                                        // The start time of the reservation
            Custs[constant].reservations[Custs[constant].res].EndTime = stoi(Custs[constant].reservations[Custs[constant].res].clock.substr(0, 2)) + Custs[constant].reservations[Custs[constant].res].time; // The end time of the reservation

            bool time_exists = false; // Checks if the reservation is made in the same time of another reservation
            for (int i = 0; i < customers_num; i++)
            {
                for (int j = 0; j < resCount; j++)
                {
                    if (Custs[constant].reservations[Custs[constant].res].StartTime >= Custs[i].reservations[resCount].StartTime &&
                        Custs[constant].reservations[Custs[constant].res].StartTime < Custs[i].reservations[resCount].EndTime)
                    {
                        time_exists = true;
                    }
                }
            }
            if (date_exists && time_exists) // Increases the number of reserved devices
            {
                reserved_devices++;
            }
        }

    // leave this part right where it issss
    Repetition:
        cout << endl
             << "To edit more information Press Y\nIf not Press any other button\n"; // repetition
        cin.get(ans);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            goto Repetition;
        }
        if (ans != 'y' && ans != 'Y')
        {
            cout << "Information updated successfully\n";
            cout << "\nYour reservation number is: " << Custs[constant].reservations[Custs[constant].res].billNumber << endl;
            cout << "Date : "
                 << Custs[constant].reservations[Custs[constant].res].date << endl;
            cout << "Time : From " << Custs[constant].reservations[Custs[constant].res].clock << " to " << Custs[constant].reservations[Custs[constant].res].EndTime << ":00" << endl
                 << endl;
        }

    } while (ans == 'y' || ans == 'Y');
}

int login()
{
    char pass; // Checks if the user forgot his password
    customer check;
    check.ID = -1;
    bool lamba = true;
    while (lamba)
    {
    tany2:
        cout << "Who are you?" << endl
             << "Customer = 1 , Worker = 2" << endl;
        cin >> i;
        if ((i != 1 && i != 2) || cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            goto tany2;
        }
        cout << "Please enter the following data:" << endl;
    stupid:
        cout << "username:";
        cin >> check.name;
        if (cin.peek() == ' ')
        {
            cout << "Your username can't contain spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto stupid;
        }
        cout << endl
             << "ID:";
        cin >> check.ID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    stupid2:
        cout << endl
             << "password:";
        cin >> check.password;
        if (cin.peek() == ' ')
        {
            cout << "Your password can't contain spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto stupid2;
        }
        if (i == 1)
        {
            if (check.ID == -1 || check.ID > Custsize)
                cout << "\nInvalid id" << endl;
            else
            {
                if (check.name == Custs[check.ID - 1].name && check.password == Custs[check.ID - 1].password)
                {
                    cout << "You have logged in successfully!";
                    lamba = false;
                    loggedIn = true;
                    constant = check.ID - 1;
                }
                else
                {
                    cout << "\nWrong Credentials!\n"
                         << endl;
                    cout << "Forgot your password ? press Y if not press any other button\n";
                    cin >> pass;
                    if (pass == 'y' || pass == 'Y')
                    {
                        forgot();
                    }
                }
            }
        }
        else if (i == 2)
        {
            if (check.ID == -1 || check.ID > worksize)
                cout << "Invalid id" << endl;
            else
            {
                if (check.name == works[check.ID - 1].name && check.password == works[check.ID - 1].password)
                {
                    cout << "You have logged in successfully!";
                    lamba = false;
                    loggedIn = true;
                    constant = check.ID - 1;
                }
                else
                    cout << "Wrong Credentials!" << endl;
            }
        }
    }
    return constant;
}
void registr()
{
    int i;               // Customer or worker
    int nums;            // Number of phone numbers
    string reenter_Pass; // Let the user reenter his password to check it.
CustWork:
    cout << "Who are you?" << endl
         << "Press 1 for Customer and 2 for worker. ";
    cin >> i;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n"
             << endl;
        goto CustWork;
    }
    if (i == 1)
    {
        cout << "Please enter your information: " << endl;

    Username:
        cout << "Username: ";
        cin >> Custs[custCount].name;
        if (cin.peek() == ' ')
        {
            cout << "Your username can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Username;
        }
    phoning:
        cout << "How many phone numbers do you have? ";
        cin >> nums;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl;
            goto phoning;
        }
        for (int i = 0; i < nums; i++)
        {
        PhoneNumbering:
            cout << "Phone number: " << endl;
            cin >> Custs[custCount].phoneNumbers[i];
            if (cin.peek() == ' ')
            {
                cout << "Your phone number can't include spaces" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto PhoneNumbering;
            }
        }
            cout << "Phone number: " << endl;
            cin >> Custs[custCount].phoneNumbers[i];
            if (cin.peek() == ' ')
            {
                cout << "Your phone number can't include spaces" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto PhoneNumbering;
            }
        }
    PasswordMaking:
        cout << "Please enter your password: ";

        string password1;
        char ch55;
        while (true)
        {
            ch55 = getch();
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
                cout << "*";
            }
        }
        cout << endl;

        password1 = Custs[custCount].password;

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
            ch66 = getch();
            if (ch66 == '\r')
            {
                break;
            }
            if (ch66 == '\b')
            {
                password1.pop_back();
                cout << "\b \b";
            }
            if (ch66 != '\b')
            {
                password1 += ch66;
                cout << "*";
            }
        }
        cout << endl;
        password2 = reenter_Pass;

        if (Custs[custCount].password != reenter_Pass || cin.peek() == ' ')
        {
            cout << endl
                 << "///Passwords don't match please double check it///" << endl
                 << endl;
            goto PasswordMaking;
        }
    Questions:
        int q; // Which question does the user want
        cout << "Choose a question (This question will be used when you reset your password)" << endl
             << "What's your first Pet Name?=1" << endl
             << "What's your first Love Name?=2" << endl
             << "What's your fav Color?=3" << endl;
        cin >> q;
        if ((q != 1 && q != 2 && q != 3) || cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            goto Questions;
        }
        Custs[custCount].question.no = q;
    Questions2:
        cout << "Answer Please : " << endl;
        cin >> Custs[custCount].question.ans;
        if (cin.peek() == ' ')
        {
            cout << "Your answer can't include spaces." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Questions2;
        }
    }
    else
    {
        cout << "Please enter your information: " << endl;

    Username2:
        cout << "Username: ";
        cin >> Custs[custCount].name;
        if (cin.peek() == ' ')
        {
            cout << "Your username can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Username2;
        }
    phoning2:
        cout << "How many phone numbers do you have? ";
        cin >> Custs[custCount].nums;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl;
            goto phoning2;
        }
        for (int i = 0; i < Custs[custCount].nums; i++)
        {
        PhoneNumbering2:
            cout << "Phone number: " << endl;
            cin >> Custs[custCount].phoneNumbers[i];
            if (cin.peek() == ' ')
            {
                cout << "Your phone number can't include spaces" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto PhoneNumbering2;
            }
        }
    PasswordMaking2:
        cout << "Please enter your password: ";
        cin >> Custs[custCount].password;
        if (cin.peek() == ' ')
        {
            cout << "Your password can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto PasswordMaking2;
        }
        cout << "Please re-enter your password: ";
        cin >> reenter_Pass;
        if (Custs[custCount].password != reenter_Pass || cin.peek() == ' ')
        {
            cout << endl
                 << "///Passwords don't match please double check it///" << endl
                 << endl;
            goto PasswordMaking2;
        }
    Questions222:
        int q; // Which question does the user want
        cout << "Choose a question (This question will be used when you reset your password)" << endl
             << "What's your first Pet Name?=1" << endl
             << "What's your first Love Name?=2" << endl
             << "What's your fav Color?=3" << endl;
        cin >> q;
        if ((q != 1 && q != 2 && q != 3) || cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            goto Questions222;
        }
        Custs[custCount].question.no = q;
    Questions22:
        cout << "Answer Please : " << endl;
        cin >> Custs[custCount].question.ans;
        if (cin.peek() == ' ')
        {
            cout << "Your answer can't include spaces." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Questions22;
        }
    }
    cout << endl
         << "Account created successfully!" << endl
         << endl;
    Custs[custCount].ID = ID;
    cout << "Your ID is " << ID++ << endl
         << endl;
    workCount++;
}
void forgot()
{
    int i; // Customer or Worker
    customer check;
    check.ID = -1;

CustomerOrWorker:
    cout << "Who are you?" << endl
         << "Customer = 1 , Worker = 2" << endl;
    cin >> i;
    if ((i != 1 && i != 2) || cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto CustomerOrWorker;
    }
    if (i == 1)
    {
    IDcheck:
        cout << "Please Enter Your ID:" << endl;
        cin >> check.ID;
        if (check.ID == -1 || check.ID > custCount + 1)
        {
            cout << "Invalid id" << endl;
            goto IDcheck;
        }
    QuestionMaking:
        if (Custs[check.ID - 1].question.no == 1)
            cout << "What's your first Pet Name?" << endl;
        else if (Custs[check.ID - 1].question.no == 2)
            cout << "What's your first Love Name?" << endl;
        else if (Custs[check.ID - 1].question.no == 3)
            cout << "What's your favourite Color?" << endl;
        cin >> check.question.ans;
        if (cin.peek() == ' ')
        {
            cout << "Your answer can't include spaces \n"
                 << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto QuestionMaking;
        }
        if (check.question.ans == Custs[check.ID - 1].question.ans)
        {
        AssignNewPassword:
            cout << "Write New Password!" << endl;
            cin >> Custs[check.ID - 1].password;
            if (cin.peek() == ' ')
            {
                cout << "Your password can't include spaces" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto AssignNewPassword;
            }
            else
            {
                cout << "\nPassword changed succesfully\n";
            }
        }
        else
        {
            cout << "Invalid answer please try again" << endl;
            goto QuestionMaking;
        }
    }
    else if (i == 2)
    {
    IDcheck2:
        cout << "Please Enter Your ID:" << endl;
        cin >> check.ID;
        if (check.ID == -1 || check.ID > worksize)
        {
            cout << "invalid id" << endl;
            goto IDcheck2;
        }
    QuestionMaking2:
        if (works[check.ID - 1].question.no == 1)
            cout << "What's your first Pet Name?" << endl;
        else if (works[check.ID - 1].question.no == 2)
            cout << "What's your first Love Name?" << endl;
        else if (works[check.ID - 1].question.no == 3)
            cout << "What's your favourite Color?" << endl;
        cin >> check.question.ans;
        if (cin.peek() == ' ')
        {
            cout << "Your answer can't include spaces \n"
                 << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto QuestionMaking2;
        }
        if (check.question.ans == works[check.ID - 1].question.ans)
        {
        AssignNewPassword2:
            cout << "Write New Password!" << endl;
            cin >> works[check.ID - 1].password;
            if (cin.peek() == ' ')
            {
                cout << "Your password can't include spaces" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto AssignNewPassword2;
            }
            else
            {
                cout << "\nPassword changed succesfully\n";
            }
        }
        else
        {
            cout << "Invalid answer please try again" << endl;
            goto QuestionMaking2;
        }
    }
}
void mostPlayed()
{
    // calculating the frequencies
    int freq_arr[game_count] = {0};
    for (int i = 0; i < customers_num; i++)
    {
        for (int j = 0; j < resCount; j++)
        {
            for (int k = 1; k <= game_count; k++)
            {
                if (Custs[i].reservations[j].game == k)
                    freq_arr[k - 1]++;
            }
        }
    }
    // adding the frequencies to memory associate it w the games
    for (int i = 0; i < game_count; i++)
    {
        Final_most[i].Mostfrequency = freq_arr[i];
    }

    // Replace duplicate numbers in freq_arr with 0, keeping one instance
    for (int i = 0; i < game_count; i++)
    {
        for (int j = i + 1; j < game_count; j++)
        {
            if (freq_arr[i] == freq_arr[j] && freq_arr[i] != 0) // Check for duplicates
            {
                freq_arr[j] = 0; // Replace duplicate with 0, keeping the first instance
            }
        }
    }
    // sorting the frequencies
    for (int i = 0; i < game_count - 1; i++)
    {
        for (int j = 0; j < game_count - i - 1; j++)
        {
            if (freq_arr[j] < freq_arr[j + 1]) // Sort in descending order
            {
                // Swap frequencies
                int temp = freq_arr[j];
                freq_arr[j] = freq_arr[j + 1];
                freq_arr[j + 1] = temp;
            }
        }
    }

    cout << endl
         << "The most played games are :\n";

    for (int j = 0; j < 3; j++)
    {
        cout << j + 1;
        if (j == 0)
            cout << "st place : ";
        else if (j == 1)
            cout << "nd place :";
        else if (j == 2)
            cout << "rd place : ";
        for (int i = 0; i < game_count; i++)
        {
            if (Final_most[i].Mostfrequency == freq_arr[j] && freq_arr[j] != 0)
            {
                cout << Final_most[i].game_name << "\n";
                cout << "PLAYED " << Final_most[i].Mostfrequency << " TIMES\n";
            }
        }
    }
}