#include "rpc.h"
#include "server.h"
#include <iostream>
#include <dsb/rpc/handlers.h>

bool test_handler(dsb::rpc::Connection *conn, dsb::NID *params) {
    std::cout << "Wooo. Test handler\n";
}

int main(int argc, char *argv[]) {
    dsbd::rpc::Initialise();
    dsbd::rpc::Server *server = new dsbd::rpc::Server(8081);
    server->Listen();
    
    //Install test handler
    dsb::rpc::Handlers::Register(dsb::RT_TEST, test_handler);
    
    dsbd::rpc::Run();
    
    delete server;
    dsbd::rpc::Finalise();
    return 0;
}
