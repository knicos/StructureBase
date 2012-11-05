#ifndef _DSB_CONNECTION_H_
#define _DSB_CONNECTION_H_

#include <unistd.h>
#include <sys/types.h>
#include <dsb/request_types.h>

namespace dsb {
    class NID;
    namespace rpc {

        class Connection {
        public:
            Connection(int socket);
            Connection(const char *address, int port);
            ~Connection();

            int Socket() { return socket_; };
            bool Connect(const char *address, int port);
            void Close();
            void Flush();
            
            bool Send(dsb::request_t request, dsb::NID *params);
            
            static void Initialise();
            static void Finalise();
            
            static Connection *FindBest();
            static int SetDescriptors(fd_set &fdread, fd_set &fderror);
            static void CheckStatus(fd_set &fdread, fd_set &fderror);

            static const unsigned int MAX_CONNECTIONS = 50;
            static const unsigned int BUFFER_SIZE = 10000;
            static const unsigned int MAX_NID_PARAMS = 10;

        private:
            void Data();
            void Error();
            
            int socket_;
            bool active_;
            unsigned char outbuffer_[BUFFER_SIZE];
            int outposition_;
            unsigned char inbuffer_[BUFFER_SIZE];
            int inposition_;
            dsb::NID *in_nid_array_;
            
            static int FindFree();

            static dsb::rpc::Connection *connections_[dsb::rpc::Connection::MAX_CONNECTIONS];

        };
    };
};

#endif
