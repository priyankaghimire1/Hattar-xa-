#include<winsock2.h>
#include<ws2tcpip.h>
#include"iostream"
#include <atlbase.h>
using namespace std;
int main(int argc, char* agrv[]) {
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
		cout << "The winsock dll found" << endl;
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
		cout << "Client: Can start sending and recieving data..." << endl;
	}
	cout << "\n=== STEP to chat with the server===\n\n" << endl;
	char buffer[200];
	cout << "Please enter the destination and the location to send to the rider:" << endl;
	cin.getline(buffer, 200);
	int byteCount=send(clientSocket, buffer, 200, 0);
	if (byteCount > 0) {
		cout << "Message sent: " << buffer << endl;
	}
	else {
		WSACleanup();
	}
	byteCount = recv(clientSocket, buffer, 200, 0);
	if(byteCount > 0) {
		cout << "Message received: " << buffer << endl;
	}
	else {
		WSACleanup();
	}
	cout << "\n=== Step to close the Socket=== \n\n\n" << endl;
	system("pause");
	WSACleanup();
	return 0;
}