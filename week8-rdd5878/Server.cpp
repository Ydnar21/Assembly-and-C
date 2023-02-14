#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int main(void)
{
    WSADATA wsadata;
    int iResult;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    //initialize WInSock DLL
    iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);

    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //Resolve serve address port
    ZeroMemory(&hints, sizeof(hints)); //memset(&hints, 0, sizeof(hits)); same thing
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;


    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);



    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    //Create new server socket

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    //bind
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
    freeaddrinfo(result);

    //Listen 
    iResult = listen(ListenSocket, SOMAXCONN); //max unsuccessful connection attempts

    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    //accept the client
    ClientSocket = accept(ListenSocket, NULL, NULL);

    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    iResult = closesocket(ListenSocket);


    //Recieve msg from client and send it back echo it
    char recvbuf[DEFAULT_BUFLEN];
    recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);
    if (iResult > 0)
    {
        printf("Bytes recieved: %d\n", iResult);
        printf("%s", recvbuf);
    }
    //send back to client
    int iSendResult = send(ClientSocket, recvbuf, iResult, 0);
    if (iSendResult == SOCKET_ERROR)
    {
        printf("recv failed");
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    else if (iResult == 0)
    {
        printf("Connection closing...\n");
    }
    else {
        printf("recv failed");
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    //shutdown
    iResult = shutdown(ClientSocket, SD_SEND);

    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    //Cleanup
    closesocket(ClientSocket);
    return 0;
}