#include "server.h"
#include <iostream>
#include <dsb/rpc/connection.h>

#include <errno.h>
#include <fcntl.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

dsbd::rpc::Server *dsbd::rpc::Server::server_ = 0;

bool dsbd::rpc::Server::Listen() {
    sd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sd_ == INVALID_SOCKET) {
            std::cout << "DSBD::Server: Unable to open socket.\n";
            return false;
    }

    localAddr_.sin_family = AF_INET;
    localAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr_.sin_port = htons(port_);

    int rc = bind(sd_, (struct sockaddr*)&localAddr_, sizeof(localAddr_));
    if (rc == SOCKET_ERROR) {
            std::cout << "DSBD::Server: Unable to bind socket.\n";
            close(sd_);
            return false;
    }

    //Attempt to start listening for connection requests.
    rc = ::listen(sd_, 1);
    if (rc == SOCKET_ERROR) {
            std::cout << "DSBD::Server: Unable to listen on socket.\n";
            close(sd_);
            return false;
    }

    listening_ = true;
    
    std::cout << "DSBD: Server listening on port " << port_ << std::endl;
    
    return true;
};

bool dsbd::rpc::Server::AcceptConnections() {
    int rsize = sizeof(sockaddr_in);
	sockaddr_in remoteAddr;

	//Finally accept this client connection.
	int csock = accept(sd_, (sockaddr*)&remoteAddr, (socklen_t*)&rsize);

	if (csock == INVALID_SOCKET) {
		return false;
	}

	dsb::rpc::Connection *newcon = new dsb::rpc::Connection(csock);
    
	//strcpy(newcon->m_addr, inet_ntoa(remoteAddr.sin_addr));
    std::cout << "DSBD: Client connected - " << inet_ntoa(remoteAddr.sin_addr) << std::endl;

	return true;
}

void dsbd::rpc::Server::CheckStatus(fd_set &fdread, fd_set &fderror) {
    if (FD_ISSET(sd_, &fdread)) {
        if (!AcceptConnections()) {
            return;
        }
    }
}

int dsbd::rpc::Server::SetDescriptors(fd_set &fdread, fd_set &fderror) {
    //Reset all file descriptors
	//FD_ZERO(&fdread);
	//FD_ZERO(&fderror);

	int n = 0;

	//Set file descriptor for the listening socket.
    FD_SET(sd_, &fdread);
	FD_SET(sd_, &fderror);
	n = sd_;

	return n;
}
