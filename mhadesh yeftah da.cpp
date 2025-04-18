// I SAID MAHADESH YEFTAHOOOOOOO WHAT'S WRONG WITH YOU ???!!!

#include <iostream>
using namespace std;
int main()
{
start:
    int startNumber, substractednumber;
    char ans;
    cout << "Press A for add and S for substraction ";
    cin >> ans;
    if (ans == 'a' || ans == 'A')
    {
        cout << "Please enter the start number : ";
        cin >> startNumber;
        cout << "Please enter the added number : ";
        cin >> substractednumber;
        for (int i = 0; startNumber < 1000; i++)
        {
            startNumber += substractednumber;
            cout << startNumber << endl
                 << endl;
        }
    }
    else
    {
        cout << "Please enter the start number : ";
        cin >> startNumber;
        cout << "Please enter the substracted number : ";
        cin >> substractednumber;
        for (int i = 0; startNumber > 0; i++)
        {
            startNumber -= substractednumber;
            cout << startNumber << endl
            << endl;
        }
    }
        cout << "Press Y if you want to continue. ";
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
        {
            goto start;
        }
        
    system("pause");
}