#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string currentUsername = "", currentPickUp = "", currentDrop = "", driverName = "";
int currentFare = 0;
bool driverAvailable = false;

// Forward declarations
void passengerMenu();
void Login();
void driverMenu();
void rideBooking();
void viewRideHistory();
void viewFareEstimate();
bool setAvailability();
void viewAssignedRide();
void completeRide();
void viewEarning();
void viewDriverHistory();

// Get the Location index for pickUp and Drop locations
int getLocationIndex(string location[]) {
    int index;
    while (true) {
        for (int i = 0; i < 5; i++) {
            cout << (i + 1) << ". " << location[i] << endl;
        }
        cin >> index;
        if (index >= 1 && index <= 5) {
            return index - 1;
        }
        cout << "Invalid choice! Please enter 1-5." << endl;
    }
}

// Get the Ride Type index
int getRideType() {
    string rides[3] = {"Bike", "Car", "Premium"};
    int ride;
    while (true) {
        cout << "Choose your ride type:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << (i + 1) << ". " << rides[i] << endl;
        }
        cin >> ride;
        if (ride >= 1 && ride <= 3) {
            return ride;
        }
        cout << "Invalid choice! Please enter 1-3." << endl;
    }
}

// Drivers Account Creation Function
void driverCreateAccount() {
    cout << "~~~~~~~~~~Drivers Zone~~~~~~~~~~" << endl;
    cout << "--------Creating Account--------" << endl;
    string username, password, name;
    ofstream inputfile;
    inputfile.open("Driver.txt", ios::app);
    cout << "Enter your name: ";
    cin >> name;
    inputfile << name << " ";
    cout << "Enter the Username: ";
    cin >> username;
    inputfile << username << " ";
    cout << "Enter the password: ";
    cin >> password;
    inputfile << password << endl;
    cout << "Account has been created!" << endl;
    inputfile.close();
    Login();
}

// Users Account Creation Function
void userCreateAccount() {
    cout << "~~~~~~~~~~Users Zone~~~~~~~~~~" << endl;
    cout << "--------Creating Account--------" << endl;
    string username, password, name;
    ofstream inputfile;
    inputfile.open("User.txt", ios::app);
    cout << "Enter your name: ";
    cin >> name;
    inputfile << name << " ";
    cout << "Enter the Username: ";
    cin >> username;
    inputfile << username << " ";
    cout << "Enter the password: ";
    cin >> password;
    inputfile << password << endl;
    cout << "Account has been created!" << endl;
    inputfile.close();
    Login();
}

// Drivers Login Function
bool driverLogin() {
    cout << "~~~~~~~~~~Drivers Zone~~~~~~~~~~" << endl;
    cout << "--------Account Login--------" << endl;
    string username, password;
    string fileName, fileUser, filePass;
    ifstream outputfile("Driver.txt");
    cout << "Enter the username: ";
    cin >> username;
    cout << "Enter the password: ";
    cin >> password;
    while (outputfile >> fileName >> fileUser >> filePass) {
        if (username == fileUser && password == filePass) {
            driverName = fileName;
            outputfile.close();
            return true;
        }
    }
    outputfile.close();
    return false;
}

// Users Login Function
bool userLogin() {
    cout << "~~~~~~~~~~Users Zone~~~~~~~~~~" << endl;
    cout << "--------Account Login--------" << endl;
    string username, password;
    string fileName, fileUser, filePass;
    ifstream outputfile("User.txt");
    cout << "Enter the username: ";
    cin >> username;
    cout << "Enter the password: ";
    cin >> password;
    while (outputfile >> fileName >> fileUser >> filePass) {
        if (username == fileUser && password == filePass) {
            currentUsername = fileName;
            outputfile.close();
            return true;
        }
    }
    outputfile.close();
    return false;
}

// Ride Booking Function (sets global ride details for driver assignment)
void rideBooking() {
    string location[] = {"Mughalpura", "DHA", "Behria", "Chaburji", "Defense Road"};
    int distance[5][5] = {
        {0, 15, 17, 9, 20},
        {15, 0, 10, 12, 14},
        {17, 10, 0, 9, 13},
        {9, 12, 9, 0, 12},
        {20, 14, 13, 12, 0}
    };
    int pickUpIndex = getLocationIndex(location);
    int dropIndex;
    do {
        cout << "Pick Up and Drop locations cannot be the same. Choose Drop Location again:" << endl;
        dropIndex = getLocationIndex(location);
    } while (dropIndex == pickUpIndex);
    int rideType = getRideType();
    int rate = (rideType == 1) ? 40 : (rideType == 2) ? 80 : 120;
    int fare = distance[pickUpIndex][dropIndex] * rate;
    currentPickUp = location[pickUpIndex];
    currentDrop = location[dropIndex];
    currentFare = fare;
    cout << "Your fare will be Rs." << fare << endl;
    cout << "Your Ride is Booked! Waiting for an available driver." << endl;
}

// View Ride History for Passenger
void viewRideHistory() {
    ifstream outputfile("Rides.txt");
    string name, pickUp, drop, driver;
    int fare;
    bool found = false;
    string searchName = currentUsername;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "     Your History     " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    if (outputfile.is_open()) {
        while (outputfile >> name >> pickUp >> drop >> fare >> driver) {
            if (name == searchName) {
                cout << "Name: " << name << endl;
                cout << "From: " << pickUp << endl;
                cout << "To: " << drop << endl;
                cout << "Fare: Rs." << fare << endl;
                cout << "Driver: " << driver << endl;
                cout << endl;
                found = true;
            }
        }
        outputfile.close();
    }
    if (!found) {
        cout << "No Record Found!" << endl;
    }
}

// View Fare Estimate (no booking or file write)
void viewFareEstimate() {
    string location[] = {"Mughalpura", "DHA", "Behria", "Chaburji", "Defense Road"};
    int distance[5][5] = {
        {0, 15, 17, 9, 20},
        {15, 0, 10, 12, 14},
        {17, 10, 0, 9, 13},
        {9, 12, 9, 0, 12},
        {20, 14, 13, 12, 0}
    };
    int pickUpIndex = getLocationIndex(location);
    int dropIndex;
    do {
        cout << "Pick Up and Drop locations cannot be the same. Choose Drop Location again:" << endl;
        dropIndex = getLocationIndex(location);
    } while (dropIndex == pickUpIndex);
    int rideType = getRideType();
    int rate = (rideType == 1) ? 40 : (rideType == 2) ? 80 : 120;
    int fare = distance[pickUpIndex][dropIndex] * rate;
    cout << "Estimated fare: Rs." << fare << endl;
}

void passengerMenu() {
    int choice;
    while (true) {
        cout << "=======================" << endl;
        cout << "    Passengers Menu    " << endl;
        cout << "=======================" << endl;
        cout << "1. Book a Ride" << endl;
        cout << "2. View Ride History" << endl;
        cout << "3. View Fare Estimation" << endl;
        cout << "0. Logout" << endl;
        cin >> choice;
        if (choice == 0) {
            cout << "Logged Out!" << endl;
            Login();
            return;
        }
        switch (choice) {
        case 1:
            rideBooking();
            break;
        case 2:
            viewRideHistory();
            break;
        case 3:
            viewFareEstimate();
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    }
}

bool setAvailability() {
    int active;
    cout << "Are you Ready/Active for a ride? (1 for Yes / 0 for No): ";
    cin >> active;
    driverAvailable = (active == 1);
    if (driverAvailable) {
        cout << "Availability set to ACTIVE." << endl;
    } else {
        cout << "Availability set to INACTIVE." << endl;
    }
    return driverAvailable;
}

void viewAssignedRide() {
    if (!driverAvailable) {
        cout << "You must set your availability to ACTIVE first!" << endl;
        return;
    }
    if (currentPickUp.empty()) {
        cout << "No ride assigned currently." << endl;
    } else {
        cout << "============ Assigned Ride ============" << endl;
        cout << "Passenger Name: " << currentUsername << endl;
        cout << "PickUp Location: " << currentPickUp << endl;
        cout << "Drop Location: " << currentDrop << endl;
        cout << "Estimated Fare: Rs." << currentFare << endl;
        cout << "======================================" << endl;
    }
}

void completeRide() {
    if (!driverAvailable) {
        cout << "You must set your availability to ACTIVE first!" << endl;
        return;
    }
    if (currentPickUp.empty()) {
        cout << "No ride assigned to complete." << endl;
        return;
    }
    ofstream rideRecord("Rides.txt", ios::app);
    rideRecord << currentUsername << " "
               << currentPickUp << " "
               << currentDrop << " "
               << currentFare << " "
               << driverName << endl;
    rideRecord.close();
    cout << "Ride completed successfully! Record saved." << endl;
    // Clear the current ride
    currentUsername = "";
    currentPickUp = "";
    currentDrop = "";
    currentFare = 0;
}

void viewDriverHistory() {
    ifstream file("Rides.txt");
    string user, pu, dr, drv;
    int fare;
    cout << "===== Driver Ride History =====\n";
    bool hasRides = false;
    if (file.is_open()) {
        while (file >> user >> pu >> dr >> fare >> drv) {
            if (drv == driverName) {
                cout << user << " | "
                     << pu << " -> " << dr
                     << " | Rs." << fare << endl;
                hasRides = true;
            }
        }
        file.close();
    }
    if (!hasRides) {
        cout << "No rides completed yet." << endl;
    }
}

void viewEarning() {
    ifstream file("Rides.txt");
    string u, pu, dr, drv;
    int fare, total = 0;
    if (file.is_open()) {
        while (file >> u >> pu >> dr >> fare >> drv) {
            if (drv == driverName) {
                total += fare;
            }
        }
        file.close();
    }
    cout << "Total Earnings: Rs." << total << endl;
}

void driverMenu() {
    int choice;
    while (true) {
        cout << "=====================" << endl;
        cout << "    Driver's Menu    " << endl;
        cout << "=====================" << endl;
        cout << "1. Set Availability" << endl;
        cout << "2. View Assigned Ride" << endl;
        cout << "3. Complete Ride" << endl;
        cout << "4. View Earning" << endl;
        cout << "5. View Ride History" << endl;
        cout << "0. Logout" << endl;
        cin >> choice;
        if (choice == 0) {
            cout << "Logged Out!" << endl;
            Login();
            return;
        }
        switch (choice) {
        case 1:
            setAvailability();
            break;
        case 2:
            viewAssignedRide();
            break;
        case 3:
            completeRide();
            break;
        case 4:
            viewEarning();
            break;
        case 5:
            viewDriverHistory();
            break;
        default:
            cout << "Invalid Choice!" << endl;
            break;
        }
    }
}

void Login() {
    int choice;
    cout << "Login/Register:" << endl;
    cout << "1. User's Login" << endl;
    cout << "2. User's Account Creation" << endl;
    cout << "3. Driver's Login" << endl;
    cout << "4. Driver's Account Creation" << endl;
    cout << "0. Exit" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        do {
            if (userLogin()) {
                cout << "Access Authorized!" << endl;
                passengerMenu();
                return;
            } else {
                cout << "Access Denied!" << endl;
                int option;
                cout << "Want to go back to menu? (1 for yes): ";
                cin >> option;
                if (option == 1) {
                    Login();
                    return;
                }
                // else retry
            }
        } while (true);
        break;
    case 2:
        userCreateAccount();
        break;
    case 3:
        do {
            if (driverLogin()) {
                cout << "Access Authorized!" << endl;
                driverMenu();
                return;
            } else {
                cout << "Access Denied!" << endl;
                int option;
                cout << "Want to go back to menu? (1 for yes): ";
                cin >> option;
                if (option == 1) {
                    Login();
                    return;
                }
                // else retry
            }
        } while (true);
        break;
    case 4:
        driverCreateAccount();
        break;
    case 0:
        cout << "Goodbye!" << endl;
        exit(0);
    default:
        cout << "Invalid Choice" << endl;
        Login();
        break;
    }
}

int main() {
    cout << "==================================" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "      Online Ride Booking App     " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "==================================" << endl;
    Login();
    return 0;
}