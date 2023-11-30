#include <fstream>
#include <sstream>

#include "Connection.hpp"
#include "HTTPResponseViews.hpp"

// Inicialize a classe base no construtor usando a lista de inicialização
HTTPResponseViews::HTTPResponseViews(Connection* conn) : HTTPResponse(conn) {
    // Inicialize o membro connection da classe derivada
    connection = conn;

    // Outras inicializações, se necessário
}

void HTTPResponseViews::showResponse() const {
    // ... (restante do código)
}

