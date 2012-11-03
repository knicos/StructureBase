#include "rpc.h"
#include "server.h"

int main(int argc, char *argv[]) {
    dsbd::rpc::Initialise();
    dsbd::rpc::Server *server = new dsbd::rpc::Server(8081);
    server->Listen();

    dsbd::rpc::Run();
    
    delete server;
    dsbd::rpc::Finalise();
    return 0;
}
