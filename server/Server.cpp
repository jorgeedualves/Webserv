#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Server.hpp"
#include "Connection.hpp"
#include "ConfigSpec.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

const int BACKLOG = 10;

Server::Server(const ConfigSpec& cfg)
    : m_name(cfg.getServerName()),
      m_host(cfg.getHostName()),
      m_port(cfg.getPort()),
      m_socket(createSocket()),
      m_config(cfg)
{
}

Server::~Server()
{
    close(m_socket);
}

void Server::listen()
{
    if (::listen(m_socket, BACKLOG) == -1)
    {
        close(m_socket);
        fatalError("Error while listening");
    }
}

int Server::accept()
{
    return ::accept(m_socket, NULL, NULL);
}

bool Server::read(Connection* conn)
{
    HTTPRequest* request = conn->request();
    std::cout << "Received: " << request->method() << std::endl;
    std::cout << "Host: " << request->get("Host") << std::endl;
    std::cout << "User-Agent: " << request->get("User-Agent") << std::endl;
    return true;
}

bool Server::write(Connection* conn) {
    HTTPResponse* response = conn->response();

    std::ifstream file("views/templates/index.html");
    if (!file.is_open()) {
        perror("Erro ao abrir o arquivo index.html");
        response->setStatus(500);
        response->set("Content-Type", "text/plain");
        response->setBody("Erro interno do servidor");
        return false;
    }

    std::ostringstream content;
    content << file.rdbuf();
    file.close();

    response->setStatus(200);
    response->set("Content-Type", "text/html");
    response->setBody(content.str());

    return true;
}

int Server::getSocket() const
{
    return m_socket;
}

int Server::createSocket()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        fatalError("Error creating socket");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    int yes = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        close(fd);
        fatalError("Error during socket initialization");
    }

    return fd;
}

void fatalError(const std::string& errMsg)
{
    std::cerr << errMsg << ": " << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
}
