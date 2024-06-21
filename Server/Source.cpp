#include<winsock2.h>
#include<ws2tcpip.h>
#include"iostream"
#include <atlbase.h>
using namespace std;
int main(int argc, char* agrv[]) {
	SOCKET serverSocket, acceptSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout<< "The Winsock dll not found" << endl;
		return 0;
	}
	else {
		cout << "The winsock dll found" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is ok!" << endl;
	}
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else{
		cout << "bind() is ok!" << endl;

	}
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		cout << "listen(): Error listening on socket" << WSAGetLastError()<<endl;
	}
	else {
		cout << "listen() is OK, I'm waiting for connections..." << endl;
	}
	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		cout << "accept failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Accepted connection" << endl;
	cout << "\n=== STEP to chat with the client===\n\n" << endl;
	char buffer[200];
	int byteCount = recv(acceptSocket, buffer, 200, 0);
	if (byteCount > 0) {
		cout << "Message recieved: " << buffer << endl;
	}
	else {
		WSACleanup();
	}
	char confirmation[200] = "Message recieved";
	byteCount=send(acceptSocket, confirmation, 200, 0);
	if (byteCount > 0) {
		cout << " Automated message sent to the client." << endl;
	}
	else {
		WSACleanup();
	}
	cout << "\n=== Step to close the Socket=== \n\n\n" << endl;
	system("pause");
	WSACleanup();
	return 0;
 }

