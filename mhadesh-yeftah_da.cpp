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
        if (substractednumber > 10)
        {
            for (int i = 0; startNumber < 5000; i++)
            {
                for (int i = 0; i < 5; i++)
                {
                    startNumber += substractednumber;
                    cout << startNumber << "  ";
                }
                cout << endl
                     << endl;
            }
        }
        else
        {
            for (int i = 0; startNumber < 1000; i++)
            {
                for (int i = 0; i < 5; i++)
                {
                    startNumber += substractednumber;
                    cout << startNumber << "  ";
                }
                cout << endl
                     << endl;
            }
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
                for (int i = 0; i < 5; i++)
                {
                    startNumber -= substractednumber;
                    cout << startNumber << "  ";
                }
                cout << endl
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