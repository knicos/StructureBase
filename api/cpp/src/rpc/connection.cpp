#include <dsb/rpc/connection.h>
#include <errno.h>
#include <fcntl.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>

dsb::rpc::Connection *dsb::rpc::Connection::connections_[dsb::rpc::Connection::MAX_CONNECTIONS];

int dsb::rpc::Connection::SetDescriptors(fd_set &fdread, fd_set &fderror) {
    int n = 0;
    
    //Set the file descriptors for each client
	for (int i=0; i<MAX_CONNECTIONS; i++) {
		if (connections_[i] && connections_[i]->Socket() >= 0) {
			if (connections_[i]->Socket() > n) {
				n = connections_[i]->Socket();
			}

			FD_SET(connections_[i]->Socket(), &fdread);
			FD_SET(connections_[i]->Socket(), &fderror);
		}
	}

	return n;
}

void dsb::rpc::Connection::CheckStatus(fd_set &fdread, fd_set &fderror) {
    //Also check each clients socket to see if any messages or errors are waiting
    for (int i=0; i<MAX_CONNECTIONS; i++) {
        if (connections_[i] && connections_[i]->Socket() >= 0) {
            //If message received from this client then deal with it
            if (FD_ISSET(connections_[i]->Socket(), &fdread)) {
                //connections_[i]->data();
            //An error occured with this client.
            } else if (FD_ISSET(connections_[i]->Socket(), &fderror)) {
                //connections_[i]->error();
            }
        }
    }
}

dsb::rpc::Connection::Connection(int socket)
 : socket_(socket) {
    int free = FindFree();
    connections_[free] = this;
}

dsb::rpc::Connection::Connection(const char *address, int port) {
    int free = FindFree();
    connections_[free] = this;
    Connect(address, port);
}


bool dsb::rpc::Connection::Connect(const char *address, int port) {
    int rc;
	sockaddr_in destAddr;

	//We want a TCP socket
	socket_ = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_ == INVALID_SOCKET) {
		return false;
	}

	hostent *host = gethostbyname(address);

	destAddr.sin_family = AF_INET;
	destAddr.sin_addr.s_addr = ((in_addr *)(host->h_addr))->s_addr;
	destAddr.sin_port = htons(port);

	rc = ::connect(socket_, (struct sockaddr*)&destAddr, sizeof(destAddr));

	if (rc == SOCKET_ERROR) {
		close(socket_);
        std::cout << "DSB: Unable to connect to server" << std::endl;
		return false;
	}

}

int dsb::rpc::Connection::FindFree() {
    for (int i=0; i<MAX_CONNECTIONS; ++i) {
        if (connections_[i] == 0) return i;   
    }
    return -1;
}

void dsb::rpc::Connection::Initialise() {
    for (int i=0; i<MAX_CONNECTIONS; ++i) {
        connections_[i] = 0;
    }
}

void dsb::rpc::Connection::Finalise() {
    //Delete all connections.
}
