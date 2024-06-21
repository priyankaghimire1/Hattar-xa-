include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <sqlite3.h>
#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"

using namespace std;

static int createDB(const char* a);
static int createTable(const char* b);
static int insertData(const char* c, long int a, int b);
static int selectData(const char* d);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // Networking Part
    SOCKET clientSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if (wsaerr != 0) {
        cout << "The Winsock dll not found" << endl;
        return 0;
    }
    else {
        cout << "The Winsock dll found" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket() is ok!" << endl;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(port);

    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "Client: connect() - Failed to connect." << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "Client: connect() is OK" << endl;
        cout << "Client: Can start sending and receiving data..." << endl;
    }

    cout << "\n=== STEP to chat with the server===\n\n" << endl;
    char buffer[200];
    cout << "Please enter the destination and the location to send to the rider:" << endl;
    cin.getline(buffer, 200);

    int byteCount = send(clientSocket, buffer, 200, 0);
    if (byteCount > 0) {
        cout << "Message sent: " << buffer << endl;
    }
    else {
        WSACleanup();
    }

    byteCount = recv(clientSocket, buffer, 200, 0);
    if (byteCount > 0) {
        cout << "Message received: " << buffer << endl;
    }
    else {
        WSACleanup();
    }

    cout << "\n=== Step to close the Socket=== \n\n\n" << endl;
    system("pause");

    // SQLite Part
    long int num;
    int pin;
    cout << "Enter the number" << endl;
    cin >> num;
    cout << "Enter the pin" << endl;
    cin >> pin;

    const char* dir = "D:\\Priyanka\\Coding\\code\\test\\database\\rider.db";
    createDB(dir);
    createTable(dir);
    insertData(dir, num, pin);
    selectData(dir);

    WSACleanup();

    // Qt GUI Part
    MainWindow w;
    w.show();

    return a.exec();
}

static int createDB(const char* a) {
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open(a, &DB);
    sqlite3_close(DB);
    return 0;
}

static int createTable(const char* b) {
    sqlite3* DB;
    string sql = "CREATE TABLE IF NOT EXISTS RIDER("
        "NUMBER     INT NOT NULL,"
        "PIN        INT NOT NULL, "
        "BALANCE    INT NOT NULL);";
    try {
        int exit = 0;
        exit = sqlite3_open(b, &DB);
        char* messageError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK) {
            cerr << "Error in creating table" << endl;
            sqlite3_free(messageError);
        }
        else {
            cout << "Table created successfully" << endl;
            sqlite3_close(DB);
        }
    }
    catch (const exception& e) {
        cerr << e.what();
    }
    return 0;
}

static int insertData(const char* c, long int a, int b) {
    sqlite3* DB;
    int databaseOpen;
    databaseOpen = sqlite3_open(c, &DB);
    if (databaseOpen) {
        cout << "error in opening database" << endl;
        return 0;
    }
    sqlite3_stmt* stmt;
    string sql = "INSERT INTO RIDER (NUMBER, PIN, BALANCE)"
        "VALUES(?, ?, 0);";
    databaseOpen = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    databaseOpen = sqlite3_bind_int(stmt, 1, a);
    databaseOpen = sqlite3_bind_int(stmt, 2, b);
    databaseOpen = sqlite3_step(stmt);
    if (databaseOpen != SQLITE_DONE) {
        cerr << "Error insert" << sqlite3_errmsg(DB) << endl;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    cout << "Data entered successfully" << endl;
    return 0;
}

static int selectData(const char* d) {
    sqlite3* DB;
    int exit = sqlite3_open(d, &DB);
    string sql = "SELECT * FROM RIDER;";
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
    return 0;
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ":" << argv[i] << endl;
    }
    return 0;
}