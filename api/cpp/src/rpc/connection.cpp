#include <dsb/rpc/connection.h>
#include <dsb/rpc/handlers.h>
#include <dsb/nid.h>
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
#include <stdarg.h>
#include <memory.h>

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
            std::cout << "Found connection to check\n";
            //If message received from this client then deal with it
            if (FD_ISSET(connections_[i]->Socket(), &fdread)) {
                connections_[i]->Data();
            //An error occured with this client.
            } else if (FD_ISSET(connections_[i]->Socket(), &fderror)) {
                connections_[i]->Error();
            }
        }
    }
}

dsb::rpc::Connection::Connection(int socket)
 : socket_(socket), outposition_(sizeof(unsigned short)) {
    int free = FindFree();
    connections_[free] = this;
    //in_nid_array_ = new dsb::NID[MAX_NID_PARAMS];
}

dsb::rpc::Connection::Connection(const char *address, int port)
 : outposition_(sizeof(unsigned short)) {
    int free = FindFree();
    connections_[free] = this;
    //in_nid_array_ = new dsb::NID[MAX_NID_PARAMS];
    Connect(address, port);
}

dsb::rpc::Connection::~Connection() {
    Close();
    //delete [] in_nid_array_;
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
        socket_ = INVALID_SOCKET;
        std::cout << "DSB: Unable to connect to server" << std::endl;
		return false;
	}
    
    std::cout << "DSB: Connected to " << address << std::endl;
    return true;
}

void dsb::rpc::Connection::Close() {
    if (socket_ != INVALID_SOCKET) {
        close(socket_);
        socket_ = INVALID_SOCKET;
    }
}

bool dsb::rpc::Connection::Send(dsb::request_t request, dsb::NID *params) {
    dsb::NID *output;
    
    //if (socket_ == INVALID_SOCKET) return false;
    
    //Put the request type into the buffer
    outbuffer_[outposition_++] = static_cast<unsigned char>(request);
    
    //Put the expected number of parameters into the buffer
    int pcount = dsb::requests[request].params;
    output = reinterpret_cast<dsb::NID*>(&(outbuffer_[outposition_]));
    outposition_ += pcount*sizeof(dsb::NID);
    
    memcpy(output, params, sizeof(dsb::NID)*pcount);
    
    //for (int i=0; i<pcount; ++i) {
    //    *output = nid;
    //    ++output;
    //}
    
    //For now, flush immediately.
    //Better eventually to fill buffer and compress it.
    Flush();
    return true;
}

void dsb::rpc::Connection::Flush() {
    if (socket_ == INVALID_SOCKET) return;
    
    //TODO: COMPRESS HERE

    //Insert the packet size.
    reinterpret_cast<unsigned short*>(&outbuffer_[0])[0] = outposition_;
    
    if (::send(socket_, outbuffer_, outposition_,0) != outposition_) {
		std::cout << "Unable to send data... probably disconnected\n";
        Close();
	}

    outposition_ = sizeof(unsigned short);
}

void dsb::rpc::Connection::Data() {
    //Read and process data.
    std::cout << "Some Data\n";
    int rc = 0;
    
	rc = recv(socket_, (char*)inbuffer_, BUFFER_SIZE, 0);
    
    if (rc <= 0) {
        std::cout << "DSB: Disconnected." << std::endl;
        Close();
        return;
    }
    
    unsigned short length = reinterpret_cast<unsigned short*>(inbuffer_)[0];
    if (rc < length) {
        std::cout << "DSB: Less than expected data";
        return;
    }
    
    //DECOMPRESS
    
    inposition_ = sizeof(unsigned short);
    dsb::request_t request;
    while (inposition_ < length) {
        request = static_cast<dsb::request_t>(inbuffer_[inposition_++]);
        
        //NOW PROCESS THIS REQUEST!!
        std::cout << "DSB: Request - " << dsb::requests[request].name << std::endl;
        dsb::rpc::Handlers::Call(request, this,reinterpret_cast<dsb::NID*>(&(inbuffer_[inposition_])));
        
        inposition_ += dsb::requests[request].params*sizeof(dsb::NID);
    }
}

void dsb::rpc::Connection::Error() {
    //find out what the error was.
    std::cout << "DSB: Connection Error." << std::endl;
    Close();
}

int dsb::rpc::Connection::FindFree() {
    for (int i=0; i<MAX_CONNECTIONS; ++i) {
        if (connections_[i] == 0) return i;   
    }
    return -1;
}

dsb::rpc::Connection *dsb::rpc::Connection::FindBest() {
    for (int i=0; i<MAX_CONNECTIONS; ++i) {
        if (connections_[i] != 0) return connections_[i];   
    }
    return 0;
}

void dsb::rpc::Connection::Initialise() {
    for (int i=0; i<MAX_CONNECTIONS; ++i) {
        connections_[i] = 0;
    }
}

void dsb::rpc::Connection::Finalise() {
    //Delete all connections.
    for (int i=0; i<MAX_CONNECTIONS; ++i) {
        if (connections_[i]) delete connections_[i];
    }
}
