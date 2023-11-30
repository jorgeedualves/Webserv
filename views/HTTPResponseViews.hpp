#ifndef HTTPRESPONSEVIEWS_HPP
#define HTTPRESPONSEVIEWS_HPP

#include "HTTPResponse.hpp"
#include "Connection.hpp"

class HTTPResponseViews : public HTTPResponse {
public:
    HTTPResponseViews(Connection* conn);
    ~HTTPResponseViews();

    void showResponse() const;

private:
    // Mude a declaração para refletir a herança
    Connection* connection;
};

#endif // HTTPRESPONSEVIEWS_HPP
