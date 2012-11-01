#include "connection.h"

bool Connection::Initialise(unsigned short port) {
  port_ = port;
  
  sd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sd_ == INVALID_SOCKET) {
		std::cout << "DSBD::Server: Unable to open socket.\n";
		return false;
	}
	
	localAddr_.sin_family = AF_INET;
	localAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr_.sin_port = htons(port);

	int rc = bind(s_sd, (struct sockaddr*)&localAddr_, sizeof(localAddr_));
	if (rc == SOCKET_ERROR) {
		std::cout << "DSBD::Server: Unable to bind socket.\n";
		closesocket(sd_);
		return false;
	}

	//Attempt to start listening for connection requests.
	rc = ::listen(sd_, 1);
	if (rc == SOCKET_ERROR) {
		std::cout << "DSBD::Server: Unable to listen on socket.\n";
		closesocket(sd_);
		return false;
	}
	
	for (int i=0; i<MAX_CLIENTS; ++i) {
	  clients_[i] = 0;
	}

  initialised_ = true;
	return true;
}
