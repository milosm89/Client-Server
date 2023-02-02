#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <iostream>
using namespace std;

int main()
{
    cout << "========SERVER==========" << endl;
    cout << "Step 1 - Set up DLL" << endl;
    SOCKET serverSocket, acceptSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    wsaerr = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (wsaerr != 0)
    {
        cout << "The WinSock dll not found" << endl;
        return 0;
    }
    else
    {
        cout << "The Win Sock dll found" << endl;
        cout << "The Status: " << wsaData.szSystemStatus << endl;
    }
    cout << "Step 2 - Set up Server Socket" << endl;
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "Socket is OK!" << endl;
    }
    cout << "Step 3 - Bind Socket" << endl;
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "bind() is OK!" << endl;
    }
    cout << "Step 4 - Initiate Listen" << endl;
    if (listen(serverSocket, 1) == SOCKET_ERROR)
    {
        cout << "listen(): Error listening on Socket " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "Listen is OK, I'm waiting for connections..." << endl;
    }
    cout << "Step 5 - Accept Connection" << endl;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "accept() failed " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    cout << "Accepted connection " << endl;
    cout << "Step 6 - Chat to the client" << endl;
    cout << "Press \"#\" if you want to exit the chat!" << endl;
    do
    {
        char buffer[200];
        int byteCount = recv(acceptSocket, buffer, 200, 0);
        if (byteCount > 0 && *buffer != '#')
        {
            cout << "Message received from Client: " << buffer<< endl;
        }
        else
        {
            WSACleanup();
            break;
        }

        char confirmation[200];
        cout << "Please eneter the message to sent to the client " << endl;
        cin.getline(confirmation, 200);
        byteCount = send(acceptSocket, confirmation, 200, 0);
        if (byteCount > 0 && *confirmation != '#')
        {
            cout << "Message sent to client: " << endl;
        }
        else
        {
            WSACleanup();
	    break;
        }

    } while (true);
    cout << "Connection terminated: from IP \"127.0.0.1\" " << endl;
    system("pause");
    closesocket(serverSocket);
    WSACleanup();
  
}
