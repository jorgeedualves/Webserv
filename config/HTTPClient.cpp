#include "HTTPClient.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>

void sendHttpRequest(const char* serverIP, int serverPort, const char* path) {
    // Criação do socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    // Configuração do endereço do servidor
    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) <= 0) {
        perror("Erro ao configurar o endereço do servidor");
        std::cerr << "Endereço IP inválido: " << serverIP << std::endl;
        exit(EXIT_FAILURE);
    }

    // Conexão com o servidor
    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        perror("Erro ao conectar ao servidor");
        exit(EXIT_FAILURE);
    }

    // Leitura do conteúdo do arquivo HTTPResponseViews.cpp
    std::ifstream file("Webserv/views/templates/index.html", std::ios::in | std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        perror("Erro ao abrir o arquivo index.html");
        exit(EXIT_FAILURE);
    }

    // Obtenha o tamanho do arquivo para alocar o buffer
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Aloque um buffer e leia o conteúdo do arquivo
    std::vector<char> fileBuffer(fileSize);
    if (!file.read(fileBuffer.data(), fileSize)) {
        perror("Erro ao ler o arquivo index.html");
        exit(EXIT_FAILURE);
    }

    // Envio da requisição HTTP com o conteúdo do arquivo no corpo
    std::ostringstream httpRequest;
    httpRequest << "GET " << path << " HTTP/1.1\r\n";
    httpRequest << "Host: " << serverIP << "\r\n";
    httpRequest << "Connection: close\r\n\r\n";

    if (send(clientSocket, httpRequest.str().c_str(), httpRequest.str().size(), 0) == -1) {
        perror("Erro ao enviar a requisição HTTP");
        exit(EXIT_FAILURE);
    }

    // Restante do código para receber e imprimir a resposta do servidor...
    const int bufferSize = 1024;
    char buffer[bufferSize];

    // Recebimento e impressão da resposta do servidor
    ssize_t bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, bufferSize - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';  // Adiciona um terminador nulo para imprimir como string
        std::cout << buffer;
    }

    if (bytesRead == -1) {
        perror("Erro ao receber a resposta do servidor");
        exit(EXIT_FAILURE);
    }

    // Fechamento do socket
    close(clientSocket);

}
