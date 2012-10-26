#ifndef _DSBD_CONNECTION_H_
#define _DSBD_CONNECTION_H_

namespace dsbd {
class Connection {
	public:
	static bool Initialise(unsigned short port);
	static bool Listen();
	
	static const unsigned int MAX_CLIENTS = 50;
	
	private:
	static bool AcceptConnections();
	static int SetDescriptors();
	static int FindFree();
	
	static unsigned short port_;
	static dsbd::Connection *connections_[dsbd::Server::MAX_CLIENTS];
	static bool initialised_;
	static int sd_;
	static fd_set fdread_;
	static fd_set fderror_;
	static sockaddr_in localAddr_;
};
};

#endif
