// RequestController.hpp

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
    // Métodos específicos para manipular cada tipo de solicitação
    void handleGetRequest(const HTTPRequest& request, HTTPResponse& response);
    void handlePostRequest(const HTTPRequest& request, HTTPResponse& response);
    void handleDeleteRequest(const HTTPRequest& request, HTTPResponse& response);
};

#endif
