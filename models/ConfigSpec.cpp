
#include "ConfigSpec.hpp"

ConfigSpec::ConfigSpec(int port, const std::string& serverName)
    : m_serverName(serverName), m_port(port)
{
}

int ConfigSpec::getPort() const
{
    return m_port;
}

std::string ConfigSpec::getServerName() const
{
    return m_serverName;
}

std::string ConfigSpec::getHostName() const
{
    return m_host;
}

int ConfigSpec::getBodySizeLimit() const
{
    return m_limitBodySize;
}
