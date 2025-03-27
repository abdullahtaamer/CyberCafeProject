#include <iostream>
#include <string>
#include <vector>
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
    vector<food> F;
    vector<drinks> D;
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
    for (int i = 0; i < res.F.size(); i++) { // Loop n times the number of the food array size
        cout << setw(7) << left << res.F[i].quantity // Display quantity
             << setw(30) << left << res.F[i].name // Display name
             << setw(10) << left << to_string(res.F[i].price * res.F[i].quantity) + " EGP" << "\n"; // Display and calculate price (food price * quantity)
        totalFoodPrice = totalFoodPrice + (res.F[i].price * res.F[i].quantity); // Add the current food price to the total price of foods
    }

    int totalDrinksPrice = 0;
    // Displaying and calculating the total price of the current drink using a for loop
    for (int j = 0; j < res.D.size(); j++) { // Loop n times the number of the drinks array size
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
    // Test data
    Reservation res;

    res.time = 2; // Hours spent playing
    res.total = 200; // Price of PlayStation rent (should be based on the time spent playing)

    // Food test data (code, name, price, quntity)
    res.F.push_back({ 0, "Kofta", 20, 2 });
    res.F.push_back({ 1, "Shawarma", 50, 1 });
    res.F.push_back({ 2, "Pizza", 80, 3 });
    res.F.push_back({ 3, "Ta3meya", 30, 4 });
    res.F.push_back({ 4, "Burger", 45, 1 });
    res.F.push_back({ 5, "Fried Chicken", 60, 2 });

    // Drinks test data (code, name, price, quntity)
    res.D.push_back({ 0, "Sobya", 10, 1 });
    res.D.push_back({ 1, "Coca-Cola", 25, 2 });
    res.D.push_back({ 2, "Fanta", 20, 3 });
    res.D.push_back({ 3, "Sprite", 22, 3 });
    res.D.push_back({ 4, "Water", 10, 5 });

    float tax = 14; // Tax of 14%

    // Function call
    billing_system_customer(res, tax);

    return 0;

    /* ----------NOTE----------
    
        res.F.push_back({ 0, "Kofta", 20, 2 });

        heya heya

        res.F[0].code = 0; -----------
        res.F[0].name = "Kofta";     | ------> el fekra en bel taree2a di hdtar eni a7aded 3adad arrays mo3ayan lel food/drinks fel struct bta3 el Reservation
        res.F[0].price = 20;         | ------> ya3ni fe struct el Reservation hnetar n3ml kda msalan: food F[10]; drinks D[10]; badal vector<food> F; vector<drinks> D;
        res.F[0].quantity = 2; -------         ama el push_back msh bne7tag enena n7aded 3dad arrays mo3ayan
    
    */
}
