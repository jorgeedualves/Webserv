#ifndef REQUEST_CONTROLLER_HPP
#define REQUEST_CONTROLLER_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

class RequestController
{
public:
    RequestController();

    // Método para lidar com uma solicitação HTTP
    void handleRequest(const HTTPRequest& request, HTTPResponse& response);

private:
    // Manipulador para solicitações GET
    void handleGetRequest(const HTTPRequest& request, HTTPResponse& response);

    // Manipulador para solicitações POST
    void handlePostRequest(const HTTPRequest& request, HTTPResponse& response);

    // Manipulador para solicitações DELETE
    void handleDeleteRequest(const HTTPRequest& request, HTTPResponse& response);
};

#endif
