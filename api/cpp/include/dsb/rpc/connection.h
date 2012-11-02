#ifndef _DSB_CONNECTION_H_
#define _DSB_CONNECTION_H_

namespace dsb {
    namespace rpc {
        class Connection {
        public:
            Connection(int socket);
            ~Connection();

            static void Initialise();
            static void Finalise();

            static const unsigned int MAX_CLIENTS = 50;

        private:
            static int FindFree();

            static dsb::rpc::Connection *connections_[dsb::rpc::Connection::MAX_CLIENTS];

        };
    };
};

#endif
