/* 
 * File:   server.h
 * Author: nick
 *
 * Created on 02 November 2012, 19:21
 */

#ifndef SERVER_H
#define	SERVER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace dsbd {
    namespace rpc {
        class Server {
        public:
            Server(int port) : port_(port), listening_(false) {};
            ~Server();

            bool Listen();

        private:
            bool AcceptConnections();
            int SetDescriptors();
    
            int port_;
            bool listening_;
            int sd_;
            fd_set fdread_;
            fd_set fderror_;
            sockaddr_in localAddr_;
        };
    };
};

#endif	/* SERVER_H */

