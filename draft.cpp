#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#define light 3
#define pastry 7
using namespace std;
int bill = 1;
int constant;
;

struct food
{
    string name;
    int code;
    int price;

} f[13];

struct drinks
{
    string name;
    int code;
    int price;

} d[15];

struct soft_drinks
{
    string name;
    int code;
    int price;
};
struct Reservation
{
    string date;
    int billNumber;
    vector<food> F;
    vector<drinks> D;
    char type;
    int time; // Duration
    float total;
};

struct customer
{
    long long ID;
    string password;
    string name;
    string phoneNumbers[3];
    vector<Reservation> reservations;
    int size = sizeof(reservations) / sizeof(reservations[0]); // Total number of reservations of a specific customer
};
vector<customer> Custs;
void cafeMenu(int, int);

int main()
{
    // display the title first
    cout << "\t\t\t\t\t\t The Cafe Menu\n"
         << "\t\t\t\t\t\t" << endl;

    int Nfood = 13, Ndrinks = 14;

    food f[14] = {{"Cheese", 123, 30}, {"Smoked Turky", 222, 40}, {"Chicken", 144, 60}, {"Croissant", 555, 40}, {"Puff pastry", 333, 30}, {"Danish Pastry", 125, 60}, {"Cinnamon Roll", 111, 80}, {"Biscuits or Cookies", 226, 30}, {"Chips or Snacks", 771, 30}, {"Instant Noodless", 126, 40}, {"Mini Pizza", 199, 50}, {"Pan Cakes", 772, 40}, {"Light Burger", 334, 70}};
    drinks d[15] = {{"Pepsi", 661, 20}, {"Cocacola", 557, 20}, {"Sprite", 993, 20}, {"Black Tea", 441, 20}, {"Green Tea", 777, 25}, {"Mint Tea", 116, 30}, {"Lemon Tea", 447, 30}, {"Espresso", 221, 40}, {"Amreicano", 551, 50}, {"Cappiccino", 141, 650}, {"Latte", 503, 50}, {"Orange Juice", 460, 30}, {"Mango Juice", 668, 40}, {"Strawberry Juice", 334, 40}, {"Bottelet Water", 445, 15}};
    cafeMenu(Nfood, Ndrinks);
}

void cafeMenu(int Nf, int Nd)
{
    // for (int i = 0; i < Nf; i++)
    //{
    //     //Entring the database
    //     cout << "Enter the product name: ";
    //     getline(cin, f[i].name);
    //     cout << "Enter the product code: ";
    //     cin >> f[i].code;
    //     cin.ignore();
    //     cout << "Enter the product price: ";
    //     cin >> f[i].price;
    //     cin.ignore();
    // }
    ////Entring the database
    // for (int i = 0; i < Nd; i++)
    //{
    //     cout << "Enter the product name: ";
    //     getline(cin, d[i].name);
    //     cout << "Enter the product code: ";
    //     cin >> d[i].code;
    //     cin.ignore();
    //     cout << "Enter the product price: ";
    //     cin >> d[i].price;
    //     cin.ignore();
    // }

    int type, code, Totalcost, quantity;
    char ans;
    // Step 1 on displaying the food menu
    food f[14] = {{"Cheese", 123, 30}, {"Smoked Turky", 222, 40}, {"Chicken", 144, 60}, {"Croissant", 555, 40}, {"Puff pastry", 333, 30}, {"Danish Pastry", 125, 60}, {"Cinnamon Roll", 111, 80}, {"Biscuits or Cookies", 226, 30}, {"Chips or Snacks", 771, 30}, {"Instant Noodless", 126, 40}, {"Mini Pizza", 199, 50}, {"Pan Cakes", 772, 40}, {"Light Burger", 312, 70}};
    drinks d[15] = {{"Pepsi", 661, 20}, {"Cocacola", 557, 20}, {"Sprite", 993, 20}, {"Black Tea", 441, 20}, {"Green Tea", 777, 25}, {"Mint Tea", 116, 30}, {"Lemon Tea", 447, 30}, {"Espresso", 221, 40}, {"Amreicano", 551, 50}, {"Cappiccino", 141, 650}, {"Latte", 503, 50}, {"Orange Juice", 460, 30}, {"Mango Juice", 668, 40}, {"Strawberry Juice", 334, 40}, {"Bottelet Water", 445, 15}};
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
        cout << "\nDrinks menu" << "\n " << "************" << endl;
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
    Totalcost = 0;

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
        for (int i = 0; i < Nf; i++)
        {
            if (code == f[i].code)
            {
                Totalcost += (f[i].price * quantity);
                break;
            }
            else
            {
                for (int i = 0; i < Nd; i++)
                {
                    if (code == d[i].code)
                    {
                        Totalcost += (d[i].price * quantity);
                        break;
                    }
                }
            }
            break;
        }
        cout << "Would you like to add another product to your cart?" << endl;
        cout << " If yes enter y\n"
             << " If no enter n\n";
        cin >> ans;
        cin.ignore();

    } while (ans == 'y' || ans == 'Y');
    cout << "Your Total cost is: " << Totalcost << endl;
    cout << "Enjoy your meal!^_^" << endl;
    ;
}