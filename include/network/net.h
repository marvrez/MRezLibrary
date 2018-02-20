#ifndef NET_H
#define NET_H

#include <cstdint>
#include <cstring>
#include <cassert>

#ifdef _WIN32
#include <WinSock2.h>
#pragma comment(lib, "wsock32.lib")
#else
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#endif

constexpr int NET_MAX_ADDR = 68;

struct Address {
    enum class Type : uint8_t {
        IPv4,
        IPv6,
        count,
    };
    // represents full IP-address: ip0.ip1.ip2.ip3
    union {
        uint32_t ipv4;
        char ipv6[16];
    };
    uint16_t port;
    uint32_t scope_id;
    Type type;
};

class UDPSocket {
public:
    UDPSocket() = delete;

    // Opens a UDP socket and binds it to a specified port
    // (use 0 to select a random open port)
    //
    // Socket will not block if 'non-blocking' is non-zero
    UDPSocket(Address address, bool non_blocking, int address_family);
    UDPSocket(uint16_t port, bool non_blocking, int address_family);

    //Closes the opened socket
    ~UDPSocket();

    // Receives a specific amount of data from 'src'
    // If src is not null, src will contain its address and port.
    // Returns the number of bytes received
    int receive(void* data, size_t size, Address* src);

    // Sends a specific amount of data to 'dst'
    // Returns number of bytes sent.
    int send(const void* data, size_t size, Address dst);


    Address getSocket() const { return socket_; }

private:
    Address socket_;

    bool is_blocking_  = false;
    uint64_t socket_handle_ = 0;
};

UDPSocket::UDPSocket(Address address, bool non_blocking, int address_family) : socket_(address), is_blocking_(!non_blocking) {
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != NO_ERROR) {
        // Windows failure
        printf("Windows Sockets failedto start");
        assert(false);
    }
#endif

    socket_handle_ = socket(address_family, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_handle_ <= 0) {
        // Failed to create socket
        printf("Failed to create socket");
        assert(false);
    }

    // Bind socket to the port
    {
        addrinfo hints;
        memset(&hints, 0, sizeof(addrinfo));
        hints.ai_family = address_family;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
        hints.ai_protocol = IPPROTO_UDP;

        addrinfo* addr_list;

        char port_str[8] = {};
        sprintf(port_str, "%hu", address.port);
        if (getaddrinfo(nullptr, port_str, &hints, &addr_list) || !addr_list) {
            printf("getaddrinfo failed\n");
            assert(false);
        }
        {
            char buffer[NET_MAX_ADDR];
            uint16_t port;
            if (address_family == AF_INET) {
                sockaddr_in* addr = (sockaddr_in*)(addr_list->ai_addr);
                port = addr->sin_port;
                inet_ntop(AF_INET, &addr->sin_addr, buffer, NET_MAX_ADDR);
            }
            else { // ipv6
                sockaddr_in6* addr = (sockaddr_in6*)(addr_list->ai_addr);
                port = addr->sin6_port;
                inet_ntop(AF_INET6, &addr->sin6_addr, buffer, NET_MAX_ADDR);
            }
            printf("Binding to [%s]:%hu...\n", buffer, ntohs(port));
        }

        if (bind(socket_handle_, addr_list->ai_addr, int32_t(addr_list->ai_addrlen))) {
            printf("Bind failed\n");
            assert(false);
        }
        else
            printf("%s\n", "Bind succeeded.");

        freeaddrinfo(addr_list);
    }


    if (non_blocking) {
#ifdef _WIN32
        // Set port to not block when calling recv
        DWORD non_blocking = 1;
        if (ioctlsocket(socket_handle_, FIONBIO, &non_blocking) != 0) {
            // Failed to set port to non-blocking
            printf(""Failed to set socket to non-blocking\n");
            assert(false);
        }
#else
        int opt = 1;
        if (ioctl(socket_handle_, FIONBIO, &opt) == -1) {
            // Failed to set socket to non-blocking
            printf("Failed to set socket to non-blocking\n");
            assert(false);
        }
#endif
    }
}

UDPSocket::UDPSocket(uint16_t port, bool non_blocking, int address_family)
    : UDPSocket({{0}, port, 0, Address::Type::count}, non_blocking, address_family)
{
}

UDPSocket::~UDPSocket() {
#ifdef _WIN32
    WSACleanup();
#endif
}

int UDPSocket::receive(void* data, size_t size, Address* src) {
#ifdef _WIN32
    typedef int32_t socklen_t;
#endif

    sockaddr_storage from;
    socklen_t from_length = sizeof(sockaddr_storage);

    int32_t received_bytes = 0;
    if (socket_handle_)
        received_bytes = recvfrom(socket_handle_, (char*)data, size, 0,
                                  (sockaddr*)&from, &from_length);

    //still not received anything, check if ipv6 address has something
    if (received_bytes <= 0) {
        if (socket_handle_) {
            received_bytes = recvfrom(socket_handle_, (char*)data, size, 0,
                                      (sockaddr*)&from, &from_length);
            if (received_bytes <= 0) return 0;
        }
        else return 0;
    }

    if(src) {
        if (from.ss_family == AF_INET6) {
            src->type = Address::Type::IPv6;
            const sockaddr_in6* ipv6 = (const sockaddr_in6*)(&from);
            memcpy(src->ipv6, &ipv6->sin6_addr, sizeof(ipv6->sin6_addr));
            src->scope_id = ipv6->sin6_scope_id;
            src->port = ipv6->sin6_port;
        }
        else {
            src->type = Address::Type::IPv4;
            const sockaddr_in* ipv4 = (const sockaddr_in*)(&from);
            src->ipv4 = ipv4->sin_addr.s_addr;
            src->scope_id = 0;
            src->port = ipv4->sin_port;
        }
    }

    return received_bytes;
}

int UDPSocket::send(const void* data, size_t size, Address dst) {
    sockaddr_storage address;
    memset(&address, 0, sizeof(address));
    size_t addr_length = 0;
    switch (dst.type) {
        case Address::Type::IPv4:
        {
            sockaddr_in* ipv4 = (sockaddr_in*)(&address);
            ipv4->sin_family = AF_INET;
            ipv4->sin_port = dst.port;
            ipv4->sin_addr.s_addr = dst.ipv4;
            addr_length = sizeof(sockaddr_in);
            break;
        }
        case Address::Type::IPv6:
        {
            sockaddr_in6* ipv6 = (sockaddr_in6*)(&address);
            ipv6->sin6_family = AF_INET6;
            ipv6->sin6_port = dst.port;
            ipv6->sin6_scope_id = dst.scope_id;
            memcpy(&ipv6->sin6_addr, &dst.ipv6, sizeof(ipv6->sin6_addr));
            addr_length = sizeof(sockaddr_in6);
            break;
        }
        default:
            return 0;
            break;
    }

    size_t sent_bytes = 0;
    // do we actually have a socket open for the desired protocol?
    if (socket_handle_) {
        sent_bytes = sendto(socket_handle_, (const char*)data, size, 0,
                                    (const sockaddr*)&address, int32_t(addr_length));
        if (sent_bytes != size) {
            printf("Failed to send data\n");
            return 0;
        }
    }

    return sent_bytes;
}

#endif // NET_H

