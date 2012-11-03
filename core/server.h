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
            Server(int port) : port_(port), listening_(false) {
                server_ = this;
            };
            ~Server() {};

            bool Listen();
            
            int SetDescriptors(fd_set &fdread, fd_set &fderror);
            void CheckStatus(fd_set &fdread, fd_set &fderror);
            
            static Server *GetServer() { return server_; };

        private:
            bool AcceptConnections();
    
            int port_;
            bool listening_;
            int sd_;
            sockaddr_in localAddr_;
            
            static Server *server_;
        };
    };
};

#endif	/* SERVER_H */

