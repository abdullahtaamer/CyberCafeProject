#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <fstream>
#include <ctime>
#define light 3
#define pastry 7
#define foodCount 40     // Max number of food in one reservation
#define drinkCount 40    // Max number of drink in one reservation
#define resCount 40      // Max number of reservations for one customer
#define customers_num 40 // Number of customers we can have
#define workers_num 40   // Number of workers we can have
#define game_count 6     // sarahss
#define singlePrice 30   // Price of 1 hour for the type Singleplayer mode
#define multiPrice 50    // Price of 1 hour for the type Multiplayer mode
using namespace std;
int bill = 0;
int i;                    // = 1 if the user is a customer , = 2 if the user is a worker
int constant;             // The used id during a process
int custCount = 0;        // Lw la'etha b ay rakam gher 0 khaliha 0
int workCount = 0;        // Lw la'etha b ay rakam gher 0 khaliha 0
int reserved_devices = 0; // Number of reserved devices in a single period
long long ID = 0;
const int Nfood = 13, Ndrinks = 15, available_Devices = 10;
float tax = 14;        // Tax of 14%
bool loggedIn = false; // True if the user logged in successfully
int Most_playedCount = 0;
bool lamba = true;
int storeID; // Used to store the id of the logged in user

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
    char date[11];
    char StartTime[6];
    int StartTimeint;
    int EndTimeint;
    char EndTime[6];
    int billNumber;
    int foodOrderCount;   // How many f the user had ordered
    int drinksOrderCount; // How many drinks the user had ordered
    food F[foodCount];
    drinks D[drinkCount];
    char type; //
    int time;  // Duration
    float total;
    int game;
    string gameName; // (1 = Fifa, 2 = PES, 3 = Mortal Kombat, 4 = GTA V, 5 = COD, 6 = fall guys)
    string clock;    // from char : 5 to char : 10
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
float cafeMenu(int, int);
void billingSystemCustomer(Reservation res, float tax);
void Reservations();
void editReservation();
int login();
void registr();
void forgot();
void getTopEmployee(customer works[], int shiftIndex);
void viewReservationsOfTheDay();
void viewInformation();
void viewInformationE();
void viewInformationEmployee();
void viewReservation();
void mostPlayed();
void viewReservationE();
void write();
void read();
int main()
{ read();
    // cafeMenu(Nfood, Ndrinks); //m7dsh yfok el comment dahh aw ymsa7o ~Sarah .... Mtz3a'ish ~Abdullah
    int question; //  What does the user want to do
    cout << "Welcome to our paradise ::)\n\n";
Menu:
    cout << "\n\nTo log in Press 1\nTo create a new account Press 2\nTo exit the program Press 3\n";
    cin >> question;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto Menu;
    }
    if (question == 1)
    {
        login();
        write();
        if (!loggedIn)
            goto Menu;
    }
    else if (question == 2)
    {
        registr();
        write();
        goto Menu;
    }
    else if (question == 3)
    {
        write();
        return 0;
    }
    else
    {
        cout << "\nInvalid input\n\n";
        goto Menu;
    }
LogedIn:
    if (loggedIn && i != 2)
    {
        cout << "\n\nTo make a new reservation Press 1\nTo edit your reservation Press 2\nTo view your information Press 3\nTo view your reservations Press 4\nTo log out Press 5\n";
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
            write();
            goto LogedIn;
        }
        else if (question == 2)
        {
            editReservation();
            write();
            goto LogedIn;
        }
        else if (question == 3)
        {
            viewInformation();
            write();
            goto LogedIn;
        }
        else if (question == 4)
        {
            viewReservation();
            cout << "\n\nDo you want to edit your reservation ?\npress Y if YES\nTo go back to main menu Press any other button\n";
            char u1; // u is for answerrs
            cin >> u1;
            if (cin.fail()) // validation w yarab yb'a sa7 ~ Sarah ... ghlt tb3n ykhrebet elly 3alemek brmaga bs ana khlas zabataha ~Abdullah
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n\n";
                goto LogedIn;
            }
            else if (u1 == 'y' || u1 == 'Y')
            {editReservation();
                    write();}
            else
                goto LogedIn;
        }

        else if (question == 5)
            goto Menu;
        else
        {
            cout << "\nInvalid input\n\n";
            goto LogedIn;
        }
    }
    else
    {
        cout << "\n\nTo make a new reservation Press 1\nTo edit your reservation Press 2\nTo view the employee of the week/month/year press 3\nTo view your information Press 4\nTo view a customer's information Press 5\nTo view the most played games Press 6\nTo view reservations of the day Press 7\nTo view a reservation Press 8\nTo log out Press 9 \n";
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
            write();
            goto LogedIn;
        }
        else if (question == 2)
        {
            editReservation();
            write();
            goto LogedIn;
        }
        else if (question == 3)
        {
            getTopEmployee(works, constant);
            write();
            goto LogedIn;
        }
        else if (question == 4)
        {
            viewInformationE();
            write();
            goto LogedIn;
        }
        else if (question == 5)
        {
            viewInformationEmployee();
            write();
            goto LogedIn;
        }
        else if (question == 6)
        {
            mostPlayed();
            write();
            goto LogedIn;
        }
        else if (question == 7)
        {
            viewReservationsOfTheDay();
            write();
            goto LogedIn;
        }
        else if (question == 8)
        {
            viewReservationE();
            write();
            goto LogedIn;
        }
        else if (question == 9)
            goto Menu;
        else
        {
            cout << "\n\nInvalid input\n";
            goto LogedIn;
        }
    }

    // getTopEmployee(works,l shiftIndex);  // Call getTopEmployee with employees array (works[]) & the array index of the currently logged in employee
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
        else if (type == 4)
        {
            for (int i = 7; i < Nf; i++)
            {
                cout << endl
                     << f[i].name << "\nCode: " << f[i].code << "\nPrice: " << f[i].price << endl;
            }
        }
        else
        {
            cout << "\nInvalid input\n";
            continue;
        }
        while (true)
        {

            cout << "\nWould you like to show another food category ?" << endl;
            cout << " If yes enter y or anything except n\n"
                 << " If no enter n\n";
            cin.ignore();
            cin >> ans;
            if (cin.fail() || (ans != 'n' && ans != 'N' && ans != 'y' && ans != 'Y'))
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
    while (true)
    {
        cout << endl
        << "\nDrinks menu" << "\n " << "" << endl;
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
        else if (type == 5)
        {
            for (int i = 14; i < Nd; i++)
            {
                cout << endl
                     << d[i].name << "\nCode: " << d[i].code << "\nPrice: " << d[i].price << endl;
            }
        }
        else 
        {
            cout << "\nInvalid input\n";
            continue;
        }
        while (true)
        {
            cout << "\nWould you like to show another drink category ?" << endl;
            cout << " If yes press y or any button\n"
                 << " If no enter press n\n";
            cin >> ans;
            if (cin.fail() || (ans != 'n' && ans != 'N' && ans != 'y' && ans != 'Y'))
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
        bool found = false;
        for (; i < Nfood + Ndrinks; i++) // Matensash tzabatha
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
                found = true;
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
                found = true;
                break;
            }
            else if (i == Nfood + Ndrinks - 1 && !found) // w di kman mtensash
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
bool shift = false;        // ********** Byb2a true lma ay employee y3ml login **********
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

// --Jimmy's function-- View all reservations made by users today, for employees
void viewReservationsOfTheDay()
{
    time_t currentTime = time(0);             // Get the current time in seconds (not very human readable)
    tm *local_time = localtime(&currentTime); // Converts the current time to a more human readable format

    char numericDate[80]; // Will hold the formatted date as a string
    char textDate[80];    // Will hold the formatted date as a string

    strftime(numericDate, sizeof(numericDate), "%d/%m/%Y", local_time); // The strftime function formats the date stored in local_time and stores the result as a string in the numericDate array (for example: 24/04/2025)
    strftime(textDate, sizeof(textDate), "%A, %B, %Y", local_time);     // Formats the date stored in local_time and stores the result as a string in the textDate array (for example: Thursday, April, 2025)

    int numOfReservationsToday = 0; // Number of reservations made today

    cout << "Today's reservations: " << textDate << " (" << numericDate << ")" << "\n\n";

    for (int i = 0; i < customers_num; i++)
    { // Loop over all customers
        for (int j = 0; j < Custs[i].res; j++)
        { // Loop over all reservations made by each customer
            // Check if today's date (numericDate) is the same as the date of the reservation (Custs[i].reservations[j].date)
            if (numericDate == Custs[i].reservations[j].date)
            {
                cout << "Reservation made by " << Custs[i].name << ", from " << Custs[i].reservations[j].StartTime << " to " << Custs[i].reservations[j].EndTime << "\n";
                numOfReservationsToday++; // Increment the number of reservations made today
            }
        }
    }

    if (numOfReservationsToday == 0)
    {
        cout << "There were no reservations made today." << "\n";
    }
    else
    {
        cout << "There were " << numOfReservationsToday << " reservations made today." << "\n";
    }
}

void Reservations()
{
    int id;
    char snacks;
    bool found = false;
    if (shift)
    {
    IDEnteration:
        cout << "\nThe ID of the customer : ";
        cin >> id;
        if (cin.fail() || id >= custCount || id < 0)
        {
            cout << "Invalid input\n\n"
                 << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto IDEnteration;
        }
        for (int i = 0; i < custCount; i++)
        {
            if (id == Custs[i].ID)
            {
                found = true;
                constant = id;
            }
        }
        if (!found)
        {
            cout << "There is no customer with this ID\n";
            goto IDEnteration;
        }
    }

    cout << "\nWelcome at our reservation page :)\n";
TypeChoice:
    cout << "\nPlease press M for Multiplayer or S for Single   ";
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
    cout << "What game are you going to play ? (1 = Fifa, 2 = PES, 3 = Mortal Kombat, 4 = GTA V, 5 = COD, 6 = fall guys)\t";
    cin >> Custs[constant].reservations[Custs[constant].res].game;
    if (cin.fail() || Custs[constant].reservations[Custs[constant].res].game > 6 ||
        Custs[constant].reservations[Custs[constant].res].game < 0) // Game validation
    {
        cout << "Invalid input\n\n"
             << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto GameChoice;
    }
    // Assigning the name of games
    if (Custs[constant].reservations[Custs[constant].res].game == 1)
        Custs[constant].reservations[Custs[constant].res].gameName = "Fifa";
    else if (Custs[constant].reservations[Custs[constant].res].game == 2)
        Custs[constant].reservations[Custs[constant].res].gameName = "PES";
    else if (Custs[constant].reservations[Custs[constant].res].game == 3)
        Custs[constant].reservations[Custs[constant].res].gameName = "Mortal Kombat";
    else if (Custs[constant].reservations[Custs[constant].res].game == 4)
        Custs[constant].reservations[Custs[constant].res].gameName = "GTA";
    else if (Custs[constant].reservations[Custs[constant].res].game == 5)
        Custs[constant].reservations[Custs[constant].res].gameName = "COD";
    else if (Custs[constant].reservations[Custs[constant].res].game == 6)
        Custs[constant].reservations[Custs[constant].res].gameName = "Fall guys";

Duration:
    cout << "How much time will you stay ? (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )   ";
    cin >> Custs[constant].reservations[Custs[constant].res].time;
    if (cin.fail() || Custs[constant].reservations[Custs[constant].res].time < 1)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto Duration;
    }

    if (Custs[constant].reservations[Custs[constant].res].type == 's' || Custs[constant].reservations[Custs[constant].res].type == 'S') // Reservation price (Not cafe recipt and tax included)
        Custs[constant].reservations[Custs[constant].res].total = singlePrice * Custs[constant].reservations[Custs[constant].res].time;
    else
        Custs[constant].reservations[Custs[constant].res].total = multiPrice * Custs[constant].reservations[Custs[constant].res].time;

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
    bool validDate = false;
    while (!validDate)
    {
        cout << "Enter reservation date (dd/mm/yyyy): ";
        cin >> Custs[constant].reservations[Custs[constant].res].date;

        if (strlen(Custs[constant].reservations[Custs[constant].res].date) == 10 &&
            isdigit(Custs[constant].reservations[Custs[constant].res].date[0]) && isdigit(Custs[constant].reservations[Custs[constant].res].date[1]) &&
            Custs[constant].reservations[Custs[constant].res].date[2] == '/' &&
            isdigit(Custs[constant].reservations[Custs[constant].res].date[3]) && isdigit(Custs[constant].reservations[Custs[constant].res].date[4]) &&
            Custs[constant].reservations[Custs[constant].res].date[5] == '/' &&
            isdigit(Custs[constant].reservations[Custs[constant].res].date[6]) && isdigit(Custs[constant].reservations[Custs[constant].res].date[7]) &&
            isdigit(Custs[constant].reservations[Custs[constant].res].date[8]) && isdigit(Custs[constant].reservations[Custs[constant].res].date[9])) // Date validation
        {
            validDate = true;
        }
        else
        {
            cout << "Invalid date format. Please use dd/mm/yyyy.\n";
        }
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

    cin >> Custs[constant].reservations[Custs[constant].res].StartTime;
    if (Custs[constant].reservations[Custs[constant].res].StartTime[2] != ':' ||
        (Custs[constant].reservations[Custs[constant].res].StartTime[0] != '0' &&
         Custs[constant].reservations[Custs[constant].res].StartTime[0] != '1') ||
         Custs[constant].reservations[Custs[constant].res].StartTime[0] > 9 ||
         Custs[constant].reservations[Custs[constant].res].StartTime[1] > 9 ||
         Custs[constant].reservations[Custs[constant].res].StartTime[3] > 9 ||
         Custs[constant].reservations[Custs[constant].res].StartTime[4] > 9 ||
         cin.peek() == ' ') // Time validation
    {
        cout << "\nInvalid input, try again\n\n";
        goto DateAndTime;
    }
    Custs[constant].reservations[Custs[constant].res].StartTimeint = stoi(Custs[constant].reservations[Custs[constant].res].StartTime);
    Custs[constant].reservations[Custs[constant].res].EndTimeint = Custs[constant].reservations[Custs[constant].res].StartTimeint + Custs[constant].reservations[Custs[constant].res].time;
    bool time_exists = false; // Checks if the reservation is made in the same time of another reservation
    for (int i = 0; i < customers_num; i++)
    {
        for (int j = 0; j < resCount; j++)
        {
            if (Custs[constant].reservations[Custs[constant].res].StartTime >= Custs[i].reservations[j].StartTime &&
                Custs[constant].reservations[Custs[constant].res].StartTime < Custs[i].reservations[j].EndTime)
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
    cout << "Time : From " << Custs[constant].reservations[Custs[constant].res].StartTime << " to " << Custs[constant].reservations[Custs[constant].res].EndTimeint << ":00" << endl
         << endl;
    billingSystemCustomer(Custs[constant].reservations[Custs[constant].res], tax);
    if (shift)
    {
        works[storeID].reservations[works[storeID].res] = Custs[constant].reservations[Custs[constant].res]; // Storing the reservation in the worker's data
        works[storeID].emp.weeklyEarnings += earnings;                                                       // Add weekly earnings to the currently logged in employee (Should be stored in the database file)
        works[storeID].emp.monthlyEarnings += earnings;                                                      // Add monthly earnings to the currently logged in employee (Should be stored in the database file)
        works[storeID].emp.yearlyEarnings += earnings;                                                       // Add yearly earnings to the currently logged in employee (Should be stored in the database file)
        works[storeID].res++;
    }
    Custs[constant].res++;
    constant = storeID;
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
        string password4;
        char ch88;
        while (true)
        {
            ch88 = getch();
            if (ch88 == '\b' && password4.empty())
            {
                continue;
            }
            if (ch88 == '\r')
            {
                break;
            }
            if (ch88 == '\b')
            {
                password4.pop_back();
                cout << "\b \b";
            }
            if (ch88 != '\b')
            {
                password4 += ch88;
                cout << "*";
            }
        }
        cout << endl;
        currentPassword = password4;
        if (currentPassword != Custs[constant].password)
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
        string password5;
        char ch888;
        while (true)
        {
            ch888 = getch();
            if (ch888 == '\b' && password5.empty())
            {
                continue;
            }
            if (ch888 == '\r')
            {
                break;
            }
            if (ch888 == '\b')
            {
                password5.pop_back();
                cout << "\b \b";
            }
            if (ch888 != '\b')
            {
                password5 += ch888;
                cout << "*";
            }
        }
        cout << endl;
        Custs[constant].password = password5;
        cout << "Please re-enter your password: ";
        string password3;
        char ch889;
        while (true)
        {
            ch889 = getch();
            if (ch889 == '\b' && password3.empty())
            {
                continue;
            }
            if (ch889 == '\r')
            {
                break;
            }
            if (ch889 == '\b')
            {
                password3.pop_back();
                cout << "\b \b";
            }
            if (ch889 != '\b')
            {
                password3 += ch889;
                cout << "*";
            }
        }
        cout << endl;
        currentPassword = password3;
        if (Custs[constant].password != currentPassword)
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
void viewInformationE()
{
    char ask;               // The user wants to change his password or not
    string currentPassword; // Compares the passwords
    cout << "\n\nHere are your personal information :\n";
    cout << "Username : " << works[constant].name << endl;
    cout << "ID : " << works[constant].ID << endl;
    cout << "Phone numbers :\n";
    for (int i = 0; i < works[constant].nums; i++)
    {
        cout << works[constant].phoneNumbers[i] << endl;
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
        string password4;
        char ch88;
        while (true)
        {
            ch88 = getch();
            if (ch88 == '\b' && password4.empty())
            {
                continue;
            }
            if (ch88 == '\r')
            {
                break;
            }
            if (ch88 == '\b')
            {
                password4.pop_back();
                cout << "\b \b";
            }
            if (ch88 != '\b')
            {
                password4 += ch88;
                cout << "*";
            }
        }
        cout << endl;
        currentPassword = password4;
        if (currentPassword != works[constant].password)
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
        string password5;
        char ch888;
        while (true)
        {
            ch888 = getch();
            if (ch888 == '\b' && password5.empty())
            {
                continue;
            }
            if (ch888 == '\r')
            {
                break;
            }
            if (ch888 == '\b')
            {
                password5.pop_back();
                cout << "\b \b";
            }
            if (ch888 != '\b')
            {
                password5 += ch888;
                cout << "*";
            }
        }
        cout << endl;
        works[constant].password = password5;
        cout << "Please re-enter your password: ";
        string password3;
        char ch889;
        while (true)
        {
            ch889 = getch();
            if (ch889 == '\b' && password3.empty())
            {
                continue;
            }
            if (ch889 == '\r')
            {
                break;
            }
            if (ch889 == '\b')
            {
                password3.pop_back();
                cout << "\b \b";
            }
            if (ch889 != '\b')
            {
                password3 += ch889;
                cout << "*";
            }
        }
        cout << endl;
        currentPassword = password3;
        if (works[constant].password != currentPassword)
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
    cout << "Username : " << Custs[IDD].name << endl;
    cout << "ID : " << Custs[IDD].ID << endl;
    cout << "Phone numbers :\n";
    for (int i = 0; i < Custs[IDD].nums; i++)
    {
        cout << Custs[IDD].phoneNumbers[i] << endl;
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
        string password3;
        char ch88;
        while (true)
        {
            ch88 = getch();
            if (ch88 == '\b' && password3.empty())
            {
                continue;
            }
            if (ch88 == '\r')
            {
                break;
            }
            if (ch88 == '\b')
            {
                password3.pop_back();
                cout << "\b \b";
            }
            if (ch88 != '\b')
            {
                password3 += ch88;
                cout << "*";
            }
        }
        cout << endl;
        currentPassword = password3;
        if (currentPassword != Custs[IDD].password)
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
        string password33;
        char ch887;
        while (true)
        {
            ch887 = getch();
            if (ch887 == '\b' && password33.empty())
            {
                continue;
            }
            if (ch887 == '\r')
            {
                break;
            }
            if (ch887 == '\b')
            {
                password33.pop_back();
                cout << "\b \b";
            }
            if (ch88 != '\b')
            {
                password33 += ch887;
                cout << "*";
            }
        }
        cout << endl;
        Custs[IDD].password = password33;
        cout << "Please re-enter your password: ";
        string password334;
        char ch8877;
        while (true)
        {
            ch8877 = getch();
            if (ch8877 == '\b' && password334.empty())
            {
                continue;
            }
            if (ch8877 == '\r')
            {
                break;
            }
            if (ch8877 == '\b')
            {
                password334.pop_back();
                cout << "\b \b";
            }
            if (ch8877 != '\b')
            {
                password334 += ch8877;
                cout << "*";
            }
        }
        cout << endl;
        currentPassword = password334;
        if (Custs[IDD].password != currentPassword)
        {
            cout << endl
                 << "///Passwords don't match please double check it///" << endl
                 << endl;
            goto PasswordMakingVE;
        }
        else
            cout << "\nPassword changed successfully\n";
    }
    else
    {
        cout << "To view another customer's information Press Y\nTo go to the main menu Press any other button\n";
        cin >> ask;
        if (ask == 'y' || ask == 'Y')
        {
            goto TakingIDVE;
        }
    }
}
void viewReservation()
{
    int billy; // Bill number
    bool found = false;
    char ans; // Checks if the user wants to view any other reservation
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
    if (Custs[constant].reservations[billy].time < 1)
    {
        cout << "Reservation not found\n\n";
        goto Bill;
    }
    cout << "Type of reservation : " << Custs[constant].reservations[billy].type << endl;
    cout << "Game : " << Custs[constant].reservations[billy].gameName << endl;
    cout << "Duration : " << Custs[constant].reservations[billy].time << " hours" << endl;
    cout << "Date : " << Custs[constant].reservations[billy].date << endl;
    cout << "From " << Custs[constant].reservations[billy].StartTime << " : 00" << endl;
    cout << "To " << Custs[constant].reservations[billy].EndTime << " : 00" << endl
         << endl
         << endl;
    cout << "Cafe orders :" << endl
         << endl;

    cout << setw(37) << left << "PlayStation for " + to_string(Custs[constant].reservations[billy].time) + " hours"  // Time spent playing
         << setw(10) << left << to_string(int(round(Custs[constant].reservations[billy].total))) + " EGP" << "\n\n"; // PlayStation rent price

    cout << "Food & Drinks:" << "\n\n";
    cout << setw(7) << left << "QTY"             // Quantity column header of the food/drink
         << setw(30) << left << "Description"    // Name column header of the food/drink
         << setw(10) << left << "Price" << "\n"; // Price column header of the food/drink

    int totalFoodPrice = 0;
    // Displaying and calculating the total price of the current food using a for loop
    for (int i = 0; i < Custs[constant].reservations[billy].foodOrderCount; i++)
    {                                                                                                                                                               // Loop n times the number of the foods ordered
        cout << setw(7) << left << Custs[constant].reservations[billy].F[i].quantity                                                                                // Display quantity
             << setw(30) << left << Custs[constant].reservations[billy].F[i].name                                                                                   // Display name
             << setw(10) << left << to_string(Custs[constant].reservations[billy].F[i].price * Custs[constant].reservations[billy].F[i].quantity) + " EGP" << "\n"; // Display and calculate price (food price * quantity)
        totalFoodPrice = totalFoodPrice + (Custs[constant].reservations[billy].F[i].price * Custs[constant].reservations[billy].F[i].quantity);                     // Add the current food price to the total price of foods
    }

    int totalDrinksPrice = 0;
    // Displaying and calculating the total price of the current drink using a for loop
    for (int j = 0; j < Custs[constant].reservations[billy].drinksOrderCount; j++)
    {                                                                                                                                                               // Loop n times the number of the drinks ordered
        cout << setw(7) << left << Custs[constant].reservations[billy].D[j].quantity                                                                                // Display quantity
             << setw(30) << left << Custs[constant].reservations[billy].D[j].name                                                                                   // Display name
             << setw(10) << left << to_string(Custs[constant].reservations[billy].D[j].price * Custs[constant].reservations[billy].D[j].quantity) + " EGP" << "\n"; // Display and calculate price (drink price * quantity)
        totalDrinksPrice = totalDrinksPrice + (Custs[constant].reservations[billy].D[j].price * Custs[constant].reservations[billy].D[j].quantity);                 // Add the current drink price to the total price of drinks
    }

    float subtotal = Custs[constant].reservations[billy].total + totalFoodPrice + totalDrinksPrice; // Calculate subtotal
    float total_price = subtotal + ((tax / 100) * subtotal);                                        // Calculate total (subtotal + tax)

    cout << "\n"
         << setw(37) << left << "Subtotal"
         << setw(10) << left << to_string(int(round(subtotal))) + " EGP" << "\n"; // Display subtotal (total price without the tax)
    cout << setw(37) << left << "Total (including " + to_string(int(round(tax))) + "% tax)"
         << setw(10) << left << to_string(int(round(total_price))) + " EGP"; // Display total (total price WITH the tax)

    cout << "\n\nTo view any reservation Press Y\nTo go back press any other button\n";
    cin >> ans;
    if (ans == 'y' || ans == 'Y')
    {
        goto Bill;
    }
}
void viewReservationE()
{
    int billy; // Bill number
    int IDD;   // User ID
    char ans;  // Checks if the user wants to view any other reservation
    bool found = false;
BillE:
    cout << "Enter the user ID : ";
    cin >> IDD;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto BillE;
    }
    cout << "Enter the bill number : ";
    cin >> billy;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto BillE;
    }
    if (Custs[IDD].reservations[billy].time < 1)
    {
        cout << "Reservation not found\n\n";
        goto BillE;
    }

    cout << "Type of reservation : " << Custs[IDD].reservations[billy].type << endl;
    cout << "Game : " << Custs[IDD].reservations[billy].gameName << endl;
    cout << "Duration : " << Custs[IDD].reservations[billy].time << " hours" << endl;
    cout << "Date : " << Custs[IDD].reservations[billy].date << endl;
    cout << "From " << Custs[IDD].reservations[billy].StartTime << " : 00" << endl;
    cout << "To " << Custs[IDD].reservations[billy].EndTime << " : 00" << endl
         << endl
         << endl;
    cout << "Cafe orders :" << endl
         << endl;

    cout << setw(37) << left << "PlayStation for " + to_string(Custs[IDD].reservations[billy].time) + " hours"  // Time spent playing
         << setw(10) << left << to_string(int(round(Custs[IDD].reservations[billy].total))) + " EGP" << "\n\n"; // PlayStation rent price

    cout << "Food & Drinks:" << "\n\n";
    cout << setw(7) << left << "QTY"             // Quantity column header of the food/drink
         << setw(30) << left << "Description"    // Name column header of the food/drink
         << setw(10) << left << "Price" << "\n"; // Price column header of the food/drink

    int totalFoodPrice = 0;
    // Displaying and calculating the total price of the current food using a for loop
    for (int i = 0; i < Custs[IDD].reservations[billy].foodOrderCount; i++)
    {                                                                                                                                                     // Loop n times the number of the foods ordered
        cout << setw(7) << left << Custs[IDD].reservations[billy].F[i].quantity                                                                           // Display quantity
             << setw(30) << left << Custs[IDD].reservations[billy].F[i].name                                                                              // Display name
             << setw(10) << left << to_string(Custs[IDD].reservations[billy].F[i].price * Custs[IDD].reservations[billy].F[i].quantity) + " EGP" << "\n"; // Display and calculate price (food price * quantity)
        totalFoodPrice = totalFoodPrice + (Custs[IDD].reservations[billy].F[i].price * Custs[IDD].reservations[billy].F[i].quantity);                     // Add the current food price to the total price of foods
    }

    int totalDrinksPrice = 0;
    // Displaying and calculating the total price of the current drink using a for loop
    for (int j = 0; j < Custs[IDD].reservations[billy].drinksOrderCount; j++)
    {                                                                                                                                                     // Loop n times the number of the drinks ordered
        cout << setw(7) << left << Custs[IDD].reservations[billy].D[j].quantity                                                                           // Display quantity
             << setw(30) << left << Custs[IDD].reservations[billy].D[j].name                                                                              // Display name
             << setw(10) << left << to_string(Custs[IDD].reservations[billy].D[j].price * Custs[IDD].reservations[billy].D[j].quantity) + " EGP" << "\n"; // Display and calculate price (drink price * quantity)
        totalDrinksPrice = totalDrinksPrice + (Custs[IDD].reservations[billy].D[j].price * Custs[IDD].reservations[billy].D[j].quantity);                 // Add the current drink price to the total price of drinks
    }

    float subtotal = Custs[IDD].reservations[billy].total + totalFoodPrice + totalDrinksPrice; // Calculate subtotal
    float total_price = subtotal + ((tax / 100) * subtotal);                                   // Calculate total (subtotal + tax)

    cout << "\n"
         << setw(37) << left << "Subtotal"
         << setw(10) << left << to_string(int(round(subtotal))) + " EGP" << "\n"; // Display subtotal (total price without the tax)
    cout << setw(37) << left << "Total (including " + to_string(int(round(tax))) + "% tax)"
         << setw(10) << left << to_string(int(round(total_price))) + " EGP"; // Display total (total price WITH the tax)

    cout << "\n\nTo view any reservation Press Y\nTo go back press any other button\n";
    cin >> ans;
    if (ans == 'y' || ans == 'Y')
    {
        goto BillE;
    }
}
char ans;
void editReservation()
{
    int billy;
Billoo:
    cout << "Enter the bill number : ";
    cin >> billy;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input\n\n";
        goto Billoo;
    }
    if (Custs[constant].reservations[billy].time < 1)
    {
        cout << "Reservation not found\n\n";
        goto Billoo;
    }
    do
    {
        cout << "\nPress H to edit your reservation's duration\nPress T to edit the game and the reservation's type (Single or Multi)\nPress D to edit date and time \n";
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
        DurationE:
            cout << "\nHow much time will you stay (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )\n";
            cin >> Custs[constant].reservations[billy].time;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n";
                goto DurationE;
            }
        }
        else if (choice == 'T' || choice == 't') // edit type
        {
            cout << "\nPlease press M for Multiplayer or S for Single   ";
        TypeChoiceE:
            cin >> Custs[constant].reservations[billy].type; // The user chooses the type of reservation
            if (cin.fail() ||
                (Custs[constant].reservations[billy].type != 'M' &&
                 Custs[constant].reservations[billy].type != 'S' &&
                 Custs[constant].reservations[billy].type != 'm' &&
                 Custs[constant].reservations[billy].type != 's')) // Validation to avoid error and unpredictable behaviour
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n";
                goto TypeChoiceE;
            }
        GameChoiceE:
            cout << "What game are you going to play ? (1 = Fifa, 2 = PES, 3 = Mortal Kombat, 4 = GTA V, 5 = COD, 6 = fall guys) ";
            cin >> Custs[constant].reservations[billy].game;
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
            bool validDate = false;
            while (!validDate)
            {
                cout << "Enter reservation date (dd/mm/yyyy): ";
                cin >> Custs[constant].reservations[billy].date;

                if (strlen(Custs[constant].reservations[billy].date) == 10 &&
                    isdigit(Custs[constant].reservations[billy].date[0]) && isdigit(Custs[constant].reservations[billy].date[1]) &&
                    Custs[constant].reservations[billy].date[2] == '/' &&
                    isdigit(Custs[constant].reservations[billy].date[3]) && isdigit(Custs[constant].reservations[billy].date[4]) &&
                    Custs[constant].reservations[billy].date[5] == '/' &&
                    isdigit(Custs[constant].reservations[billy].date[6]) && isdigit(Custs[constant].reservations[billy].date[7]) &&
                    isdigit(Custs[constant].reservations[billy].date[8]) && isdigit(Custs[constant].reservations[billy].date[9])) // Dte va;idation
                {
                    validDate = true;
                }
                else
                {
                    cout << "Invalid date format. Please use dd/mm/yyyy.\n";
                }
            }
            Custs[constant].reservations[billy].StartTimeint = stoi(Custs[constant].reservations[billy].StartTime);
            Custs[constant].reservations[billy].EndTimeint = Custs[constant].reservations[billy].StartTimeint + Custs[constant].reservations[billy].time;

            bool date_exists = false; // Checks if the reservation is made in the same date of another reservation
            for (int i = 0; i < customers_num; i++)
            {
                for (int j = 0; j < resCount; j++)
                {
                    if (Custs[constant].reservations[billy].date == Custs[i].reservations[j].date)
                    {
                        date_exists = true;
                    }
                }
            }

            cout << "Enter the start time of the reservation in the following form ( hh:00 ) " << endl;

            cin >> Custs[constant].reservations[billy].StartTime;
            if (Custs[constant].reservations[billy].clock[2] != ':' ||
                (Custs[constant].reservations[billy].clock[0] != '0' &&
                 Custs[constant].reservations[billy].clock[0] != '1')) // Time validation
            {
                cout << "\n\nInvalid input, try again\n\n";
                goto DateAndTime;
            }
            bool time_exists = false; // Checks if the reservation is made in the same time of another reservation
            for (int i = 0; i < customers_num; i++)
            {
                for (int j = 0; j < resCount; j++)
                {
                    if (Custs[constant].reservations[billy].StartTime >= Custs[i].reservations[j].StartTime &&
                        Custs[constant].reservations[billy].StartTime < Custs[i].reservations[j].EndTime)
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
        cin >> ans;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            goto Repetition;
        }
        else if (ans != 'y' && ans != 'Y')
        {
            cout << "Information updated successfully\n";
            cout << "\nYour reservation number is: " << Custs[constant].reservations[billy].billNumber << endl;
            cout << "Date : "
                 << Custs[constant].reservations[billy].date << endl;
            cout << "Time : From " << Custs[constant].reservations[billy].clock << " to " << Custs[constant].reservations[billy].EndTime << ":00" << endl
                 << endl;
        }

    } while (ans == 'y' || ans == 'Y');
}

int login()
{
    char pass; // Checks if the user forgot his password
    customer check;
    check.ID = -1;
tany2:
    cout << "Who are you?" << endl
         << "Customer = 1 , Worker = 2" << endl;
    cin >> i;
    if ((i != 1 && i != 2) || cin.fail())
    {
        cout << "\nInvalid input\n";
        cin.clear();
        cin.ignore(1000, '\n');
        goto tany2;
    }
    cout << "Please enter the following data:" << endl;
    cout << "username:";
    cin >> check.name;
    if (cin.peek() == ' ')
    {
        cout << "Your username can't contain spaces" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto tany2;
    }
    cout << endl
         << "ID:";
    cin >> check.ID;
    check.ID--;
    if (cin.fail())
    {
        cout << "\nInvalid ID, Try again\n";
        cin.clear();
        cin.ignore(1000, '\n');
        goto tany2;
    }
stupid2:
    cout << endl
         << "password:";

    string password3;
    char ch88;
    while (true)
    {
        ch88 = getch();
        if (ch88 == '\b' && password3.empty())
        {
            continue;
        }
        if (ch88 == '\r')
        {
            break;
        }
        if (ch88 == '\b')
        {
            password3.pop_back();
            cout << "\b \b";
        }
        if (ch88 != '\b')
        {
            password3 += ch88;
            cout << "*";
        }
    }
    cout << endl;
    check.password = password3;
    if (i == 1)
    {
        if (check.ID == -1 || check.ID >= custCount) 
                {
            cout << "\nInvalid id\n"
                 << endl;
            goto tany2;
        }
        else
        {
            if (check.name == Custs[check.ID].name && check.password == Custs[check.ID].password)
            {
                cout << "You have logged in successfully!";
                loggedIn = true;
                constant = check.ID;
                storeID = constant;
            }
            else
            {
                cout << "\nWrong Credentials!\n"
                     << endl;
            passso:
                cout << "Forgot your password ? press Y\nTo go back to main menu press M\nTo try again Press any other button\n";
                cin >> pass;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    goto passso;
                }
                else if (pass == 'y' || pass == 'Y')
                {
                    forgot();
                }
                else if (pass == 'm' || pass == 'M')
                    return 0;
                else
                    goto tany2;
            }
        }
    }
    else if (i == 2)
    {
        if (check.ID == -1 || check.ID >= workCount)
        {
            cout << "Invalid id" << endl;
            goto tany2;
        }
        else
        {
            if (check.name == works[check.ID].name && check.password == works[check.ID].password)
            {
                cout << "You have logged in successfully!";
                lamba = false;
                loggedIn = true;
                shift = true;
                constant = check.ID;
                storeID = constant;
            }
            else
            {
                cout << "\nWrong Credentials!\n"
                     << endl;
                cout << "Forgot your password ? press Y\nTo go back to main menu press M\nTo try again Press any other button\n";
                cin >> pass;
                if (pass == 'y' || pass == 'Y')
                {
                    forgot();
                }
                else if (pass == 'm' || pass == 'M')
                    return 0;
                else if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                    goto tany2;
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
        cout << "How many phone numbers do you have? (3 numbers maximum) ";
        cin >> nums;
        if (cin.fail() || nums > 3 || nums < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl;
            goto phoning;
        }
        Custs[custCount].nums = nums;
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
    PasswordMaking:
        cout << "Please enter your password: ";
        string password1;
        char ch55;
        while (true)
        {
            ch55 = getch();
            if (ch55 == '\b' && password1.empty())
            {
                continue;
            }
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

        Custs[custCount].password = password1;

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
            if (ch66 == '\b' && password2.empty())
            {
                continue;
            }
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
        cout << endl
             << "Account created successfully!" << endl
             << endl;
        cout << "Your ID is " << custCount+1 << endl
             << endl;
        Custs[custCount].ID = custCount++;
    }
    else if (i == 2)
    {
        cout << "Please enter your information: " << endl;

    Username2:
        cout << "Username: ";
        cin >> works[workCount].name;
        if (cin.peek() == ' ')
        {
            cout << "Your username can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Username2;
        }
    phoning2:
        cout << "How many phone numbers do you have? ";
        cin >> works[workCount].nums;
        if (cin.fail() || works[workCount].nums > 3 || works[workCount].nums < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl;
            goto phoning2;
        }
        for (int i = 0; i < works[workCount].nums; i++)
        {
        PhoneNumbering2:
            cout << "Phone number: " << endl;
            cin >> works[workCount].phoneNumbers[i];
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

        string password4;
        char ch99;
        while (true)
        {
            ch99 = getch();
            if (ch99 == '\b' && password4.empty())
                continue;
            if (ch99 == '\r')
            {
                break;
            }
            if (ch99 == '\b')
            {
                password4.pop_back();
                cout << "\b \b";
            }
            if (ch99 != '\b')
            {
                password4 += ch99;
                cout << "*";
            }
        }
        cout << endl;
        works[workCount].password = password4;

        if (cin.peek() == ' ')
        {
            cout << "Your password can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto PasswordMaking2;
        }
        cout << "Please re-enter your password: ";

        string password7;
        char ch22;
        while (true)
        {
            ch22 = getch();
            if (ch22 == '\b' && password7.empty())
                continue;
            if (ch22 == '\r')
            {
                break;
            }
            if (ch22 == '\b')
            {
                password7.pop_back();
                cout << "\b \b";
            }
            if (ch22 != '\b')
            {
                password7 += ch22;
                cout << "*";
            }
        }
        cout << endl;
        reenter_Pass = password7;

        if (works[workCount].password != reenter_Pass || cin.peek() == ' ')
        {
            cout << endl
                 << "///Passwords don't match please double check it///" << endl
                 << endl;
            goto PasswordMaking2;
        }
    Questions222:
        int q; // Which question does the user want
        cout << "Choose a question (This question will be used when you reset your password)" << endl
             << "What's your first Pet Name? = 1" << endl
             << "What's your first Love Name? = 2" << endl
             << "What's your fav Color? = 3" << endl;
        cin >> q;
        if ((q != 1 && q != 2 && q != 3) || cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            goto Questions222;
        }
        works[workCount].question.no = q;
    Questions22:
        cout << "Answer Please : " << endl;
        cin >> works[workCount].question.ans;
        if (cin.peek() == ' ')
        {
            cout << "Your answer can't include spaces." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Questions22;
        }
        cout << endl
             << "Account created successfully!" << endl
             << endl;
        cout << "Your ID is " << workCount+1 << endl
             << endl;
        works[workCount].ID = workCount++;
    }
    else
    {
        cout << "\nInvalid input\n";
        goto CustWork;
    }
}
void forgot()
{
    int i;       // Customer or Worker
    char checkk; // Checks if the user doesn't remember the answer of his question
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
        if (check.ID == -1 || check.ID > custCount)
        {
            cout << "Invalid id" << endl;
            goto IDcheck;
        }
    QuestionMaking:
        if (Custs[check.ID].question.no == 1)
            cout << "What's your first Pet Name?" << endl;
        else if (Custs[check.ID].question.no == 2)
            cout << "What's your first Love Name?" << endl;
        else if (Custs[check.ID].question.no == 3)
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
        if (check.question.ans == Custs[check.ID].question.ans)
        {
        AssignNewPassword:
            cout << "Write New Password!" << endl;

            string password5;
            char ch00;
            while (true)
            {
                ch00 = getch();
                if (ch00 == '\b' && password5.empty())
                {
                    continue;
                }
                if (ch00 == '\r')
                {
                    break;
                }
                if (ch00 == '\b')
                {
                    password5.pop_back();
                    cout << "\b \b";
                }
                if (ch00 != '\b')
                {
                    password5 += ch00;
                    cout << "*";
                }
            }
            cout << endl;
            Custs[check.ID].password = password5;
            cout << "\nPassword changed succesfully\n";
        }
        else
        {
            cout << "Invalid answer please try again" << endl;
        checko:
            cout << "If you don't remember your answer Press Y\nIf not Press any other button\n";
            cin >> checkk;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n\n";
                goto checko;
            }
            else if (checkk == 'y' || checkk == 'Y')
            {
                cout << "Please call our hotline 13012\n";
                return;
            }
            else
                goto QuestionMaking;
        }
    }
    else if (i == 2)
    {
    IDcheck2:
        cout << "Please Enter Your ID:" << endl;
        cin >> check.ID;
        if (check.ID == -1 || check.ID > workCount)
        {
            cout << "invalid id" << endl;
            goto IDcheck2;
        }
    QuestionMaking2:
        if (works[check.ID].question.no == 1)
            cout << "What's your first Pet Name?" << endl;
        else if (works[check.ID].question.no == 2)
            cout << "What's your first Love Name?" << endl;
        else if (works[check.ID].question.no == 3)
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
        if (check.question.ans == works[check.ID].question.ans)
        {
        AssignNewPassword2:
            cout << "Write New Password!" << endl;

            string password6;
            char ch11;
            while (true)
            {
                ch11 = getch();
                if (ch11 == '\b' && password6.empty())
                    continue;
                if (ch11 == '\r')
                {
                    break;
                }
                if (ch11 == '\b')
                {
                    password6.pop_back();
                    cout << "\b \b";
                }
                if (ch11 != '\b')
                {
                    password6 += ch11;
                    cout << "*";
                }
            }
            cout << endl;
            works[check.ID].password = password6;

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
            cout << "Invalid answer please try again\n"
                 << endl;
        checkoo:
            cout << "If you don't remember your answer Press Y\nIf not Press any other button\n";
            cin >> checkk;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input\n\n";
                goto checkoo;
            }
            else if (checkk == 'y' || checkk == 'Y')
            {
                cout << "Please call our hotline 13012\n\n";
                return;
            }
            else
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
                cout << "PLAYEDD " << Final_most[i].Mostfrequency << " TIMES\n";
            }
            cout <<endl;
        }
    }
}
void write()
{
    ofstream out("customers.txt", ios::out);
    if (!out.is_open())
    {
        cout << "Error opening customers file for writing." << endl;
        return;
    }

    out << custCount << endl; // Write number of customers first
    for (int i = 0; i < custCount; i++)
    {
        // Write basic customer info
        out << Custs[i].name << endl;
        out << Custs[i].ID << endl;
        out << Custs[i].password << endl;
        out << Custs[i].nums << endl;
        out << Custs[i].res << endl; // Number of reservations

        // Write phone numbers
        for (int j = 0; j < Custs[i].nums; j++)
        {
            out << Custs[i].phoneNumbers[j] << endl;
        }

        // Write security question
        out << Custs[i].question.no << endl;
        out << Custs[i].question.ans << endl;

        // Write reservations
        for (int j = 0; j < Custs[i].res; j++)
        {
            out << Custs[i].reservations[j].date << endl;
            out << Custs[i].reservations[j].StartTime << endl;
            out << Custs[i].reservations[j].StartTimeint << endl;
            out << Custs[i].reservations[j].EndTimeint << endl;
            out << Custs[i].reservations[j].EndTime << endl;
            out << Custs[i].reservations[j].billNumber << endl;
            out << Custs[i].reservations[j].foodOrderCount << endl;
            out << Custs[i].reservations[j].drinksOrderCount << endl;
            out << Custs[i].reservations[j].type << endl;
            out << Custs[i].reservations[j].time << endl;
            out << Custs[i].reservations[j].total << endl;
            out << Custs[i].reservations[j].game << endl;
            out << Custs[i].reservations[j].gameName << endl;
            out << Custs[i].reservations[j].clock << endl;

            // Write food orders
            for (int k = 0; k < Custs[i].reservations[j].foodOrderCount; k++)
            {
                out << Custs[i].reservations[j].F[k].name << endl;
                out << Custs[i].reservations[j].F[k].code << endl;
                out << Custs[i].reservations[j].F[k].price << endl;
                out << Custs[i].reservations[j].F[k].quantity << endl;
            }

            // Write drink orders
            for (int k = 0; k < Custs[i].reservations[j].drinksOrderCount; k++)
            {
                out << Custs[i].reservations[j].D[k].name << endl;
                out << Custs[i].reservations[j].D[k].code << endl;
                out << Custs[i].reservations[j].D[k].price << endl;
                out << Custs[i].reservations[j].D[k].quantity << endl;
            }
        }
    }
    out.close();

    ofstream out2("workers.txt", ios::out);
    if (!out2.is_open())
    {
        cout << "Error opening workers file for writing." << endl;
        return;
    }

    out2 << workCount << endl; // Write number of workers first
    for (int i = 0; i < workCount; i++)
    {
        // Write basic worker info
        out2 << works[i].name << endl;
        out2 << works[i].ID << endl;
        out2 << works[i].password << endl;
        out2 << works[i].nums << endl;
        out2 << works[i].res << endl; // Number of reservations
        out2 << works[i].emp.shift << endl;
        out2 << works[i].emp.weeklyEarnings << endl;
        out2 << works[i].emp.monthlyEarnings << endl;
        out2 << works[i].emp.yearlyEarnings << endl;

        // Write phone numbers
        for (int j = 0; j < works[i].nums; j++)
        {
            out2 << works[i].phoneNumbers[j] << endl;
        }

        // Write security question
        out2 << works[i].question.no << endl;
        out2 << works[i].question.ans << endl;

        // Write reservations
        for (int j = 0; j < works[i].res; j++)
        {
            out2 << works[i].reservations[j].date << endl;
            out2 << works[i].reservations[j].StartTime << endl;
            out2 << works[i].reservations[j].StartTimeint << endl;
            out2 << works[i].reservations[j].EndTimeint << endl;
            out2 << works[i].reservations[j].EndTime << endl;
            out2 << works[i].reservations[j].billNumber << endl;
            out2 << works[i].reservations[j].foodOrderCount << endl;
            out2 << works[i].reservations[j].drinksOrderCount << endl;
            out2 << works[i].reservations[j].type << endl;
            out2 << works[i].reservations[j].time << endl;
            out2 << works[i].reservations[j].total << endl;
            out2 << works[i].reservations[j].game << endl;
            out2 << works[i].reservations[j].gameName << endl;
            out2 << works[i].reservations[j].clock << endl;

            // Write food orders
            for (int k = 0; k < works[i].reservations[j].foodOrderCount; k++)
            {
                out2 << works[i].reservations[j].F[k].name << endl;
                out2 << works[i].reservations[j].F[k].code << endl;
                out2 << works[i].reservations[j].F[k].price << endl;
                out2 << works[i].reservations[j].F[k].quantity << endl;
            }

            // Write drink orders
            for (int k = 0; k < works[i].reservations[j].drinksOrderCount; k++)
            {
                out2 << works[i].reservations[j].D[k].name << endl;
                out2 << works[i].reservations[j].D[k].code << endl;
                out2 << works[i].reservations[j].D[k].price << endl;
                out2 << works[i].reservations[j].D[k].quantity << endl;
            }
        }
    }
    out2.close();
}

void read()
{
    ifstream in("customers.txt", ios::in);
    if (!in.is_open())
    {
        cout << "No existing customer data found. Starting fresh." << endl;
        return;
    }

    in >> custCount; // Read number of customers
    for (int i = 0; i < custCount; i++)
    {
        // Read basic customer info
        in >> Custs[i].name;
        in >> Custs[i].ID;
        in >> Custs[i].password;
        in >> Custs[i].nums;
        in >> Custs[i].res; // Number of reservations

        // Read phone numbers
        for (int j = 0; j < Custs[i].nums; j++)
        {
            in >> Custs[i].phoneNumbers[j];
        }

        // Read security question
        in >> Custs[i].question.no;
        in >> Custs[i].question.ans;

        // Read reservations
        for (int j = 0; j < Custs[i].res; j++)
        {
            in >> Custs[i].reservations[j].date;
            in >> Custs[i].reservations[j].StartTime;
            in >> Custs[i].reservations[j].StartTimeint;
            in >> Custs[i].reservations[j].EndTimeint;
            in >> Custs[i].reservations[j].EndTime;
            in >> Custs[i].reservations[j].billNumber;
            in >> Custs[i].reservations[j].foodOrderCount;
            in >> Custs[i].reservations[j].drinksOrderCount;
            in >> Custs[i].reservations[j].type;
            in >> Custs[i].reservations[j].time;
            in >> Custs[i].reservations[j].total;
            in >> Custs[i].reservations[j].game;
            in >> Custs[i].reservations[j].gameName;
            in >> Custs[i].reservations[j].clock;

            // Read food orders
            for (int k = 0; k < Custs[i].reservations[j].foodOrderCount; k++)
            {
                in >> Custs[i].reservations[j].F[k].name;
                in >> Custs[i].reservations[j].F[k].code;
                in >> Custs[i].reservations[j].F[k].price;
                in >> Custs[i].reservations[j].F[k].quantity;
            }

            // Read drink orders
            for (int k = 0; k < Custs[i].reservations[j].drinksOrderCount; k++)
            {
                in >> Custs[i].reservations[j].D[k].name;
                in >> Custs[i].reservations[j].D[k].code;
                in >> Custs[i].reservations[j].D[k].price;
                in >> Custs[i].reservations[j].D[k].quantity;
            }
        }
    }
    in.close();

    ifstream in2("workers.txt", ios::in);
    if (!in2.is_open())
    {
        cout << "No existing worker data found. Starting fresh." << endl;
        return;
    }

    in2 >> workCount; // Read number of workers
    for (int i = 0; i < workCount; i++)
    {
        // Read basic worker info
        in2 >> works[i].name;
        in2 >> works[i].ID;
        in2 >> works[i].password;
        in2 >> works[i].nums;
        in2 >> works[i].res; // Number of reservations
        in2 >> works[i].emp.shift;
        in2 >> works[i].emp.weeklyEarnings;
        in2 >> works[i].emp.monthlyEarnings;
        in2 >> works[i].emp.yearlyEarnings;

        // Read phone numbers
        for (int j = 0; j < works[i].nums; j++)
        {
            in2 >> works[i].phoneNumbers[j];
        }

        // Read security question
        in2 >> works[i].question.no;
        in2 >> works[i].question.ans;

        // Read reservations
        for (int j = 0; j < works[i].res; j++)
        {
            in2 >> works[i].reservations[j].date;
            in2 >> works[i].reservations[j].StartTime;
            in2 >> works[i].reservations[j].StartTimeint;
            in2 >> works[i].reservations[j].EndTimeint;
            in2 >> works[i].reservations[j].EndTime;
            in2 >> works[i].reservations[j].billNumber;
            in2 >> works[i].reservations[j].foodOrderCount;
            in2 >> works[i].reservations[j].drinksOrderCount;
            in2 >> works[i].reservations[j].type;
            in2 >> works[i].reservations[j].time;
            in2 >> works[i].reservations[j].total;
            in2 >> works[i].reservations[j].game;
            in2 >> works[i].reservations[j].gameName;
            in2 >> works[i].reservations[j].clock;

            // Read food orders
            for (int k = 0; k < works[i].reservations[j].foodOrderCount; k++)
            {
                in2 >> works[i].reservations[j].F[k].name;
                in2 >> works[i].reservations[j].F[k].code;
                in2 >> works[i].reservations[j].F[k].price;
                in2 >> works[i].reservations[j].F[k].quantity;
            }

            // Read drink orders
            for (int k = 0; k < works[i].reservations[j].drinksOrderCount; k++)
            {
                in2 >> works[i].reservations[j].D[k].name;
                in2 >> works[i].reservations[j].D[k].code;
                in2 >> works[i].reservations[j].D[k].price;
                in2 >> works[i].reservations[j].D[k].quantity;
            }
        }
    }
    in2.close();
}
