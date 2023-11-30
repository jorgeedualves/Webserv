// RequestController.cpp

#include "RequestController.hpp"

// Método para lidar com uma solicitação HTTP
void RequestController::handleRequest(const HTTPRequest& request, HTTPResponse& response)
{
    // Verifica o método HTTP (GET, POST, DELETE)
    std::string method = request.method();  
    std::string url = request.URL();        

    // Roteamento com base no método
    if (method == "GET")
    {
        handleGetRequest(request, response);
    }
    else if (method == "POST")
    {
        handlePostRequest(request, response);
    }
    else if (method == "DELETE")
    {
        handleDeleteRequest(request, response);
    }
    else
    {
        // Método não suportado
        response.setStatus(405);
        response.setBody("Method not allowed");
    }
}

// Manipulador para solicitações GET
void RequestController::handleGetRequest(const HTTPRequest&, HTTPResponse&)
{
    // Lógica para manipular solicitações GET
    // Pode incluir leitura de arquivos estáticos, geração dinâmica de conteúdo, etc.
}

// Manipulador para solicitações POST
void RequestController::handlePostRequest(const HTTPRequest&, HTTPResponse&)
{
    // Lógica para manipular solicitações POST
}

// Manipulador para solicitações DELETE
void RequestController::handleDeleteRequest(const HTTPRequest&, HTTPResponse&)
{
    // Lógica para manipular solicitações DELETE
}
