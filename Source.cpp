#include <iostream>
#include "sqlite3.h"
#include <string>
#include <stdexcept>

using namespace std;

static int createDB(const char* s);
static int createTable(const char* s);
static void handleSQLError(int exitCode, char* errorMessage);
static void registerUser(const char* s, const string& username, const string& password);
static int loginUser(const char* s, const string& username, const string& password);
static void registerRider(const char* s, const string& username, const string& password);
static int loginRider(const char* s, const string& username, const string& password);
static void updateUserLocation(const char* s, int userID, const string& locationFrom, const string& locationTo);
static void viewRequests(const char* s);
static void updateStatusAndAcceptRide(const char* s, int userID, int riderID, const string& newStatus);
static void insertAcceptedRide(const char* s, int userID, int riderID);
static void viewAcceptedRides(const char* s);

int main() {
    const char* dir = "C:\\Users\\acer\\source\\repos\\sqlfile\\sqlfile\\x64\\Debug\\Delete_me\\RIDESHARING.db";
    createDB(dir);
    createTable(dir);

    string username, password, locationA, locationB, status;
    int choice, userID, riderID;

    while (true) {
        cout << "Menu:\n1. Register User\n2. Login User\n3. Register Rider\n4. Login Rider\n5. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter username and password: ";
            cin >> username >> password;
            registerUser(dir, username, password);
            break;
        case 2:
            cout << "Enter username and password: ";
            cin >> username >> password;
            userID = loginUser(dir, username, password);
            if (userID != -1) {
                cout << "User logged in successfully with UserID: " << userID << endl;
                cout << "Enter location (From and To): ";
                cin >> locationA >> locationB;
                updateUserLocation(dir, userID, locationA, locationB);
            }
            else {
                cout << "Invalid username or password" << endl;
            }
            break;
        case 3:
            cout << "Enter username and password: ";
            cin >> username >> password;
            registerRider(dir, username, password);
            break;
        case 4:
            cout << "Enter username and password: ";
            cin >> username >> password;
            riderID = loginRider(dir, username, password);
            if (riderID != -1) {
                cout << "Rider logged in successfully with RiderID: " << riderID << endl;
                viewRequests(dir);
                cout << "Do you want to accept a ride? (1 for Yes, 0 for No): ";
                int acceptChoice;
                cin >> acceptChoice;
                if (acceptChoice == 1) {
                    cout << "Enter UserID and new status: ";
                    cin >> userID >> status;
                    updateStatusAndAcceptRide(dir, userID, riderID, status);
                    insertAcceptedRide(dir, userID, riderID);
                    viewAcceptedRides(dir);
                }
            }
            else {
                cout << "Invalid username or password" << endl;
            }
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

static int createDB(const char* s) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    if (exit) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }
    sqlite3_close(DB);
    return 0;
}

static int createTable(const char* s) {
    sqlite3* DB;
    char* errorMessage;
    string userTable = "CREATE TABLE IF NOT EXISTS Users("
        "UserID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Username TEXT NOT NULL, "
        "Password TEXT NOT NULL,"
        "Status TEXT NOT NULL, "
        "LocationFrom TEXT NOT NULL, "
        "LocationTo TEXT NOT NULL);";

    string riderTable = "CREATE TABLE IF NOT EXISTS Riders("
        "RiderID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Username TEXT NOT NULL, "
        "Password TEXT NOT NULL);";

    string acceptedRidesTable = "CREATE TABLE IF NOT EXISTS AcceptedRides("
        "RideID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "UserID INTEGER, "
        "RiderID INTEGER, "
        "FOREIGN KEY(UserID) REFERENCES Users(UserID), "
        "FOREIGN KEY(RiderID) REFERENCES Riders(RiderID));";

    int exit = sqlite3_open(s, &DB);
    if (exit) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }

    exit = sqlite3_exec(DB, userTable.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    exit = sqlite3_exec(DB, riderTable.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    exit = sqlite3_exec(DB, acceptedRidesTable.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    sqlite3_close(DB);
    return 0;
}

static void handleSQLError(int exitCode, char* errorMessage) {
    if (exitCode != SQLITE_OK) {
        cerr << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

static void registerUser(const char* s, const string& username, const string& password) {
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(s, &DB);

    string sql = "INSERT INTO Users (Username, Password, Status, LocationFrom, LocationTo) VALUES ('"
        + username + "', '" + password + "', 'on hold', '', '');";

    exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    if (exit == SQLITE_OK) {
        cout << "User registered successfully" << endl;
    }
    sqlite3_close(DB);
}

static int loginUser(const char* s, const string& username, const string& password) {
    sqlite3* DB;
    sqlite3_stmt* stmt;
    int exit = sqlite3_open(s, &DB);

    string sql = "SELECT UserID FROM Users WHERE Username = '" + username + "' AND Password = '" + password + "';";
    exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    int userID = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userID = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    return userID;
}

static void registerRider(const char* s, const string& username, const string& password) {
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(s, &DB);

    string sql = "INSERT INTO Riders (Username, Password) VALUES ('" + username + "', '" + password + "');";

    exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    if (exit == SQLITE_OK) {
        cout << "Rider registered successfully" << endl;
    }
    sqlite3_close(DB);
}

static int loginRider(const char* s, const string& username, const string& password) {
    sqlite3* DB;
    sqlite3_stmt* stmt;
    int exit = sqlite3_open(s, &DB);

    string sql = "SELECT RiderID FROM Riders WHERE Username = '" + username + "' AND Password = '" + password + "';";
    exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    int riderID = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        riderID = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    return riderID;
}

static void updateUserLocation(const char* s, int userID, const string& locationFrom, const string& locationTo) {
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(s, &DB);

    string sql = "UPDATE Users SET LocationFrom = '" + locationFrom + "', LocationTo = '" + locationTo + "', Status = 'on hold' WHERE UserID = " + to_string(userID) + ";";

    exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    if (exit == SQLITE_OK) {
        cout << "Location updated successfully" << endl;
    }
    sqlite3_close(DB);
}

static void viewRequests(const char* s) {
    sqlite3* DB;
    sqlite3_stmt* stmt;
    int exit = sqlite3_open(s, &DB);

    string sql = "SELECT UserID, Username, LocationFrom, LocationTo, Status FROM Users WHERE Status = 'on hold';";
    exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    cout << "Pending Requests:" << endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int userID = sqlite3_column_int(stmt, 0);
        string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string locationFrom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string locationTo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        cout << "UserID: " << userID << ", Username: " << username
            << ", Location From: " << locationFrom << ", Location To: " << locationTo
            << ", Status: " << status << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

static void updateStatusAndAcceptRide(const char* s, int userID, int riderID, const string& newStatus) {
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(s, &DB);

    string sql = "UPDATE Users SET Status = '" + newStatus + "' WHERE UserID = " + to_string(userID) + ";";
    exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    if (exit == SQLITE_OK) {
        cout << "Ride status updated successfully" << endl;
    }
    sqlite3_close(DB);
}

static void insertAcceptedRide(const char* s, int userID, int riderID) {
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(s, &DB);

    string sql = "INSERT INTO AcceptedRides (UserID, RiderID) VALUES (" + to_string(userID) + ", " + to_string(riderID) + ");";

    exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
    handleSQLError(exit, errorMessage);

    if (exit == SQLITE_OK) {
        cout << "Ride accepted successfully" << endl;
    }
    sqlite3_close(DB);
}

static void viewAcceptedRides(const char* s) {
    sqlite3* DB;
    sqlite3_stmt* stmt;
    int exit = sqlite3_open(s, &DB);

    string sql = "SELECT RideID, UserID, RiderID FROM AcceptedRides;";
    exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    cout << "Accepted Rides:" << endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int rideID = sqlite3_column_int(stmt, 0);
        int userID = sqlite3_column_int(stmt, 1);
        int riderID = sqlite3_column_int(stmt, 2);

        cout << "RideID: " << rideID << ", UserID: " << userID << ", RiderID: " << riderID << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
