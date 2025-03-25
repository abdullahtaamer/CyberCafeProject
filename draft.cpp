#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#define light 3
#define pastry 7
using namespace std;
int bill = 1;
int constant;
struct light_sandwiches {
    string name;
    int code;
    int price;
};

struct food {
    string name;
    int code;
    int price;
    string type;
}f[30];


struct drinks {
    string name;
    int code;
    int price;
    string type;
}d[30];

//struct soft_drinks {
//    string name;
//    int code; jmkbnjfknvsgjnkl
//    int price;
//};
struct Reservation {
    string date;
    int billNumber;
    vector<food> F;
    vector<drinks> D;
    char type;
    int time; //Duration
    float total;
};

struct customer {
    long long ID;
    string password;
    string name;
    string phoneNumbers[3];
    vector<Reservation> reservations;
    int size = sizeof(reservations) / sizeof(reservations[0]); //Total number of reservations of a specific customer
};vector <customer> Custs;
void cafeMenu(int,int);

int main()
{
    //display the title first
    cout << "\t\t\t\t\t\t The Cafe Menu\n" << "\t\t\t\t\t\t*" << endl;

    int Nfood,Ndrinks;
    cout << "Enter the number of products" << "\t\t\t\t\t\t\t\t\t\t\t\t\t**\n";
    cout << "food count : ";
    cin >> Nfood; cout << "\n";
    cout << "drinks count : ";
    cin >> Ndrinks;
    cout << endl;
    cin.ignore();
    cafeMenu(Nfood,Ndrinks);
  
}

void cafeMenu(int Nf,int Nd)
{
    int type, answer, code, Totalcost , quantity;
    char ans;
    for (int i = 0; i < Nf; i++)
    {
        //Entring the database
        cout << "Enter the product name: ";
        getline(cin, f[i].name);
        cout << "Enter the product code: ";
        cin >> f[i].code;
        cin.ignore();
        cout << "Enter the product price: ";
        cin >> f[i].price;
        cin.ignore();
    }
    //Step 1 on displaying the food menu
    cout << "Food menu" << "" << endl;
        cout << "If you want light sandwich press 1"<<endl;
        cout << "If you want Pastry press 2"<<endl;
        cout << "if you want other options press 3" << endl;
        cin >> type;
        cin.ignore();
        if (type == 1)
        {
            for (int i = 0; i < light; i++)
            {
                cout << f[i].name << "\t\t\t";
                cout << f[i].code << "\t\t\t";
                cout << f[i].price << "\t\t\t";
            }
        }
        else  if (type == 2)
        {
            for (int i = light; i < pastry; i++)
            {
                cout << f[i].name << "\t\t\t";
                cout << f[i].code << "\t\t\t";
                cout << f[i].price << "\t\t\t";
            }
        }
        else
        {
            for (int i = 7; i < Nf; i++)
            {
                cout << f[i].name << "\t\t\t";
                cout << f[i].code << "\t\t\t";
                cout << f[i].price << "\t\t\t";
            }

        }
        //Entring the database
        for (int i = 0; i < Nd; i++)
        {
            cout << "Enter the product name: ";
            getline(cin, d[i].name);
            cout << "Enter the product code: ";
            cin >> d[i].code;
            cin.ignore();
            cout << "Enter the product price: ";
            cin >> d[i].price;
            cin.ignore();
        }
        

        //displaying thye menun of drinks
        cout << "Drinks menu" << "" << endl;
        cout << "If you want Soft Drinks press 1" << endl;
        cout << "If you want Tea press 2" << endl;
        cout << "if you want Coffee press 3" << endl;
        cout << "If you want Fresh Juices press 4" << endl;
        cout << "If you want Botteled Water press 5" << endl;
        
        cin >> answer;
        cin.ignore();
        
        if (answer == 1)
        {
            for (int i = 0; i < light; i++)
            {
                cout << d[i].name << "\t\t\t";
                cout << d[i].code << "\t\t\t";
                cout << d[i].price << "\t\t\t";
            }

        }
        else if (answer ==2)
        {
            for (int i = 3; i < pastry; i++)
            {
                cout << d[i].name << "\t\t\t";
                cout << d[i].code << "\t\t\t";
                cout << d[i].price << "\t\t\t";
            }

        }
        else if (answer == 3)
        {
            for (int i = pastry; i < 11; i++)
            {
                cout << d[i].name << "\t\t\t";
                cout << d[i].code << "\t\t\t";
                cout << d[i].price << "\t\t\t";
            }

        }
        else if (answer == 4)
        {
            for (int i = 11; i < Nd; i++)
            {
                cout << d[i].name << "\t\t\t";
                cout << d[i].code << "\t\t\t";
                cout << d[i].price << "\t\t\t";
            }

        }
        else 
        {
            for (int i = 14; i <= Nd; i++)
            {
                cout << d[i].name << "\t\t\t";
                cout << d[i].code << "\t\t\t";
                cout << d[i].price << "\t\t\t";
            }

        }
        do {
            cout << "Please Enter the code of the product you want" << endl;
            cin >> code;
            cin.ignore();
            cout << "Please Enter the quantity of this product you want" << endl;
            cin >> quantity;
            cin.ignore();
            for (int i = 0; i < Nf; i++)
            {
                if (code == f[i].code) {
                    Totalcost += Totalcost + (f[i].price * quantity);
                    break;
                }
                else
                {
                    for (int i = 0; i < Nd; i++)
                    {
                        if (code == d[i].code)
                            Totalcost += Totalcost + (d[i].price * quantity);

                        break;
                    }
                     
                }break;
            }
            cout << "Would you like to add another product to your cart?" << endl;
            cout << " If yes enter y\n" << "If no enter n\n";
            cin >> ans;
            cin.ignore();






        } while (ans == 'y' || ans == 'Y');
        cout << "Your Total cost is:" << Totalcost << endl;
        cout << "Enjoy your meal!^_^" << endl;;
}