// #include <iostream>
// #include <cstring>
// #include <cstdlib>
// #include <cstdio>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>
// #include <err.h>
// #include <arpa/inet.h>


// int main() {
//     // Configurações do servidor
//     const char* serverIP = "localhost";
//     const int serverPort = 8080;

//     // Criação do socket
//     int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (clientSocket == -1) {
//         perror("Erro ao criar o socket");
//         exit(EXIT_FAILURE);
//     }

//     // Configuração do endereço do servidor
//     sockaddr_in serverAddress;
//     memset(&serverAddress, 0, sizeof(serverAddress));
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_port = htons(serverPort);
//     if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) <= 0) {
//         perror("Erro ao configurar o endereço do servidor");
//         exit(EXIT_FAILURE);
//     }

//     // Conexão com o servidor
//     if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
//         perror("Erro ao conectar ao servidor");
//         exit(EXIT_FAILURE);
//     }

//     // Envio da requisição HTTP
//     const char* httpRequest = "GET /path/to/resource HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
//     if (send(clientSocket, httpRequest, strlen(httpRequest), 0) == -1) {
//         perror("Erro ao enviar a requisição HTTP");
//         exit(EXIT_FAILURE);
//     }

//     // Recebimento e impressão da resposta do servidor
//     char buffer[BUFSIZ];
//     int bytesRead;
//     while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
//         std::cout.write(buffer, bytesRead);
//     }

//     // Fechamento do socket
//     close(clientSocket);

//     return 0;
// }

// main.cpp

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

#include "Connection.hpp"
#include "Dispatcher.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPResponseViews.hpp"
#include "Server.hpp"
#include "EventListener.hpp"
#include "ConfigSpec.hpp"
#include "HTTPClient.hpp"

int main() {
    EventListener listener;

    ConfigSpec config(8080, "TestServer1");
    Server server(config);
    listener.subscribe(&server);

    ConfigSpec config2(8081, "TestServer2");
    Server server2(config2);
    listener.subscribe(&server2);

    listener.start();

    // Exemplo de uso da função sendHttpRequest
    sendHttpRequest("localhost", 8080, "/path/to/resource");

    return 0;
}
