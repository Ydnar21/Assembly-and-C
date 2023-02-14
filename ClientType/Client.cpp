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
int main(int argc, char** argv)
{
    WSADATA wsadata;
    int iResult;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    SOCKET ConnectSocket = INVALID_SOCKET;

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


    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);



    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        printf("connect failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);
    char sendbuf[DEFAULT_BUFLEN];
    printf("Enter either a word or a number here: ");
    fgets(sendbuf, DEFAULT_BUFLEN, stdin);
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);

    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes sent: %d\n", iResult);
    char recvbuf[DEFAULT_BUFLEN];
    recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
    printf("%s", recvbuf);
    char newer[DEFAULT_BUFLEN];

    recv(ConnectSocket, newer, DEFAULT_BUFLEN, 0);
    printf("%s\n", newer);
    iResult = shutdown(ConnectSocket, SD_SEND);

    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    closesocket(ConnectSocket);
    WSACleanup();


    return 0;
   
}