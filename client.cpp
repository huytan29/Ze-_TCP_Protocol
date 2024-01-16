#include <iostream>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main(){
    //Startup Winsock
    WSAData data;
    WORD version = MAKEWORD(2 ,2);
    int wsResult = WSAStartup(version, &data);
    if(wsResult != 0) {
        std::cerr << "Unable to initialize Winsock! Error code: " << wsResult << std::endl;
        return -1;
    }
    

    //Create Socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == INVALID_SOCKET) {
        std::cerr << "Unable to create socket! Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    //Connect to Server
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

    int connResult = connect(clientSocket, (sockaddr*)&hint, sizeof(hint));
    if(connResult == SOCKET_ERROR) {
        std::cerr << "Unable to connect to server! Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    //Input and send data
    char buf[4096];
    std::string userInput;

    do {
        std::cout << "> ";
        std::getline(std::cin, userInput);

        if(userInput.size() > 0) {
            int sendResult = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
            if(sendResult != SOCKET_ERROR) {
                ZeroMemory(buf, 4096);
                int bytesReceived = recv(clientSocket, buf, 4096, 0);
                if(bytesReceived > 0) {
                    std::cout << "Server: " << std::string(buf, 0, bytesReceived) << std::endl;
                }
            }
        }
    } while(userInput.size() > 0);

    //Close socket
    closesocket(clientSocket);

    //Cleanup Winsocket
    WSACleanup();

    return 0;

}