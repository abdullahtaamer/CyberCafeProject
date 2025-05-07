#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <limits>
using namespace std;

const int SIZE = 5, N = 10, Max_Exercise = 10, NUM_TRAINERS = 10; // review later N of clients will increase 

struct Measurements {
    float weight[SIZE];
    float height[SIZE];
    float bmi[SIZE];
    int count = 0;    // Keep track of the number of measurements
};

struct Workout {
    string workoutID, workoutName, exercises[SIZE];
    int duration, exerciseCount = 0;
};

struct Client {
    string clientId, cUsername, cPassword;
    Workout workoutplans[SIZE];
    float progresslogs[SIZE];
    Measurements measure;
};

struct Trainer {
    string TrainerID, tUsername, tPassword;
    Client client[N];
};

// Global arrays for Clients and Trainers
Client clients[N * NUM_TRAINERS];
Trainer trainers[N];
int nextClientID = 1; // ID for clients
int nextTrainerID = 101; // ID for trainers
int clientCount = 0;
int trainerCount = 0;

const string CLIENT_FILE = "clients.txt";
const string TRAINER_FILE = "trainers.txt";

void mainMenu() {
    cout << "1. Register as Client\n";
    cout << "2. Register as Trainer\n";
    cout << "3. Login\n";
    cout << "0. Logout from our application\n";
}

void readPassword(string& password, char& pass) {
    password.clear();
    do {
        pass = _getch();
        if (pass == 13) {
            break;
        }
        else if (pass == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password += pass;
            cout << "*";
        }
    } while (true);
    cout << endl;
}

bool isUsernameTaken(char choiceOfRegister, const string& userName) {
    if (choiceOfRegister == 'c' || choiceOfRegister == 'C') {
        for (int i = 0; i < clientCount; i++) {
            if (clients[i].cUsername == userName) {
                return true;
            }
        }
    }
    else if (choiceOfRegister == 't' || choiceOfRegister == 'T') {
        for (int i = 0; i < trainerCount; i++) {
            if (trainers[i].tUsername == userName) {
                return true;
            }
        }
    }
    return false;
}
void loadData() {
    ifstream clientFile("clients.txt");
    ifstream trainerFile("trainers.txt");
    int maxClientID = 0, maxTrainerID = 0;
    if (clientFile.is_open()) {
        while (clientFile >> clients[clientCount].clientId >> clients[clientCount].cUsername >> clients[clientCount].cPassword) {
            int currentID = stoi(clients[clientCount].clientId);
            if (currentID >= maxClientID) {
                maxClientID = currentID + 1;
            }
            clientCount++;
        }
        clientFile.close();
    }

    // Assign clients to trainers 
    int clientIndex = 0;
    for (int i = 0; i < NUM_TRAINERS; ++i) {
        for (int j = 0; j < N && clientIndex < clientCount; ++j) {
            trainers[i].client[j] = clients[clientIndex];
            clientIndex++;
        }
    }

    if (trainerFile.is_open()) {
        while (trainerFile >> trainers[trainerCount].TrainerID >> trainers[trainerCount].tUsername >> trainers[trainerCount].tPassword) {
            int currentID = stoi(trainers[trainerCount].TrainerID);
            if (currentID >= maxTrainerID) {
                maxTrainerID = currentID + 1;
            }
            trainerCount++;
        }
        trainerFile.close();
    }

    nextClientID = maxClientID > nextClientID ? maxClientID : nextClientID;
    nextTrainerID = maxTrainerID > nextTrainerID ? maxTrainerID : nextTrainerID;
}

// Initialized workouts as they aren't in a file
Workout workouts[SIZE] = {
{"W001", "Full Body Blast", {"Squats", "Push-ups", "Pull-ups", "Plank", "Lunges"}, 60, 5 },
{ "W002", "Cardio Power", {"Running", "Jumping Jacks", "Burpees", "Mountain Climbers"}, 45, 4 },
{ "W003", "Strength Focus", {"Bench Press", "Deadlifts", "Overhead Press", "Rows"}, 75, 4 },
{ "W004", "Leg Day",  {"Squats", "Lunges", "Leg Press", "Calf Raises"}, 55, 4 },
{ "W005", "Core Circuit", {"Crunches", "Leg Raises", "Russian Twists", "Plank"}, 30, 4 }
};

int workoutCount = 5;


// Function to find if the username is unique

Client* findClient(const string& id) {
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].clientId == id) {
            return &clients[i]; // Client found
        }
    }
    return nullptr; // Client not found
}

Trainer* findTrainerById(const string& id) {
    for (int i = 0; i < trainerCount; i++) {
        if (trainers[i].TrainerID == id) {
            return &trainers[i]; // Trainer found
        }
    }
    return nullptr; // Trainer not found
}


//Fatma

void registerClient() {
    char choiceOfRegister = 'c';
    if (clientCount >= N * NUM_TRAINERS) {
        cout << "Maximum number of clients reached.\n";
        return;
    }

    Client& newClient = clients[clientCount];
    newClient.clientId = to_string(nextClientID);

    cout << "\n--- Register as Client ---" << endl;

    do {
        cout << "Username: ";
        cin >> newClient.cUsername;
        if (newClient.cUsername.empty()) {
            cout << "Error: Username cannot be empty. Please try again.\n";
            continue;
        }
        if (isUsernameTaken(choiceOfRegister, newClient.cUsername)) {
            cout << "This username is taken. Choose another one.\n\n";
        }
        else {
            break;
        }
    } while (true);

    cout << "Password: ";
    char pass;
    readPassword(newClient.cPassword, pass);
    if (newClient.cPassword.empty()) {
        cout << "Error: Password cannot be empty. Registration failed.\n";
        return;
    }

    ofstream clientFile(CLIENT_FILE, ios::app);
    if (clientFile.is_open()) {
        clientFile << newClient.clientId << '\n' << newClient.cUsername << '\n' << newClient.cPassword << endl;
        clientFile.close();
        cout << "Client registered successfully! now you can proceed and login\n";
        cout << "Your ID is: " << nextClientID << "\n\n";
        int trainerIndex = clientCount / N; // Determine which trainer to assign to
        if (trainerIndex < NUM_TRAINERS) {
            int clientSlot = clientCount % N; // Determine the next available slot for that trainer
            trainers[trainerIndex].client[clientSlot] = newClient;

        }

        clients[clientCount].clientId = to_string(nextClientID++);
        clientCount++;
    }
    else {
        cerr << "Error: Unable to open client file for writing." << endl;
    }
}

void registerTrainer() {
    char choiceOfRegister = 't';
    if (trainerCount >= N) {
        cout << "Maximum number of trainers reached.\n";
        return;
    }

    Trainer& newTrainer = trainers[trainerCount];
    newTrainer.TrainerID = to_string(nextTrainerID);
    char pass;

    cout << "\n--- Register as Trainer ---" << endl;

    do {
        cout << "Username: ";
        cin >> newTrainer.tUsername;
        if (newTrainer.tUsername.empty()) {
            cout << "Error: Username cannot be empty. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (isUsernameTaken(choiceOfRegister, newTrainer.tUsername)) {
            cout << "This username is taken. Choose another one.\n\n";
        }
        else {
            break;
        }
    } while (true);

    cout << "Password: ";
    readPassword(newTrainer.tPassword, pass);
    if (newTrainer.tPassword.empty()) {
        cout << "Error: Password cannot be empty. Registration failed.\n";
        return;
    }

    ofstream trainerFile(TRAINER_FILE, ios::app);
    if (trainerFile.is_open()) {
        trainerFile << newTrainer.TrainerID << '\n' << newTrainer.tUsername << '\n' << newTrainer.tPassword << endl;
        trainerFile.close();
        cout << "Trainer registered successfully! now you can proceed to login\n";
        cout << "Your ID is: " << nextTrainerID << "\n\n";
        trainers[trainerCount].TrainerID = to_string(nextTrainerID++);
        trainerCount++;
    }
    else {
        cerr << "Error: Unable to open trainer file for writing." << endl;
    }
}

Client* loggedInClient = nullptr;
Trainer* loggedInTrainer = nullptr;
string loggedInUserType = "";

string loginUser() {
    string username, password;
    string storedUsername, storedPassword;
    char pass;

    cout << "\n--- Login ---" << endl;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    readPassword(password, pass);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].cUsername == username && clients[i].cPassword == password) {
            cout << "Logged in successfully as a Client!\n";
            loggedInClient = &clients[i];
            loggedInUserType = "client";
            return "client";
        }
    }
    for (int i = 0; i < trainerCount; i++) {
        if (trainers[i].tUsername == username && trainers[i].tPassword == password) {
            cout << "Logged in successfully as a Trainer!\n";
            loggedInTrainer = &trainers[i];
            loggedInUserType = "trainer";
            return "trainer";
        }
    }

    cout << "\nLogin failed. Invalid username or password.\n\n";
    return "";
}


//Kariman Functions

void deleteWorkout() {
    string id;
    cout << "Enter workout ID to delete: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < workoutCount; ++i) {
        if (workouts[i].workoutID == id) {
            char confirm;//Confirm deletion
            cout << "Are you sure you want to delete workout \"" << workouts[i].workoutName << "\"? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                //  to delete from global workouts array
                for (int j = i; j < workoutCount - 1; ++j) {
                    workouts[j] = workouts[j + 1];
                }
                workoutCount--;
                found = true;
                cout << "Workout deleted successfully.\n";

                // to remove from clients' workout plans
                for (int t = 0; t < NUM_TRAINERS; ++t) {
                    for (int c = 0; c < N; ++c) {
                        for (int w = 0; w < SIZE; ++w) {
                            if (trainers[t].client[c].workoutplans[w].workoutID == id) {
                                trainers[t].client[c].workoutplans[w] = Workout(); // Clear the workout
                            }
                        }
                    }
                }

                //  to remove from the global clients array
                for (int c = 0; c < clientCount; ++c) {
                    for (int w = 0; w < SIZE; ++w) {
                        if (clients[c].workoutplans[w].workoutID == id) {
                            clients[c].workoutplans[w] = Workout();
                        }
                    }
                }
            }
            else {
                cout << "Deletion cancelled.\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "Workout not found.\n";
    }
}

void editWorkout() {
    string id;
    cout << "Enter workout ID to edit: ";
    cin >> id;
    cout << endl;

    for (int i = 0; i < workoutCount; i++) {
        if (workouts[i].workoutID == id) {
            cout << "Editing workout:" << workouts[i].workoutName << endl;

            cout << "Enter new workout name: ";
            cin.ignore();
            getline(cin, workouts[i].workoutName);

            // exerciseCount must be an integer
            while (true) {
                cout << "Enter new number of exercises: ";
                if (cin >> workouts[i].exerciseCount) {
                    // Check if  integer and within range
                    if (cin.peek() == '\n' && workouts[i].exerciseCount > 0 &&
                        workouts[i].exerciseCount <= SIZE) {
                        break; // Valid input, exit the loop
                    }
                    else {
                        cout << "Invalid input, Please enter a positive integer less than or equal to "
                            << SIZE << ".\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                else {
                    cout << "Invalid input, Please enter an integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            cin.ignore(); // Consume the newline character

            for (int j = 0; j < workouts[i].exerciseCount; j++) {
                cout << "Exercise name " << (j + 1) << ": ";
                getline(cin, workouts[i].exercises[j]);
            }

            // Validate duration (must be an integer)
            while (true) {
                cout << "Enter new duration: ";
                if (cin >> workouts[i].duration) {
                    // Check if it's an integer AND positive
                    if (cin.peek() == '\n' && workouts[i].duration > 0) {
                        break; // Valid input
                    }
                    else {
                        cout << "Invalid input, Please enter a positive integer for duration.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                else {
                    cout << "Invalid input, Please enter an integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            // Update workout in clients' plans
            for (int t = 0; t < NUM_TRAINERS; ++t) {
                for (int c = 0; c < N; ++c) {
                    for (int w = 0; w < SIZE; ++w) {
                        if (trainers[t].client[c].workoutplans[w].workoutID == id) {
                            trainers[t].client[c].workoutplans[w] = workouts[i];
                        }
                    }
                }
            }

            for (int c = 0; c < clientCount; ++c) {
                for (int w = 0; w < SIZE; ++w) {
                    if (clients[c].workoutplans[w].workoutID == id) {
                        clients[c].workoutplans[w] = workouts[i];
                    }
                }
            }

            cout << "Workout done!\n\n";
            return;
        }
    }
    cout << "Workout not found\n";
    cout << "----------------------------------------\n\n";
}

void listAllWorkouts() {
    if (workoutCount == 0) {
        cout << "No workouts available.\n";
        return;
    }
    for (int i = 0; i < workoutCount; i++) {
        cout << "\nworkout ID :" << workouts[i].workoutID << endl;
        cout << "workout name :" << workouts[i].workoutName << endl;
        cout << "Exercises:\n";
        for (int j = 0; j < workouts[i].exerciseCount; ++j) {
            cout << "  - " << workouts[i].exercises[j] << endl;
        }
        cout << "duration in minutes:" << workouts[i].duration << endl;
        cout << "------------------------\n\n";
    }
}


//_________________________

void assignWorkoutToClient(Trainer currentTrainer[NUM_TRAINERS]) {
    string answer = "y";

    do {
        string ClientID, workID;
        bool CIDFOUND = false, WIDFOUND = false;
        Workout* workoutToAssignPtr = nullptr;
        Client* clientPtr = nullptr;

        // Find the client
        cout << "Enter The Client's ID: ";
        cin >> ClientID;

        for (int i = 0; i < NUM_TRAINERS && !CIDFOUND; i++) {
            for (int j = 0; j < N && !CIDFOUND; j++) {
                if (currentTrainer[i].client[j].clientId == ClientID) {
                    clientPtr = &currentTrainer[i].client[j];
                    CIDFOUND = true;
                }
            }
        }

        if (!CIDFOUND) {
            cout << "Invalid Client ID! Please try again.\n\n";
            continue;
        }

        // Find the workout
        cout << "Enter The Workout's ID: ";
        cin >> workID;

        for (int i = 0; i < workoutCount; i++) {
            if (workouts[i].workoutID == workID) {
                workoutToAssignPtr = &workouts[i];
                WIDFOUND = true;
                break;
            }
        }

        if (!WIDFOUND) {
            cout << "Invalid Workout ID! Please try again.\n\n";
            continue;
        }

        // Check if workout is already assigned
        bool alreadyAssigned = false;
        for (int i = 0; i < SIZE; i++) {
            if (clientPtr->workoutplans[i].workoutID == workID) {
                alreadyAssigned = true;
                break;
            }
        }

        if (alreadyAssigned) {
            cout << "This workout is already assigned to this Client.\n\n";
        }
        else {
            // Assign the workout to trainer's copy
            bool assigned = false;
            for (int i = 0; i < SIZE; i++) {
                if (clientPtr->workoutplans[i].workoutID == "") {
                    clientPtr->workoutplans[i] = *workoutToAssignPtr;
                    assigned = true;
                    cout << "Workout \"" << workoutToAssignPtr->workoutName
                        << "\" added to Client: " << ClientID << " successfully!\n\n";

                    // Assign the workout to the global clients[] array too
                    for (int k = 0; k < clientCount; ++k) {
                        if (clients[k].clientId == ClientID) {
                            for (int m = 0; m < SIZE; m++) {
                                if (clients[k].workoutplans[m].workoutID == "") {
                                    clients[k].workoutplans[m] = *workoutToAssignPtr;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    break;
                }
            }

            if (!assigned) {
                cout << "No available workout plan slots for Client: " << ClientID << ".\n\n";
            }
        }

        // Ask to assign another workout
        cout << "Do you want to add another workout? (Y/N)\n";
        cout << "Enter your answer: ";
        cin >> answer;
        cout << endl;

        while (answer != "Y" && answer != "y" && answer != "N" && answer != "n") {
            cout << "Invalid input! Please enter 'Y' or 'N': ";
            cin >> answer;
            cout << endl;
        }

    } while (answer == "Y" || answer == "y");
}

void unassignWorkoutFromClient(Trainer currentTrainer[NUM_TRAINERS]) {
    string answer;

    do {
        string ClientID;
        string workID;
        bool CIDFOUND = false;
        bool WIDFOUND = false;
        bool isWorkoutIDValid = false;

        // Find client ID
        do {
            cout << "Please enter the Client ID: ";
            cin >> ClientID;

            for (int i = 0; i < NUM_TRAINERS && !CIDFOUND; i++) {
                for (int j = 0; j < N && !CIDFOUND; j++) {
                    if (currentTrainer[i].client[j].clientId == ClientID) {
                        CIDFOUND = true;
                    }
                }
            }

            if (!CIDFOUND) {
                cout << "Client ID not found. Please try again.\n";
            }
        } while (!CIDFOUND);

        //  Validate workout ID
        do {
            cout << "Enter the Workout ID to remove: ";
            cin >> workID;

            for (int i = 0; i < workoutCount; i++) {
                if (workouts[i].workoutID == workID) {
                    isWorkoutIDValid = true;
                    break;
                }
            }

            if (!isWorkoutIDValid) {
                cout << "Invalid Workout ID! Please try again.\n\n";
            }
        } while (!isWorkoutIDValid);

        //  Unassign from trainer's client array
        for (int i = 0; i < NUM_TRAINERS; i++) {
            for (int j = 0; j < N; j++) {
                if (currentTrainer[i].client[j].clientId == ClientID) {
                    for (int n = 0; n < SIZE; n++) {
                        if (currentTrainer[i].client[j].workoutplans[n].workoutID == workID) {
                            currentTrainer[i].client[j].workoutplans[n] = Workout(); // Clear workout
                            WIDFOUND = true;
                            break;
                        }
                    }
                }
            }
        }

        //  Unassign from global clients[]
        for (int c = 0; c < clientCount; ++c) {
            if (clients[c].clientId == ClientID) {
                for (int p = 0; p < SIZE; ++p) {
                    if (clients[c].workoutplans[p].workoutID == workID) {
                        clients[c].workoutplans[p] = Workout(); // Clear workout
                        break;
                    }
                }
                break;
            }
        }


        if (WIDFOUND) {
            cout << "Workout \"" << workID << "\" was successfully removed from Client ID: " << ClientID << ".\n";
        }
        else {
            cout << "That workout wasn't found in the client's plan.\n";
        }

        // Ask to unassign another workout
        cout << "\nDo you want to remove another workout? (Y/N)\n";
        cout << "Enter your answer: ";
        cin >> answer;
        cout << endl;
        while (answer != "Y" && answer != "y" && answer != "N" && answer != "n") {
            cout << "Invalid input! Please enter 'Y' or 'N': ";
            cin >> answer;
            cout << endl;
        }
        cout << "----------------------------------------\n\n";
    } while (answer == "Y" || answer == "y");
}

void viewAssignedClientsForWorkout(Trainer currentTrainer[NUM_TRAINERS]) {
    string answer = "y";

    do {
        string inputWorkoutID;
        bool isWorkoutIDValid = false;
        bool clientFound = false;

        // Validate the workout ID
        do {
            cout << "Please enter the Workout ID you want to check: ";
            cin >> inputWorkoutID;

            for (int i = 0; i < workoutCount; i++) {
                if (workouts[i].workoutID == inputWorkoutID) {
                    isWorkoutIDValid = true;
                    break;
                }
            }

            if (!isWorkoutIDValid) {
                cout << "That Workout ID doesn't exist. Please try again.\n\n";
            }
        } while (!isWorkoutIDValid);

        cout << "\nClients assigned to this Workout:\n\n";

        //  Loop through trainers and their clients
        for (int i = 0; i < NUM_TRAINERS; i++) {
            for (int j = 0; j < N; j++) {
                string trainerClientID = currentTrainer[i].client[j].clientId;

                if (!trainerClientID.empty()) {
                    bool realClientFound = false;

                    for (int c = 0; c < clientCount; c++) {
                        if (clients[c].clientId == trainerClientID) {
                            realClientFound = true;

                            //  Check if this client has the workout assigned
                            for (int k = 0; k < SIZE; k++) {
                                if (currentTrainer[i].client[j].workoutplans[k].workoutID == inputWorkoutID) {
                                    cout << "Trainer ID: " << currentTrainer[i].TrainerID << "\n";
                                    cout << "Client ID: " << clients[c].clientId << "\n";
                                    cout << "Username: " << clients[c].cUsername << "\n\n";
                                    clientFound = true;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    //  Handle missing client in global list
                    if (!realClientFound) {
                        cout << "Oops! One of the trainer's clients couldn't be found in the system. ";
                        cout << "Please contact support if this continues.\n\n";
                    }
                }
            }
        }

        if (!clientFound) {
            cout << "No clients are currently assigned to Workout: " << inputWorkoutID << ".\n\n";
        }

        //Ask to view another workout
        cout << "Do you want to view another workout? (Y/N)\n";
        cout << "Enter your answer: ";
        cin >> answer;
        cout << endl;

        while (answer != "Y" && answer != "y" && answer != "N" && answer != "n") {
            cout << "Invalid input! Please enter 'Y' or 'N': ";
            cin >> answer;
            cout << endl;
        }

    } while (answer == "Y" || answer == "y");
}


// Kamila clients

void viewAssignedWorkouts(Client& currentClient) {
    cout << "\t***Your Assigned Workouts***\n\n";

    int foundWorkouts = 0;

    for (int i = 0; i < SIZE; i++) {
        if (currentClient.workoutplans[i].workoutID != "") {
            foundWorkouts++;
            cout << "Workout #" << foundWorkouts << ":" << endl;
            cout << "ID: " << currentClient.workoutplans[i].workoutID << endl;
            cout << "Name: " << currentClient.workoutplans[i].workoutName << endl;
            cout << "Duration: " << currentClient.workoutplans[i].duration << endl;
            if (currentClient.workoutplans[i].exerciseCount > 0) {
                cout << "Exercises:" << endl;
                for (int j = 0; j < currentClient.workoutplans[i].exerciseCount; j++) {
                    cout << "- " << currentClient.workoutplans[i].exercises[j] << endl;
                }
            }
            cout << "----------------------------------------" << endl;
        }
    }
    if (foundWorkouts == 0) {
        cout << "No workouts found! Ask your trainer to assign some.\n\n";
    }
}

void logCompletedWorkout(Client& currentClient) {
    cout << "\t***Log Completed Workout***\n\n";

    viewAssignedWorkouts(currentClient);
    cout << endl;

    bool hasAssignedWorkouts = false;
    for (int i = 0; i < SIZE; i++) {
        if (currentClient.workoutplans[i].workoutID != "") {
            hasAssignedWorkouts = true;
            break;
        }
    }

    if (!hasAssignedWorkouts) {
        return;
    }

    string ans = "y";
    do {
        string input;
        int workoutNumber;
        int realIndex = -1;
        int count = 0;

        cout << "Enter the number of the Workout you want to log: ";
        cin >> input;

        bool valid = true;
        for (int i = 0; i < input.length(); i++) {
            if (input[i] < '0' || input[i] > '9') {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid input! Please enter the right number.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        workoutNumber = stoi(input);

        for (int i = 0; i < SIZE; i++) {
            if (currentClient.workoutplans[i].workoutID != "") {
                count++;
                if (count == workoutNumber) {
                    realIndex = i;
                    break;
                }
            }
        }

        if (realIndex == -1) {
            cout << "Invalid workout number!\n\n";
            continue;
        }

        cout << endl;
        float percent = -1;
        bool validProgress = false;

        do {
            cout << "How much of " << currentClient.workoutplans[realIndex].workoutName << " did you complete (0-100%)? ";
            cin >> input;

            validProgress = true;
            bool hasdot = false;

            for (char c : input) {
                if (c == '.') {
                    if (hasdot) {
                        validProgress = false;
                        break;
                    }
                    hasdot = true;
                }
                else if (c < '0' || c > '9') {
                    validProgress = false;
                    break;
                }
            }

            if (validProgress) {
                percent = stof(input);
                if (percent < 0 || percent > 100) {
                    validProgress = false;
                    cout << "Please enter a value between 0 and 100.\n";
                }
            }
            else {
                cout << "Invalid input!\n\n";
            }

        } while (!validProgress);

        currentClient.progresslogs[realIndex] = percent;
        cout << "Progress logged: You completed " << percent << "% of " << currentClient.workoutplans[realIndex].workoutName << ".\n\n";

        cout << "Do you want to log another workout? (Y/N): ";
        cin >> ans;


        while (ans != "Y" && ans != "y" && ans != "N" && ans != "n") {
            cout << "Invalid input! Please enter 'Y' for yes or 'N' for no.\n";
            cout << "Enter again: ";
            cin >> ans;
            cout << endl;
        }

        cout << "----------------------------------------\n\n";
    } while (ans == "Y" || ans == "y");
}

void viewWorkoutHistory(Client& currentClient) {
    cout << "\t***Workout History***\n\n";

    bool hasWorkouts = false;
    for (int i = 0; i < SIZE; i++) {
        if (currentClient.workoutplans[i].workoutID != "") {
            hasWorkouts = true;
            cout << "Workout " << i + 1 << ": " << currentClient.workoutplans[i].workoutName << endl;
            cout << "Completed: " << currentClient.progresslogs[i] << " %" << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    if (hasWorkouts == false) {
        cout << "No workout history found. Please log some completed workouts!\n\n";
    }
}

void summarizeWorkoutProgress(Client& currentClient) {
    cout << "\t***Workout Progress Summary***\n\n";

    float sum = 0.0;
    int loggedCount = 0;
    int totalAssigned = 0;
    int fullyComplete = 0;
    for (int i = 0; i < SIZE; i++) {
        if (currentClient.workoutplans[i].workoutID != "") {
            totalAssigned++;
            if (currentClient.progresslogs[i] > 0.0) {
                loggedCount++;
                sum += currentClient.progresslogs[i];
                if (currentClient.progresslogs[i] == 100.0) {
                    fullyComplete++;
                }
            }
        }
    }
    cout << "Total Workouts Completed (100%): " << fullyComplete << " out of " << totalAssigned << endl;

    cout << "----------------------------------------\n\n";

    if (loggedCount == 0) {
        cout << "Average Progress : 0% (No progress logged yet)" << endl;
        cout << "It looks like you haven't logged any progress yet. Let's get started and make that first step today!" << endl;
    }
    else {
        cout << "Average Progress: " << (sum / loggedCount) << " %" << endl;
        if (fullyComplete == totalAssigned && totalAssigned != 0) {
            cout << "Fantastic job! You've completed all your workouts with full dedication! Keep it up!" << endl;
        }
        else {
            cout << "You're making excellent progress! Keep pushing towards your goal, you're on the right track." << endl;
        }
    }
    cout << "----------------------------------------\n\n";
}


//Laila clients measurement
void addMeasurement(Client clients[N * NUM_TRAINERS], string& clientId) {
    cout << "\t*** Add your new Measurements ***\n\nClient ID: " << clientId << "\n";

    for (int i = 0; i < (N * NUM_TRAINERS); i++) {
        if (clients[i].clientId == clientId) {
            if (clients[i].measure.count < 50) {
                float weight, height;

                // Validate weight
                while (true) {
                    cout << "Enter Weight (in kg): ";
                    cin >> weight;
                    if (cin.fail() || weight <= 0) {
                        cin.clear(); //  error
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a positive number for weight.\n";
                    }
                    else {
                        break;
                    }
                }

                // Validate height 3shan maykonsh fe division by 0
                while (true) {
                    cout << "Enter Height (in meters): ";
                    cin >> height;
                    if (cin.fail() || height <= 0) {
                        cin.clear(); // clear error
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a positive number for height.\n";
                    }
                    else {
                        break;
                    }
                }

                int index = clients[i].measure.count;
                clients[i].measure.weight[index] = weight;
                clients[i].measure.height[index] = height;
                clients[i].measure.bmi[index] = weight / (height * height);

                cout << "BMI calculated: " << clients[i].measure.bmi[index] << "\n";

                clients[i].measure.count++;
                cout << "Measurement added successfully for client " << clientId << "!\n\n";
            }
            else {
                cout << "Maximum number of measurements reached for this client.\n";
            }
            return;
        }
    }

    cout << "Client with ID " << clientId << " not found.\n";
}

void viewMeasurements(Client clients[N * NUM_TRAINERS], string& clientId) {
    cout << "\t***Measurement History***\n\nClient ID: " << clientId << "\n";
    for (int i = 0; i < (N * NUM_TRAINERS); i++) {
        if (clients[i].clientId == clientId) {
            if (clients[i].measure.count > 0) {
                for (int j = 0; j < clients[i].measure.count; j++) {
                    cout << "Measurement " << j + 1 << ":\n";
                    cout << "Weight: " << clients[i].measure.weight[j] << " kg\n";
                    cout << "Height: " << clients[i].measure.height[j] << " m\n";
                    cout << "BMI: " << clients[i].measure.bmi[j] << "\n";
                    cout << "----------------------\n";
                }
            }
            else {
                cout << "No measurements found for this client.\n";
            }
            return;
        }
    }
    cout << "Client with ID " << clientId << " not found.\n";
}

void viewAssignedClients(Trainer trainer[N]) {
    cout << "To Show Your Assigned Clients, Please Enter Your ID: ";
    string IDToBeFound;
    cin >> IDToBeFound;

    Trainer* currentTrainer = findTrainerById(IDToBeFound);

    if (currentTrainer != nullptr) {
        cout << "\nYour CLients:" << '\n';
        for (int j = 0, t = 1; j < 10; j++) {
            string clientID = currentTrainer->client[j].clientId;
            if (!clientID.empty()) {
                Client* trueClient = findClient(clientID);
                if (trueClient != nullptr) {
                    int last = trueClient->measure.count - 1;
                    cout << "~ ~ ~ ~ ~ ~ ~ ~ \n";
                    cout << "Client's Name: " << trueClient->cUsername << endl;
                    cout << "Client's ID: " << trueClient->clientId << endl;
                    cout << "Client's Weight: " << trueClient->measure.weight[last] << endl;
                    cout << "Client's Height: " << trueClient->measure.height[last] << endl;
                    cout << "Client's BMI: " << trueClient->measure.bmi[last] << endl;
                    for (int w = 0, l = 1; w < SIZE; w++) {
                        if (trueClient->workoutplans[w].workoutName != "") {
                            cout << "Workout " << l << " Name: " << trueClient->workoutplans[w].workoutName << endl;
                            cout << "Workout " << l << " ID: " << trueClient->workoutplans[w].workoutID << endl;
                            cout << "Client's Progress in This Workout: " << trueClient->progresslogs[w] << endl;
                            cout << "Number of Exercises in Workout " << l << ": " << trueClient->workoutplans[w].exerciseCount << endl;
                            l++;
                            for (int e = 0, q = 1; e < trueClient->workoutplans[w].exerciseCount; e++) {
                                if (trueClient->workoutplans[w].exercises[e] != "") {
                                    cout << "Exercise " << q << ": " << trueClient->workoutplans[w].exercises[e] << endl;
                                    cout << "Exercise " << q << " Duration: " << trueClient->workoutplans[w].duration << endl;
                                    q++;
                                }
                            }
                        }
                    }
                }

                cout << "----------------------------------------\n\n";
            }
        }
    }
}

void clientActions() {
    string choice;
    bool running = true;

    if (loggedInClient == nullptr) {
        cout << "Error: No client is currently logged in.\n";
        return;
    }

    cout << "Client ID: " << loggedInClient->clientId << endl;

    while (running) {
        cout << "\t\t\t\t\t    Personal Workout Hub\n";
        cout << "\t\t\t\t\t****************************\n";
        cout << "Press" << endl;
        cout << "1. View Assigned Workouts" << endl;
        cout << "2. Log Completed Workout" << endl;
        cout << "3. View Workout History" << endl;
        cout << "4. View Workout Progress Summary" << endl;
        cout << "5. Add Measurement" << endl;
        cout << "6. View Measurements" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cout << endl;

        if (choice == "1") {
            viewAssignedWorkouts(*loggedInClient);
        }
        else if (choice == "2") {
            logCompletedWorkout(*loggedInClient);
        }
        else if (choice == "3") {
            viewWorkoutHistory(*loggedInClient);
        }
        else if (choice == "4") {
            summarizeWorkoutProgress(*loggedInClient);
        }
        else if (choice == "5") {
            addMeasurement(clients, loggedInClient->clientId);
        }
        else if (choice == "6") {
            viewMeasurements(clients, loggedInClient->clientId);
        }
        else if (choice == "0") {
            cout << "Exiting the client menu.\n";
            running = false;
            continue;
        }
        else {
            cout << "Invalid choice! Please enter a number between 0 and 6.\n";
            cout << "----------------------------------------\n\n";
            continue;
        }

        string answer;
        cout << "Do you want to do another operation? (Y/N)\n";
        cout << "Enter your answer: ";
        cin >> answer;

        while (answer != "Y" && answer != "y" && answer != "N" && answer != "n") {
            cout << "Invalid input! Enter 'Y' to continue or 'N' to exit: ";
            cin >> answer;
        }

        if (answer == "N" || answer == "n") {
            cout << "Returning to the main menu.\n";
            running = false;
        }
        cout << "----------------------------------------\n\n";
    }
}

void trainerActions() {
    string choice;
    bool running = true;

    if (loggedInTrainer == nullptr) {
        cout << "Error: No trainer is currently logged in.\n";
        return;
    }

    while (running) {
        cout << "\t\t\t\t\t    Trainer Control Hub\n";
        cout << "\t\t\t\t\t****************************\n";
        cout << "Press" << endl;
        cout << "1. View Your Clients details\n";
        cout << "2. Add Workout to Client\n";
        cout << "3. Remove Workout from Client\n";
        cout << "4. Edit Workout\n";
        cout << "5. Delete Workout\n";
        cout << "6. List all Workouts\n";
        cout << "7. View Assigned Clients for a Workout\n";
        cout << "0. Go back to the Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;


        if (choice == "1") {
            cout << "\t***View your Clients Details***\n\n";
            viewAssignedClients(trainers);
        }
        else if (choice == "2") {
            cout << "\t***Add Workout To Client***\n\n";
            assignWorkoutToClient(trainers);
        }
        else if (choice == "3") {
            cout << "\t***Remove Workout from Client***\n\n";
            unassignWorkoutFromClient(trainers);
        }
        else if (choice == "4") {
            cout << "\t***Edit Workout***\n\n";
            editWorkout();
        }
        else if (choice == "5") {
            cout << "\t***Delete Workout***\n\n";
            deleteWorkout();
        }
        else if (choice == "6") {
            cout << "\t***List All Workouts***\n\n";
            listAllWorkouts();
        }
        else if (choice == "7") {
            cout << "\t***View Assigned Clients for a Workout***\n\n";
            viewAssignedClientsForWorkout(trainers);
        }
        else if (choice == "0") {
            cout << "Returning to the main menu.\n";
            running = false;
            continue;
        }
        else {
            cout << "Invalid choice! Please enter a number between 0 and 7.\n";
            cout << "----------------------------------------\n\n";
            continue;
        }

        string answer;
        cout << "Do you want to do another operation? (Y/N)\n";
        cout << "Enter your answer: ";
        cin >> answer;

        while (answer != "Y" && answer != "y" && answer != "N" && answer != "n") {
            cout << "Invalid input! Enter 'Y' to continue or 'N' to exit: ";
            cin >> answer;
        }

        if (answer == "N" || answer == "n") {
            cout << "\nReturning to the main menu.\n";
            running = false;
        }
        cout << "----------------------------------------\n\n";
    }
}


// Check if the string is a valid whole number using plain ASCII comparison
bool isValidWholeNumber(const string& input) {
    if (input.empty()) return false;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] < '0' || input[i] > '9') {
            return false;
        }
    }
    return true;
}

void takeChoice() {
    string input;
    int choice = -1;

    do {
        mainMenu();
        cout << "Enter your choice: ";
        cin >> input;

        if (!isValidWholeNumber(input)) {
            cout << "Invalid input. Please enter a whole number (no decimals or letters).\n";
            continue;
        }

        choice = stoi(input); // conversion after validation

        switch (choice) {
        case 1:
            registerClient();
            break;
        case 2:
            registerTrainer();
            break;
        case 3: {
            string loggedInAs = loginUser();
            if (!loggedInAs.empty()) {
                cout << "Welcome!\n";
                if (loggedInAs == "client") {
                    clientActions();
                }
                else if (loggedInAs == "trainer") {
                    trainerActions();
                }
            }
            break;
        }
        case 0:
            cout << "Exiting the application. Goodbye <3 \n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 0);
}

int main() {
    loadData();
    cout << "\t\t\t\t\t--- Welcome to our fitness app ---" << endl;
    takeChoice();

    return 0;
}