#include <iostream>
#include <cstring>
#include <cstdlib>
#include <Winsock2.h>

const int PORT = 12345;
const char* SERVER_IP = "127.0.0.1";
const int BUFFER_SIZE = 1024;

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erro ao inicializar o Winsock." << std::endl;
        return 1;
    }

    SOCKET clientSocket;
    sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erro ao criar o socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erro ao conectar ao servidor." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    while (true) {
        std::cout << "Digite a sua requisicao (ou 'exit' para sair): ";
        std::string request;
        std::getline(std::cin, request);

        if (request == "exit") {
            break;
        }

        send(clientSocket, request.c_str(), request.size() + 1, 0);

        char buffer[BUFFER_SIZE];
        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        std::cout << "Resposta do servidor: " << buffer << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
