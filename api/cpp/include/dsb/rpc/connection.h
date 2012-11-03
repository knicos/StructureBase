#ifndef _DSB_CONNECTION_H_
#define _DSB_CONNECTION_H_

#include <unistd.h>
#include <sys/types.h>

namespace dsb {
    namespace rpc {
        class Connection {
        public:
            Connection(int socket);
            Connection(const char *address, int port);
            ~Connection();

            int Socket() { return socket_; };
            bool Connect(const char *address, int port);
            void Close();
            
            static void Initialise();
            static void Finalise();
            
            static Connection *FindBest();
            static int SetDescriptors(fd_set &fdread, fd_set &fderror);
            static void CheckStatus(fd_set &fdread, fd_set &fderror);

            static const unsigned int MAX_CONNECTIONS = 50;

        private:
            void Data();
            void Error();
            
            int socket_;
            bool active_;
            
            static int FindFree();

            static dsb::rpc::Connection *connections_[dsb::rpc::Connection::MAX_CONNECTIONS];

        };
    };
};

#endif
