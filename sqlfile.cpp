// sqlfile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sqlite/sqlite3.h"
#include<stdio.h>
#include<string>
//#include<format>
using namespace std;

static int createDB(const char* s);
static int createTable(const char* s);
//Registration
static void registerUser(const char* s, const string& username, int password) {
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(s, &DB);

	string sql = "INSERT INTO Users (Username, Password, Status, LocationFrom, LocationTo) VALUES ('"
		+ username + "', " + std::to_string(password) + ", 'on hold', '', '');";

	exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error registering user: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "User registered successfully" << std::endl;
	}
	sqlite3_close(DB);
}


static int loginUser(const char* s, const string& username, int password) {
	sqlite3* DB;
	sqlite3_stmt* stmt;
	int exit = sqlite3_open(s, &DB);

	std::string sql = "SELECT UserID FROM Users WHERE Username = '" + username + "' AND Password = " + std::to_string(password) + ";";
	exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

	int userID = -1;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		userID = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);

	return userID;
}
//Rider registration
static void registerRider(const char* s ,const string& username, int password) {
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(s, &DB);

	string sql = "INSERT INTO Riders (Username, Password) VALUES ('"
		+ username + "', " + std::to_string(password) + ");";

	exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error registering rider: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Rider registered successfully" << std::endl;
	}
	sqlite3_close(DB);
}
// Function to login a rider and return the rider ID
static int loginRider(const char* s ,const string& username, int password) {
	sqlite3* DB;
	sqlite3_stmt* stmt;
	int exit = sqlite3_open(s, &DB);

	std::string sql = "SELECT RiderID FROM Riders WHERE Username = '" + username + "' AND Password = " + std::to_string(password) + ";";
	exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

	int riderID = -1;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		riderID = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);

	return riderID;
}
// User location and status
static void updateUserLocation(const char* s,int userID, const string& locationFrom, const string& locationTo) {
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(s, &DB);

	string sql = "UPDATE Users SET LocationFrom = '" + locationFrom + "', LocationTo = '" + locationTo + "', Status = 'on hold' WHERE UserID = " + std::to_string(userID) + ";";

	exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error updating location: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Location updated successfully" << std::endl;
	}

	sqlite3_close(DB);
}
//View requests
static void viewRequests(const char *s) {
	sqlite3* DB;
	sqlite3_stmt* stmt;
	int exit = sqlite3_open(s, &DB);

	string sql = "SELECT UserID, Username, Status, LocationFrom, LocationTo FROM Users;";

	exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
	if (exit != SQLITE_OK) {
		std::cerr << "Error viewing data: " << sqlite3_errmsg(DB) << std::endl;
		return;
	}

	cout << "UserID\t\tUsername\t\tStatus\t\t\tLocationFrom\t\t\tLocationTo\n";
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int userID = sqlite3_column_int(stmt, 0);
		string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		string locationFrom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		string locationTo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

		cout << userID << "\t\t" << username << "\t\t\t" << status << "\t\t\t" << locationFrom << "\t\t\t\t" << locationTo << "\n";
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}
//Updating status and adding to accepted rides
static void updateStatusAndAcceptRide(const char* s, int userID, int riderID, const string& newStatus) {
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(s, &DB);

	std::string sqlUpdate = "UPDATE Users SET Status = '" + newStatus + "' WHERE UserID = " + std::to_string(userID) + ";";

	exit = sqlite3_exec(DB, sqlUpdate.c_str(), nullptr, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error updating status: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
}
// Function to insert accepted rides
static void insertAcceptedRide( const char* s, int userID, int riderID) {
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(s, &DB);

	std::string sql = "INSERT INTO AcceptedRides (UserID, RiderID) VALUES (" + std::to_string(userID) + ", " + std::to_string(riderID) + ");";

	exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error inserting accepted ride: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Accepted ride inserted successfully" << std::endl;
	}
	sqlite3_close(DB);
}

// Function to view accepted rides
static void viewAcceptedRides(const char* s) {
	sqlite3* DB;
	sqlite3_stmt* stmt;
	int exit = sqlite3_open(s, &DB);

	std::string sql = "SELECT * FROM AcceptedRides;";
	exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

	if (exit != SQLITE_OK) {
		std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
		return;
	}

	std::cout << "RideID\tUserID\tRiderID\n";
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int rideID = sqlite3_column_int(stmt, 0);
		int userID = sqlite3_column_int(stmt, 1);
		int riderID = sqlite3_column_int(stmt, 2);

		std::cout << rideID << "\t" << userID <<"\t"<< riderID<<"\n";
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}
int main()
{
	const char* dir = "C:\\Users\\acer\\source\\repos\\sqlfile\\sqlfile\\x64\\Debug\\Delete_me\\RIDESHARING.db";
	sqlite3* DB;
	createDB(dir);
	createTable(dir);
	string userUsername;
	int userPassword;
	int riderPassword;
	int riderID;
	string riderUsername;
	string LocationA, LocationB;
	int choice;
	cout << "Type 1 for registration and 0 for login for user" << endl;
	cout << "Type 2 for registration and 3 for login for rider" << endl;
	cin >> choice;
	if (choice == 1) {
		// Simulate user registration and login
		cout << "To create an account with us create username and password" << endl;
		cin >> userUsername >> userPassword;
		registerUser(dir, userUsername, userPassword);
		main();
	}
	else if (choice == 0) {
		cout << "Enter the login credentials" << endl;
		cout << "Enter the username " << endl;
		cin >> userUsername;
		cout << "\nEnter the password " << endl;
		cin >> userPassword;
		int userID = loginUser(dir, userUsername, userPassword);
		if (userID != -1) {
			std::cout << "User logged in successfully with UserID: " << userID << std::endl;
			cout << "Enter the the location and the destination" << endl;
			cout << "From: ";
			cin >> LocationA;
			cout << "To: ";
			cin >> LocationB;
			updateUserLocation(dir, userID, LocationA, LocationB);
		}
		else {
			std::cout << "Invalid username or password" << std::endl;
			main();
		}
	}
		
	else if(choice == 2) {
		cout << "To create an account with us create username and password" << endl;
		cin >> userUsername >> userPassword;
		registerRider(dir, userUsername, userPassword);
		main();
	}
	else {
		cout << "Enter the login credentials" << endl;
		cout << "Enter the username " << endl;
		cin >> riderUsername;
		cout << "\nEnter the password " << endl;
		cin >> riderPassword;
		int riderID = loginRider(dir, riderUsername, riderPassword);
		if (riderID != -1) {
			std::cout << "Rider logged in successfully with RiderID: " << riderID << std::endl;
			cout << endl;
			viewRequests(dir);
			cout << "Is there any rides that you want to accept type 1 else 0" << endl;
			bool choice;
			cin >> choice;
			if (choice == 1) {
				int userID;
				string newstatus;
				cout << "Enter the user's Id whose status you want to modify " << endl;
				cin >> userID;
				cout << "Enter the new status for user " << userID << endl;
				cin >> newstatus;
				updateStatusAndAcceptRide(dir, userID, riderID, newstatus);
				insertAcceptedRide(dir, userID, riderID);
				viewAcceptedRides(dir);
			}
			else {
				main();
			}
		}
		else {
			std::cout << "Invalid username or password" << std::endl;
			main();
			}
		}
			return 0;
		}


static int createDB(const char* s)
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(s, &DB);
	sqlite3_close(DB);
	return 0;
}

static int createTable(const char* s)
{
	sqlite3* DB;
	char* errorMessage;

	string userTable = "CREATE TABLE IF NOT EXISTS Users("
		"UserID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Username TEXT NOT NULL, "
		"Password INT NOT NULL,"
		"Status TEXT NOT NULL, "
		"LocationFrom TEXT NOT NULL, "
		"LocationTo TEXT NOT NULL);";
	string riderTable = "CREATE TABLE IF NOT EXISTS Riders("
		"RiderID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Username TEXT NOT NULL, "
		"Password INTEGER NOT NULL);";

	string acceptedRidesTable = "CREATE TABLE IF NOT EXISTS AcceptedRides("
		"RideID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"UserID INTEGER, "
		"RiderID INTEGER, "
		"FOREIGN KEY(UserID) REFERENCES Users(UserID), "
		"FOREIGN KEY(RiderID) REFERENCES Riders(RiderID));";


	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, userTable.c_str(), nullptr, 0, &errorMessage);
		if (exit != SQLITE_OK) {
			std::cerr << "Error creating Users table: " << errorMessage << std::endl;
			sqlite3_free(errorMessage);
		}

		exit = sqlite3_exec(DB, riderTable.c_str(), nullptr, 0, &errorMessage);
		if (exit != SQLITE_OK) {
			std::cerr << "Error creating Riders table: " << errorMessage << std::endl;
			sqlite3_free(errorMessage);
		}

		exit = sqlite3_exec(DB, acceptedRidesTable.c_str(), nullptr, 0, &errorMessage);
		if (exit != SQLITE_OK) {
			std::cerr << "Error creating AcceptedRides table: " << errorMessage << std::endl;
			sqlite3_free(errorMessage);
		}
		sqlite3_close(DB);
}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

