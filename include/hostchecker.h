
#ifndef HOST_CHECKER_H
#define HOST_CHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// void bzero(void *s, size_t n);
#define bzero(s, n) memset((s), 0, (n))

// void bcopy(const void *s1, void *s2, size_t n);
#define bcopy(s1, s2, n) memmove((s2), (s1), (n))

/**
 * @brief Check if host alive on specific port
 *
 */
class Hostchecker
{
public:
    explicit Hostchecker(std::string host, int port);
    Hostchecker();
    virtual ~Hostchecker();
    void setHost(std::string host);
    void setPort(int port);
    bool alive();

private:
    std::string m_host;
    int m_port;
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
};

#endif