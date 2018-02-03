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

struct address_t {
    // represents full IP-address: ip0.ip1.ip2.ip3
    union {
        uint8_t ip0, ip1, ip2, ip3;
        uint8_t ip[4];
    };
    uint16_t port;
};

class UDPSocket {
public:
    UDPSocket() = delete;

    // Opens a UDP socket and binds it to a specified port
    // (use 0 to select a random open port)
    //
    // Socket will not block if 'non-blocking' is non-zero
    UDPSocket(address_t addr, bool non_blocking);
    UDPSocket(uint16_t port, bool non_blocking);

    //Closes the opened socket
    ~UDPSocket();

    // Receives a specific amount of data from 'src'
    // If src is not null, src will contain its address and port.
    // Returns the number of bytes received
    int receive(void* data, size_t size, address_t* src);

    // Sends a specific amount of data to 'dst'
    // Returns number of bytes sent.
    int send(const void* data, size_t size, address_t dst);


    address_t getSocket() const { return socket_; }

private:
    address_t socket_;

    bool is_blocking_  = 0;
    int socket_status_ = 0;
};

UDPSocket::UDPSocket(address_t addr, bool non_blocking) : socket_(addr), is_blocking_(!non_blocking) {
#ifdef _WIN32
    WSADATA WsaData;
    if (WSAStartup(MAKEWORD(2, 2), &WsaData) != NO_ERROR) {
        // Windows failure
        assert(false);
    }

    socket_status_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_status_ <= 0) {
        // Failed to create socket
        UDP_ASSERT(false);
    }

    // Bind socket to a port
    sockaddr_in address;
    address.sin_family = AF_INET;
    if (addr.ip0 == 0 &&
        addr.ip1 == 0 &&
        addr.ip2 == 0 &&
        addr.ip3 == 0)
        address.sin_addr.s_addr = INADDR_ANY;
    else
        address.sin_addr.s_addr = htonl(
        (addr.ip0 << 24) |
        (addr.ip1 << 16) |
        (addr.ip2 <<  8) |
        (addr.ip3));
    address.sin_port = htons(addr.port);
    if (bind(socket_status_, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0) {
        // Failed to bind socket (maybe port was taken?)
        assert(false);
    }

    if (non_blocking) {
        // Set port to not block when calling recvfrom
        DWORD non_blocking = 1;
        if (ioctlsocket(socket_status_, FIONBIO, &non_blocking) != 0) {
            // Failed to set port to non-blocking
            assert(false);
        }
    }
#else
    socket_status_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_status_ < 0) {
        // Failed to open socket
        assert(false);
    }

    sockaddr_in address = {};
    address.sin_family = AF_INET;
    if (addr.ip0 == 0 &&
        addr.ip1 == 0 &&
        addr.ip2 == 0 &&
        addr.ip3 == 0)
        address.sin_addr.s_addr = INADDR_ANY;
    else
        address.sin_addr.s_addr = htonl(
        (addr.ip0 << 24) |
        (addr.ip1 << 16) |
        (addr.ip2 <<  8) |
        (addr.ip3));
    address.sin_port = htons(addr.port);

    if (bind(socket_status_, (sockaddr*)&address, sizeof(address)) < 0) {
        // Failed to bind socket
        assert(false);
    }

    if (non_blocking) {
        int opt = 1;
        if (ioctl(socket_status_, FIONBIO, &opt) == -1) {
            // Failed to set socket to non-blocking
            assert(false);
        }
    }
#endif
}

UDPSocket::UDPSocket(uint16_t port, bool non_blocking)
    : UDPSocket({{0}, port}, non_blocking)
{
}

UDPSocket::~UDPSocket() {
#ifdef _WIN32
    WSACleanup();
#endif
}

#endif // NET_H

