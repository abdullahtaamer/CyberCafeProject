#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <bits/stdc++.h>
#define light 3
#define pastry 7
#define foodCount 40     // Max number of food in one reservation
#define drinkCount 40    // Max number of drink in one reservation
#define resCount 40      // Max number of reservations for one customer
#define customers_num 40 // Number of customers we can have
#define workers_num 40 // Number of workers we can have
using namespace std;
int bill = 0;
int constant;
int custCount = 0;        // Lw la'etha b ay rakam gher 0 khaliha 0
int workCount = 0;        // Lw la'etha b ay rakam gher 0 khaliha 0
int reserved_devices = 0; // Number of reserved devices in a single period
long long ID = 1;
const int Nfood = 13, Ndrinks = 15, available_Devices = 10;
int Custsize = 1; // Ziad hatetha
int worksize = 1; // Ziad hatetha

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
    int game;     // //F = Fifa 25 , M = Mortal kombat ("Eb'o zawedo games 3shan malish fi el gaming")
    string clock; // from char : 5 to char : 10
};

struct security
{
    int no;
    string ans;
};

// Struct for employee earnings
struct employee {
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
    string phoneNumbers[3];
    Reservation reservations[resCount]; // Array of reservations for each customer
    security question;
    int res = 0; // Total number of reservations of a specific customer

    employee emp;
} Custs[customers_num], works[workers_num];

food f[Nfood] = { {"Cheese", 123, 30}, {"Smoked Turky", 222, 40}, {"Chicken", 144, 60}, {"Croissant", 555, 40}, {"Puff pastry", 333, 30}, {"Danish Pastry", 125, 60}, {"Cinnamon Roll", 111, 80}, {"Biscuits or Cookies", 226, 30}, {"Chips or Snacks", 771, 30}, {"Instant Noodless", 126, 40}, {"Mini Pizza", 199, 50}, {"Pan Cakes", 772, 40}, {"Light Burger", 312, 70} };
drinks d[Ndrinks] = { {"Pepsi", 661, 20}, {"Cocacola", 557, 20}, {"Sprite", 993, 20}, {"Black Tea", 441, 20}, {"Green Tea", 777, 25}, {"Mint Tea", 116, 30}, {"Lemon Tea", 447, 30}, {"Espresso", 221, 40}, {"Amreicano", 551, 50}, {"Cappiccino", 141, 650}, {"Latte", 503, 50}, {"Orange Juice", 460, 30}, {"Mango Juice", 668, 40}, {"Strawberry Juice", 334, 40}, {"Bottelet Water", 445, 15} };
// vector<customer> Custs;  //tf is this bro ~sarah
float cafeMenu(int, int);
void billing_system_customer(Reservation Res, float tax);
void Reservations();
void editReservation();
int login();
void registr();
void forgot();

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
    // Test data

    // Custs[0] = {1, "pass123", "Ahmed Ali", {"01012345678", "01198765432", "01234567890"}, {{"01/04/2025", 1001, 3, 3, {{"Cheese", 123, 30, 1}, {"Smoked Turkey", 222, 40, 2}, {"Chicken", 144, 60, 1}}, {{"Pepsi", 661, 20, 2}, {"CocaCola", 557, 20, 1}, {"Espresso", 221, 40, 1}}, 'S', 2, 210.0}, {"02/04/2025", 1002, 3, 3, {{"Croissant", 555, 40, 1}, {"Puff pastry", 333, 30, 1}, {"Danish Pastry", 125, 60, 2}}, {{"Green Tea", 777, 25, 1}, {"Mint Tea", 116, 30, 2}, {"Lemon Tea", 447, 30, 1}}, 'B', 3, 260.0}, {"03/04/2025", 1003, 3, 3, {{"Biscuits", 226, 30, 2}, {"Mini Pizza", 199, 50, 1}, {"Pan Cakes", 772, 40, 2}}, {{"Americano", 551, 50, 1}, {"Cappuccino", 141, 65, 1}, {"Latte", 503, 50, 2}}, 'C', 2, 355.0}, {"04/04/2025", 1004, 3, 3, {{"Light Burger", 334, 70, 1}, {"Instant Noodles", 126, 40, 2}, {"Chips", 771, 30, 1}}, {{"Orange Juice", 460, 30, 1}, {"Mango Juice", 668, 40, 2}, {"Water", 445, 15, 1}}, 'A', 2, 305.0}, {"05/04/2025", 1005, 3, 3, {{"Cinnamon Roll", 111, 80, 1}, {"Puff Pastry", 333, 30, 2}, {"Croissant", 555, 40, 1}}, {{"Sprite", 993, 20, 1}, {"Black Tea", 441, 20, 1}, {"Mint Tea", 116, 30, 2}}, 'B', 3, 280.0}}, 5};

    // Custs[1] = {2, "pass456", "Sara Mohamed", {"01098765432", "01176543210", "01267890123"}, {{"06/04/2025", 2001, 3, 3, {{"Mini Pizza", 199, 50, 2}, {"Cheese", 123, 30, 1}, {"Cinnamon Roll", 111, 80, 1}}, {{"Latte", 503, 50, 1}, {"Americano", 551, 50, 2}, {"Mint Tea", 116, 30, 1}}, 'M', 3, 320.0}, {"07/04/2025", 2002, 3, 3, {{"Biscuits", 226, 30, 1}, {"Light Burger", 334, 70, 1}, {"Puff Pastry", 333, 30, 2}}, {{"Espresso", 221, 40, 1}, {"Green Tea", 777, 25, 2}, {"CocaCola", 557, 20, 1}}, 'A', 2, 285.0}, {"08/04/2025", 2003, 3, 3, {{"Chicken", 144, 60, 2}, {"Pan Cakes", 772, 40, 1}, {"Instant Noodles", 126, 40, 1}}, {{"Black Tea", 441, 20, 1}, {"Lemon Tea", 447, 30, 1}, {"Sprite", 993, 20, 2}}, 'B', 3, 260.0}, {"09/04/2025", 2004, 3, 3, {{"Danish Pastry", 125, 60, 1}, {"Smoked Turkey", 222, 40, 2}, {"Mini Pizza", 199, 50, 1}}, {{"Mango Juice", 668, 40, 1}, {"Water", 445, 15, 2}, {"Orange Juice", 460, 30, 1}}, 'C', 2, 285.0}, {"10/04/2025", 2005, 3, 3, {{"Chips", 771, 30, 1}, {"Croissant", 555, 40, 1}, {"Puff Pastry", 333, 30, 1}}, {{"Cappuccino", 141, 65, 1}, {"Pepsi", 661, 20, 2}, {"Black Tea", 441, 20, 1}}, 'A', 3, 245.0}}, 5};

    // Custs[2] = {3, "pass789", "Mohamed Tarek", {"0105554433", "0116665544", "0127776655"}, {{"11/04/2025", 3001, 3, 3, {{"Light Burger", 334, 70, 1}, {"Instant Noodles", 126, 40, 1}, {"Mini Pizza", 199, 50, 1}}, {{"Green Tea", 777, 25, 1}, {"Espresso", 221, 40, 2}, {"Mango Juice", 668, 40, 1}}, 'S', 2, 285.0}, {"12/04/2025", 3002, 3, 3, {{"Croissant", 555, 40, 1}, {"Danish Pastry", 125, 60, 2}, {"Cinnamon Roll", 111, 80, 1}}, {{"Pepsi", 661, 20, 1}, {"Black Tea", 441, 20, 2}, {"Americano", 551, 50, 1}}, 'C', 3, 330.0}, {"13/04/2025", 3003, 3, 3, {{"Biscuits", 226, 30, 1}, {"Puff Pastry", 333, 30, 1}, {"Chicken", 144, 60, 2}}, {{"Latte", 503, 50, 1}, {"Water", 445, 15, 2}, {"Lemon Tea", 447, 30, 1}}, 'A', 2, 250.0}, {"14/04/2025", 3004, 3, 3, {{"Smoked Turkey", 222, 40, 1}, {"Pan Cakes", 772, 40, 2}, {"Cheese", 123, 30, 1}}, {{"CocaCola", 557, 20, 1}, {"Sprite", 993, 20, 1}, {"Mint Tea", 116, 30, 1}}, 'B', 3, 265.0}, {"15/04/2025", 3005, 3, 3, {{"Chips", 771, 30, 1}, {"Mini Pizza", 199, 50, 2}, {"Croissant", 555, 40, 1}}, {{"Cappuccino", 141, 65, 1}, {"Orange Juice", 460, 30, 1}, {"Pepsi", 661, 20, 2}}, 'C', 2, 285.0}}, 5};

    // Function call
    // billing_system_customer(res, tax);

    // Hana///
    // cafeMenu(Nfood, Ndrinks); //m7dsh yfok el comment dahh aw ymsa7o ~Sarah .... Mtz3a'ish ~Abdullah

    registr();

    login();
    Reservations();
    // cout << "Billing for Reservation: " << Custs[constant].res - 1 << endl;
    billing_system_customer(Custs[constant].reservations[Custs[constant].res - 1], tax); // Call the billing system function with the reservation and tax

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

float earnings; // This will store the price the user pays for later use in the getTopEmployee function
bool shift = true; // ********** Byb2a true lma ay employee y3ml login **********
int shiftIndex = 5; // ********** El index bta3 el employee el 3amal login fel array bta3 el works (For example: works[5]) 3shan el earnings htedaf lel employee da **********

int employeeOfWeekIndex;
int employeeOfMonthIndex;
int employeeOfYearIndex;

// --Jimmy's function-- Billing System function for customers, takes a reservation from the user & the tax as parameters
void billingSystemCustomer(Reservation res, float tax) {
    cout << "Hi there! Hope you had a great time with us. Here is your bill:" << "\n\n";

    cout << setw(37) << left << "PlayStation for " + to_string(res.time) + " hours" // Time spent playing
        << setw(10) << left << to_string(int(round(res.total))) + " EGP" << "\n\n"; // PlayStation rent price

    cout << "Food & Drinks:" << "\n\n";
    cout << setw(7) << left << "QTY" // Quantity column header of the food/drink
        << setw(30) << left << "Description" // Name column header of the food/drink
        << setw(10) << left << "Price" << "\n"; // Price column header of the food/drink

    int totalFoodPrice = 0;
    // Displaying and calculating the total price of the current food using a for loop
    for (int i = 0; i < res.foodOrderCount; i++) { // Loop n times the number of the foods ordered
        cout << setw(7) << left << res.F[i].quantity // Display quantity
            << setw(30) << left << res.F[i].name // Display name
            << setw(10) << left << to_string(res.F[i].price * res.F[i].quantity) + " EGP" << "\n"; // Display and calculate price (food price * quantity)
        totalFoodPrice = totalFoodPrice + (res.F[i].price * res.F[i].quantity); // Add the current food price to the total price of foods
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

    earnings = total_price;
}

// --Jimmy's function-- Display employee of the week/month/year function, takes the employees array (works[]) & the array index of the currently logged in employee
void getTopEmployee(customer works[], int shiftIndex) {
    time_t currentTime = time(0); // Time in seconds since 1970 (El wa2t mn awl ma el function di yt3melaha run)

    if (shift) {
        works[shiftIndex].emp.weeklyEarnings += earnings; // Add weekly earnings to the currently logged in employee (Should be stored in the database file)
        works[shiftIndex].emp.monthlyEarnings += earnings; // Add monthly earnings to the currently logged in employee (Should be stored in the database file)
        works[shiftIndex].emp.yearlyEarnings += earnings; // Add yearly earnings to the currently logged in employee (Should be stored in the database file)
    }


    float weeklyMax = works[0].emp.weeklyEarnings;
    float monthlyMax = works[0].emp.monthlyEarnings;
    float yearlyMax = works[0].emp.yearlyEarnings;
    employeeOfWeekIndex = 0;
    employeeOfMonthIndex = 0;
    employeeOfYearIndex = 0;

    for (int i = 0; i < workers_num; i++) { // Loop over all employees
        // Get employee of the week
        if (works[i].emp.weeklyEarnings > weeklyMax) { // Get the employee with the most earnings the past week by their index
            weeklyMax = works[i].emp.weeklyEarnings;
            employeeOfWeekIndex = i; // Save the employee's index
        }

        // Get employee of the month
        if (works[i].emp.monthlyEarnings > monthlyMax) { // Get the employee with the most earnings the past month by their index
            monthlyMax = works[i].emp.monthlyEarnings;
            employeeOfMonthIndex = i; // Save the employee's index
        }

        // Get employee of the year
        if (works[i].emp.yearlyEarnings > yearlyMax) { // Get the employee with the most earnings the past year by their index
            yearlyMax = works[i].emp.yearlyEarnings;
            employeeOfYearIndex = i; // Save the employee's index
        }
    }

    cout << "Employee of the week: " << works[employeeOfWeekIndex].name << ", Earnings: " << weeklyMax << " EGP\n"; // Display employee of the week
    cout << "Employee of the month: " << works[employeeOfMonthIndex].name << ", Earnings: " << monthlyMax << " EGP\n"; // Display employee of the month
    cout << "Employee of the year: " << works[employeeOfYearIndex].name << ", Earnings: " << yearlyMax << " EGP\n"; // Display employee of the year


    // Check if 7 days have passed to reset the earnings
    if (difftime(currentTime, lastWeekReset) >= 7 * day_in_seconds) { // Check hal el wa2t mn awl el osbo3 l7ad dlw2ti (in seconds) = 7 ayam (in seconds)?
        for (int i = 0; i < workers_num; i++) { // Loop over all employees
            works[i].emp.weeklyEarnings = 0; // Reset all of the employees earnings by the end of this week
        }
        lastWeekReset = currentTime; // Reset the current week to start calculting new earnings from employees and display the employee of the week
    }

    // Check if 30 days have passed to reset the earnings
    if (difftime(currentTime, lastMonthReset) >= 30 * day_in_seconds) { // Check hal el wa2t mn awl el shahr l7ad dlw2ti (in seconds) = 30 yom (in seconds)?
        for (int i = 0; i < workers_num; i++) { // Loop over all employees
            works[i].emp.monthlyEarnings = 0; // Reset all of the employees earnings by the end of this month
        }
        lastMonthReset = currentTime; // Reset the current month to start calculting new earnings from employees and display the employee of the month
    }

    // Check if 365 days have passed to reset the earnings
    if (difftime(currentTime, lastYearReset) >= 365 * day_in_seconds) { // Check hal el wa2t mn awl el sana l7ad dlw2ti (in seconds) = 365 yom (in seconds)?
        for (int i = 0; i < workers_num; i++) { // Loop over all employees
            works[i].emp.yearlyEarnings = 0; // Reset all of the employees earnings by the end of this year
        }
        lastYearReset = currentTime; // Reset the current year to start calculting new earnings from employees and display the employee of the year
    }
}

void Reservations()
{
    while (true)
    {
        char snacks;
        cout << "\nWelcome at our reservation page :)\n";
        cout << "\nPlease press M for Multiplayer or S for Single   ";
        cin.get(Custs[constant].reservations[Custs[constant].res].type);
        if (cin.fail() ||
            (Custs[constant].reservations[Custs[constant].res].type != 'M' &&
                Custs[constant].reservations[Custs[constant].res].type != 'S' &&
                Custs[constant].reservations[Custs[constant].res].type != 'm' &&
                Custs[constant].reservations[Custs[constant].res].type != 's'))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n";
            continue;
        }
    GameChoice:
        cout << "What game are you going to play ? (1 = Fifa, 2 = PES, 3 = Mortal Kombat, 4 = Fortnite) ";
        cin >> Custs[constant].reservations[Custs[constant].res].game;
        if (cin.fail())
        {
            cout << "Invalid input" << endl;
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
            cout << "\nInvalid input\n";
            goto Duration;
        }
        cout << "Press Y if you need any snacks (If not press any button)  ";
        cin.ignore();
        cin.get(snacks);
        cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input, Start again\n\n";
            continue;
        }
        if (snacks == 'Y' || snacks == 'y')
            cafeMenu(Nfood, Ndrinks);
        int startTime, endTime;
    DateAndTime:
        cout << "Enter date of reservation (DD/MM/YYYY) Ex.: 02/03/2025\n";
        getline(cin, Custs[constant].reservations[Custs[constant].res].date);
        if (Custs[constant].reservations[Custs[constant].res].date[2] != '/' ||
            Custs[constant].reservations[Custs[constant].res].date[5] != '/') // Date validation
        {
            cout << "\n<<Invalid input>>\n\n";
            goto DateAndTime;
        }
        bool date_exists;
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
            cout << "\n\nInvalid input\n\n";
            goto DateAndTime;
        }
        startTime = stoi(Custs[constant].reservations[Custs[constant].res].clock.substr(0, 2));
        endTime = startTime + Custs[constant].reservations[Custs[constant].res].time;
        bool time_exists;
        for (int i = 0; i < customers_num; i++)
        {
            for (int j = 0; j < resCount; j++)
            {
                if (Custs[constant].reservations[Custs[constant].res].clock == Custs[i].reservations[j].clock)
                {
                    time_exists = true;
                }
            }
        }
        if (date_exists && time_exists)
        {
            reserved_devices++;
        }

        Custs[constant].reservations[Custs[constant].res].billNumber = bill++;
        cout << "\nYour reservation has been made successfully!\n\n";
        cout << "\nYour reservation number is: " << Custs[constant].reservations[Custs[constant].res].billNumber << endl;
        cout << "Date : "
            << Custs[constant].reservations[Custs[constant].res].date << endl;
        cout << "Time : From " << Custs[constant].reservations[Custs[constant].res].clock << " to " << endTime << ":00" << endl
            << endl;
        Custs[constant].res++;
        break;
    }
}

char ans;
void editReservation()
{
    do
    {
        cout << "press H to edit time || T to edit type || D to edit date \n";
        char choice;
        cin.get(choice);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            continue;
        }
        else if (choice == 'H' || choice == 'h') // edit time // hours
        {
            cout << "How much time will you stay (NOTE: We only deal with hours so it's currently unavailable to reserve 30 mins, 15 min, etc )";
            cin >> Custs[constant].reservations[Custs[constant].res].time;
        }
        else if (choice == 'T' || choice == 't') // edit time
        {
            while (true)
            {
                cout << "\nPlease press M for Multiplayer or S for Single";
                cin >> Custs[constant].reservations[Custs[constant].res].type;
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
                getline(cin, Custs[constant].reservations[Custs[constant].res].date);
                if (Custs[constant].reservations[Custs[constant].res].date[2] != '/' ||
                    Custs[constant].reservations[Custs[constant].res].date[5] != '/')
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
        cin.get(ans);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n";
            continue;
        }
    } while (ans == 'y' || ans == 'Y');
}

int login()
{
    int i;
    customer check;
    check.ID = -1;
    bool lamba = true;
    while (lamba) {
    tany2:
        cout << "Who are you?" << endl << "Customer = 1 , Worker = 2" << endl;
        cin >> i;
        if ((i != 1 && i != 2) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            goto tany2;
        }
        cout << "Please enter the following data:" << endl;
    stupid:
        cout << "username:";
        cin >> check.name;
        if (cin.peek() == ' ') {
            cout << "Your username can't contain spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto stupid;
        }
        cout << endl << "ID:";
        cin >> check.ID;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    stupid2:
        cout << endl << "password:";
        cin >> check.password;
        if (cin.peek() == ' ') {
            cout << "Your password can't contain spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto stupid2;
        }
        if (i == 1) {
            if (check.ID == -1 || check.ID > Custsize)
                cout << "\nInvalid id" << endl;
            else {
                if (check.name == Custs[check.ID - 1].name && check.password == Custs[check.ID - 1].password) {
                    cout << "You have logged in successfully!";
                    lamba = false;
                }
                else cout << "\nWrong Credentials!" << endl;
            }
        }
        else if (i == 2) {
            if (check.ID == -1 || check.ID > worksize)
                cout << "Invalid id" << endl;
            else {
                if (check.name == works[check.ID - 1].name && check.password == works[check.ID - 1].password) {
                    cout << "You have logged in successfully!";
                    lamba = false;
                    constant = check.ID - 1;
                }
                else cout << "Wrong Credentials!" << endl;
            }
        }
    }
    return constant;
}
void registr()
{
    int i; // Customer or worker 
    int nums; // Number of phone numbers
    string reenter_Pass; // Let the user reenter his password to check it.
CustWork:
    cout << "Who are you?" << endl << "Press 1 for Customer and 2 for worker. ";
    cin >> i;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n" << endl;
        goto CustWork;
    }
    if (i == 1)
    {
        cout << "Please enter your information: " << endl;

    Username:
        cout << "Username: ";
        cin >> Custs[custCount].name;
        if (cin.peek() == ' ') {
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
            if (cin.peek() == ' ') {
                cout << "Your phone number can't include spaces" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto PhoneNumbering;
            }
        }
    PasswordMaking:
        cout << "Please enter your password: ";
        cin >> Custs[custCount].password;
        if (cin.peek() == ' ') {
            cout << "Your password can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto PasswordMaking;
        }
        cout << "Please re-enter your password: ";
        cin >> reenter_Pass;
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
        if (cin.peek() == ' ') {
            cout << "Your username can't include spaces" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto Username2;
        }
    phoning2:
        cout << "How many phone numbers do you have? ";
        cin >> nums;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl;
            goto phoning2;
        }
        for (int i = 0; i < nums; i++)
        {
        PhoneNumbering2:
            cout << "Phone number: " << endl;
            cin >> Custs[custCount].phoneNumbers[i];
            if (cin.peek() == ' ') {
                cout << "Your phone number can't include spaces" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto PhoneNumbering2;
            }
        }
    PasswordMaking2:
        cout << "Please enter your password: ";
        cin >> Custs[custCount].password;
        if (cin.peek() == ' ') {
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
        }
        else
        {
            cout << "invalid answer please try again" << endl;
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
        }
        else
        {
            cout << "Invalid answer please try again" << endl;
            goto QuestionMaking2;
        }
    }
}
