#include <iostream>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main(){
    //Strartup Winsock
    WSAData data;
    WORD version = MAKEWORD(2, 2);
    int wsResult = WSAStartup(version, &data);
    if(wsResult != 0) {
        std::cerr << "Can't Startup Winsock! Error Code: " << wsResult << std::endl;
        return -1;
    }

    //Socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == INVALID_SOCKET) {
        std::cerr << "Unable to create socket! Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    //Bind socket to address and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&hint, sizeof(hint));

    //Listen for connections
    listen(serverSocket, SOMAXCONN);

    //Accept new connection 
    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&client, &clientSize);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        std::cout << host << "Connecting on port: " << service << std::endl;
    } else {
        inet_ntop (AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << "Connecting on port: " << ntohs(client.sin_port) << std::endl;
    }

    //Close Socket
    closesocket(serverSocket);

    //receiver and send data
    char buf[4096];
    while(true){
        ZeroMemory(buf, 4096);

        //Receiver data
        int bytesReceived = recv(clientSocket, buf,  4096, 0);
        if(bytesReceived == SOCKET_ERROR) {
            std::cerr << "Error while receiving data! Error code: " << WSAGetLastError() << std::endl;
            break;
        }

        if(bytesReceived == 0) {
            std::cout << "The client has closed the connection." << std::endl;
            break;
        }

        std::cout << "Client: " << std::string(buf, 0, bytesReceived) << std::endl;

        //Send data back to for client
        send(clientSocket, buf, bytesReceived + 1, 0);
    } 

    //Close socket
    closesocket(clientSocket);

    //Cleanup Winsock
    WSACleanup();

    return 0;
}