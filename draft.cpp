#include <bits/stdc++.h>

using namespace std;



int bill = 1;
int constant;
int Custsize=1;
int worksize=1;
struct food {
    int code;
    string name;
    int price;
};

struct drinks {
    int code;
    string name;
    int price;
};

struct Reservation {
    string date;
    int billNumber;
    vector<food> F;
    vector<drinks> D;
    char type;
    int time; //Duration
    float total;
};
struct security {
    int no;
    string ans;
};
struct customer {
    long long ID;
    string password;
    string name;
    string phoneNumbers[3];
    security question;
    vector<Reservation> reservations;
    int size = sizeof(reservations) / sizeof(reservations[0]); //Total number of reservations of a specific customer
}; customer Custs[1000],works[1000];
customer un, pw, id, pn;


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
         if(cin.peek()==' '){
            cout<<"Your username can't contain spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
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
        if(cin.peek()==' '){
            cout<<"Your password can't contain spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
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
                else cout << "\nWrong Credentials!"<<endl;
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
                else cout << "Wrong Credentials!"<<endl;
            }
        }
    }
    return constant;
}
void registr()
{
    int i,q;
tany:
    cout << "Who are you?" << endl << "Customer = 1 , Worker = 2" << endl;
    cin >> i;
    if ((i != 1 && i != 2) || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        goto tany;
    }
    if (i == 1) {ghaby:
        customer newCustomer;
        cout << "enter username: ";
        cin >> newCustomer.name;
        if(cin.peek()==' '){
            cout<<"Your username can't include spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby;
        }
                ghaby3:
        cout << endl << "enter password: ";
        cin >> newCustomer.password;
        if(cin.peek()==' '){
            cout<<"Your password can't include spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby3;
        }
        //cout << endl << "enter phone number: ";
        // Use index 0 instead of 3
        //cin >> newCustomer.phoneNumbers[0];
        tany1:
        cout << "Choose a question (This question will be used when you reset your password)" << endl << "First Pet Name?=1" << endl << "First Love Name?=2" << endl << "Fav Color?=3" << endl;
        cin >> q;
        if ((q != 1 && q != 2 && q != 3) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input\n\n"
            goto tany1;
        }
        // Assign ID as current size (assuming no deletions)
        
        newCustomer.ID = Custsize;
        Custs[newCustomer.ID-1]=newCustomer;
        Custs[newCustomer.ID-1].question.no = q;
        ghaby6:
        cout << "Answer Please"<<endl;
        cin >> Custs[newCustomer.ID-1].question.ans;
        if(cin.peek()==' '){
            cout<<"Your answer can't include spaces "<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby6;
        }
        cout << "your id is: " << newCustomer.ID << endl;
          Custsize++;
    }
    else if (i == 2) {ghaby2:
        customer newWork;
        cout << "enter username: ";
        cin >> newWork.name;
        if(cin.peek()==' '){
            cout<<"Your username can't include spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby2;
        }ghaby4:
        cout << endl << "enter password: ";
        cin >> newWork.password;
        if(cin.peek()==' '){
            cout<<"Your password can't include spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby4;
        }
        //cout << endl << "enter phone number: ";
        // Use index 0 instead of 3
        //cin >> newCustomer.phoneNumbers[0];
        tany3:
        cout << "Choose a question" << endl << "First Pet Name?=1" << endl << "First Love Name?=2" << endl << "Fav Color?=3" << endl;
        cin >> q;
        if ((q != 1 && q != 2 && q != 3) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            goto tany3;
        }
        
        // Assign ID as current size (assuming no deletions)
        newWork.ID = worksize;
        works[newWork.ID-1]=newWork;
        works[newWork.ID-1].question.no = q;
        ghaby5:
        cout << "Answer Please"<<endl;
        cin >> works[newWork.ID-1].question.ans;
if(cin.peek()==' '){
            cout<<"Your answer can't include spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby5;
        }
        cout << "your id is: " << newWork.ID << endl;
            worksize++;
    }

}

void forgot()
{int i,q;customer check;
check.ID=-1;
tany4:
    cout << "Who are you?" << endl << "Customer = 1 , Worker = 2" << endl;
    cin >> i;
    if ((i != 1 && i != 2) || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        goto tany4;
    }
    if(i==1){
    tany5:
    cout<<"Please Enter Your ID:"<<endl;
    cin>>check.ID;
    if (check.ID == -1 || check.ID > Custsize){
                cout << "invalid id" << endl;
                goto tany5;}
        if(Custs[check.ID-1].question.no==1){
            cout<<"First Pet Name?"<<endl;
        }
        else if(Custs[check.ID-1].question.no==2){
            cout<<"First Love Name?"<<endl;
        }
        else if(Custs[check.ID-1].question.no==3){
            cout<<"Fav Color?"<<endl;
        }
        cout << "Answer Please"<<endl;
        cin>>check.question.ans;
        if(check.question.ans==Custs[check.ID-1].question.ans){
            ghaby8:
            cout<<"Write New Password!"<<endl;
            cin>>Custs[check.ID-1].password;
            if(cin.peek()==' '){
            cout<<"Your password can't include spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby8;
        }
        }
        else {
        cout<<"invalid answer please try again"<<endl;
            goto tany5;
        }
    }
                else if (i==2){
                    tany6:
    cout<<"Please Enter Your ID:"<<endl;
    cin>>check.ID;
    if (check.ID == -1 || check.ID > worksize){
                cout << "invalid id" << endl;
                goto tany6;}
                if(works[check.ID-1].question.no==1){
            cout<<"First Pet Name?"<<endl;
        }
        else if(works[check.ID-1].question.no==2){
            cout<<"First Love Name?"<<endl;
        }
        else if(works[check.ID-1].question.no==3){
            cout<<"Fav Color?"<<endl;
        }
        cout << "Answer Please"<<endl;
        cin>>check.question.ans;
        if(check.question.ans==works[check.ID-1].question.ans){
            ghaby7:
            cout<<"Write New Password!"<<endl;
            cin>>works[check.ID-1].password;
            if(cin.peek()==' '){
            cout<<"Your password can't include spaces"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            goto ghaby7;
        }
        }
        else {
        cout<<"invalid answer please try again"<<endl;
            goto tany6;
        }
                }

}





int main()
{
    int pick;
    long long index = 0;
    tany:
    cout << "WELCOME" << endl << "1:login" << endl << "2:register" << endl << "3:forgot password" << endl << "4:exit" << endl;
    cin >> pick;

    if (pick == 1)
    {
         login();

    }
    else if (pick == 2)
    {
       registr();
       goto tany;

    }
    else if (pick == 3)
    {
         forgot();
         goto tany;
    }
    else
        cout << "thank you for visiting!";


    return 0;

}