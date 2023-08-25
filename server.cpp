#include <iostream>
#include <cstring>
#include <cstdlib>
#include <Winsock2.h>
#include <process.h>

const int PORT = 12345;
const int MAX_CONNECTIONS = 10;
const int BUFFER_SIZE = 1024;

void handleClient(void* arg) {
    SOCKET clientSocket = (SOCKET)arg;

    while (true) {
        char buffer[BUFFER_SIZE];
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            break;
        }

        std::cout << "Recebido: " << buffer << std::endl;

        std::string response = "Servico prestado pela thread_" + std::to_string(GetCurrentThreadId());
        send(clientSocket, response.c_str(), response.size() + 1, 0);
    }

    closesocket(clientSocket);
    _endthread();
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erro ao inicializar o Winsock." << std::endl;
        return 1;
    }

    SOCKET serverSocket;
    sockaddr_in serverAddr;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erro ao criar o socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erro no bind." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen
    if (listen(serverSocket, MAX_CONNECTIONS) == SOCKET_ERROR) {
        std::cerr << "Erro ao ouvir conexoes." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Servidor esperando por conexoes na porta " << PORT << std::endl;

    // Accept and handle connections
    while (true) {
        sockaddr_in clientAddr;
        int clientAddrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Erro ao aceitar conexao." << std::endl;
            continue;
        }

        _beginthread(handleClient, 0, (void*)clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
