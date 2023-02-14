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
    WSADATA wsaData;
    struct addinfo* result = NULL;
    struct addrinfo hints;
    int iResult;

    SOCKET ClientSocket = INVALID_SOCKET;

    //Initialize Winsock DLL
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //Get address info
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(arg[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    //Create socket connection
    ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    if (iResult == SOCKET_ERROR)
    {
        printf("connect failed with error: %d\n", WSAgetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    FreeAddrInfo(result);
    char sendbuf[] = "Hello Server, this is the client.";
    send(ConnectSocket, sendbuf, strlen(sendbuf));

    


    
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    
    printf("Bytes sent: %d\n", iResult);
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