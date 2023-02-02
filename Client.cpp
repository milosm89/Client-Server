#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <iostream>
using namespace std;

int main() {

	cout << "Step - 1 Set up DLL" << endl;
	SOCKET clientSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaerr != 0)
	{
		cout << "The WinSock DLL not found" << endl;
		return 0;
	}
	else
	{
		cout << "The WinSock DLL fount" << endl;
	}
	cout << "Step - 2 Set up Socket" << endl;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Error at socket() " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "Socket is Ok!" << endl;
	}
	cout << "Step - 3 Set up Connection" << endl;
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(55555);
	int result = connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (result == SOCKET_ERROR)
	{
		cout << "Connection not established " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "Client: connect() is ok!" << endl;
		cout << "Client: Can start sending and receiving data..." << endl;
	}
	cout << "Step - 4 Caht to the Server" << endl;
	cout << "Press \"#\" if you want to exit the chat!" << endl;

	do
	{
		int byteCount;
		char buffer[200], recvbuffer[200];
		cout << "Please eneter the message to sent to the server" << endl;
		byteCount = send(clientSocket, buffer, 200, 0);
		if (byteCount > 0 && *buffer != '#')
		{
			cout << "Message sent to Server: " << buffer << endl;
		}
		else
		{
			WSACleanup();
			break;
		}

		byteCount = recv(clientSocket, recvbuffer, 200, 0);
		if (byteCount > 0 && *recvbuffer != '#')
		{
			cout << "Message received from Server: " << recvbuffer << endl;
		}
		else
		{
			WSACleanup();
			break;
		}
	} while (true);
	cout << "Connection terminated: from IP \"127.0.0.1\" " << endl;
	system("pause");
	closesocket(clientSocket);
	WSACleanup();
}