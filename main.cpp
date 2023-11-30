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

    // Exemplo de uso da função sendHttpRequest
    sendHttpRequest("localhost", 8080, "/path/to/resource");

    listener.start();

    

    return 0;
}
