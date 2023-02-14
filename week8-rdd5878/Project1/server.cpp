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

DWORD WINAPI myThread(LPVOID lpParameter)
{
    unsigned int& myCounter = *((unsigned int*)lpParameter);
    while (myCounter < 0xFFFFFFFF) {
        ++myCounter;
    }
    return 0;
}
int isNumber(char *input) {
    int length, i;
    length = strlen(input)-1;
    for (i = 0; i < length; i++)
        if (!isdigit(input[i]))
        {
            if (i == 1) {
                continue;
            }
            else {

                printf("Entered input is not a number\n");
                return 0;
            }
            
        }
    return 1;
}int *number(char *fakenum) {
    int *realnumber = (int*)malloc(sizeof(int*));;
    sscanf_s(fakenum, "%d", &realnumber);
    return realnumber;
}

int isword(char *recvbuff) {
    int length, i;
    length = strlen(recvbuff) - 1;
    for (i = 0; i < length; i++)
        if (!isalpha(recvbuff[i]))
        {

                printf("\nEntered a string with 1 or more non letters");
                return 0;


        }

}
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
    HANDLE hThread;
    DWORD dwThreadId;
    unsigned int myCounter = 0;
    hThread = CreateThread(NULL, 0, myThread, &myCounter, 0, &dwThreadId);
    printf("Thank you for connecting client %d\n", myCounter); //add ID number here

    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    


    //Recieve msg from client asnd send it back echo it
    char recvbuf[DEFAULT_BUFLEN];
    send(ClientSocket, "Thank you for connecting\n", DEFAULT_BUFLEN, 0);
    ZeroMemory(recvbuf, DEFAULT_BUFLEN);
    iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);

    if (iResult > 0)
    {

        if (strcmp(recvbuf, "quit\n") == 0)
        {
            printf("Client closed the connection with input\n");
            closesocket(ClientSocket);
            WSACleanup();
            exit(0);
        }
        else
        {
            printf("%s", recvbuf);
        }


        if (isNumber(recvbuf)) {
            int* realnumber = (int*)malloc(sizeof(int*));
            char* msg = (char*)malloc(DEFAULT_BUFLEN);
            
            realnumber = number(recvbuf);
            //sscanf_s(recvbuf, "%d", &x);
            int x = (int)realnumber;
            sprintf_s(msg, 300, "%d %d %d %d %d %d %d %d %d %d %d", x,  x+1, x + 2, x + 3, x + 4, x + 5, x + 6, x + 7, x + 8, x + 9, x + 10);



            //sprintf_s   sscanf_s
            send(ClientSocket, msg, DEFAULT_BUFLEN, 0);

        }

        if (isword(recvbuf))
        {
            char *msg= (char*)malloc(DEFAULT_BUFLEN);
            
                sprintf_s(msg ,DEFAULT_BUFLEN, "%s %s %s %s %s %s %s %s %s %s", recvbuf, recvbuf,recvbuf,recvbuf,recvbuf,recvbuf,recvbuf, recvbuf, recvbuf, recvbuf);
            
            send(ClientSocket, msg, DEFAULT_BUFLEN, 0);
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
    printf("Made it");
    closesocket(ClientSocket);
    return 0;
}

   
