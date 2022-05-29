
#include <hostchecker.h>

Hostchecker::Hostchecker(std::string host, int port) : m_host(host), m_port(port)
{
}

Hostchecker::Hostchecker()
{
}

Hostchecker::~Hostchecker()
{
}

void Hostchecker::setHost(std::string host)
{
    m_host = host;
}

void Hostchecker::setPort(int port)
{
    m_port = port;
}

bool Hostchecker::alive()
{
    if (m_port > 0 && m_host.length() > 0)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            fprintf(stderr, "ERROR opening socket\n");
            return false;
        }
        server = gethostbyname(m_host.c_str());
        if (server == NULL)
        {
            fprintf(stderr, "ERROR, no such host\n");
            return false;
        }
        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(m_port);
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            close(sockfd);
            return false;
        }
        else
        {
            close(sockfd);
            return true;
        }
    }
    return false;
}
