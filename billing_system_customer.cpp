#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>

using namespace std;

int bill = 1;
int constant;

struct food {
    int code;
    string name;
    int price;
    int quantity;
};

struct drinks {
    int code;
    string name;
    int price;
    int quantity;
};

struct Reservation {
    string date;
    int billNumber;
    food F[100];
    drinks D[100];
    int foodOrderCount; // How many foods the user had ordered
    int drinksOrderCount; // How many drinks the user had ordered
    char type;
    int time; // Duration
    float total;
};

struct customer {
    long long ID;
    string password;
    string name;
    string phoneNumbers[3];
    vector<Reservation> reservations;
    int size = sizeof(reservations) / sizeof(reservations[0]); // Total number of reservations of a specific customer
}; vector <customer> Custs;


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
}




int main() {
    Reservation res;

    // Test data
    res.time = 2; // Hours spent playing
    res.total = 200; // Price of PlayStation rent (should be based on the time spent playing)

    res.foodOrderCount = 6;
    // Food test data { code, name, price, quantity }
    res.F[0] = { 0, "Kofta", 20, 2 };
    res.F[1] = { 1, "Shawarma", 50, 1 };
    res.F[2] = { 2, "Pizza", 80, 3 };
    res.F[3] = { 3, "Ta3meya", 30, 4 };
    res.F[4] = { 4, "Burger", 45, 1 };
    res.F[5] = { 5, "Fried Chicken", 60, 2 };

    res.drinksOrderCount = 5;
    // Drinks test data { code, name, price, quantity }
    res.D[0] = { 0, "Sobya", 10, 1 };
    res.D[1] = { 1, "Coca-Cola", 25, 2 };
    res.D[2] = { 2, "Fanta", 20, 3 };
    res.D[3] = { 3, "Sprite", 22, 3 };
    res.D[4] = { 4, "Water", 10, 5 };

    float tax = 14; // Tax of 14%

    // Function call
    billing_system_customer(res, tax);

    return 0;
}
