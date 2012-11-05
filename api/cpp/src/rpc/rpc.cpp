#include <dsb/rpc/rpc.h>
#include <dsb/rpc/connection.h>
#include <dsb/rpc/handlers.h>

bool dsb::rpc::Initialise() {
    dsb::rpc::Connection::Initialise();
    dsb::rpc::Handlers::Initialise();
    return true;
}

bool dsb::rpc::Finalise() {
    dsb::rpc::Connection::Finalise();
    dsb::rpc::Handlers::Finalise();
}

void dsb::rpc::Poll() {
    fd_set fdread;
    fd_set fderror;
    
    FD_ZERO(&fdread);
    FD_ZERO(&fderror);
    int n = dsb::rpc::Connection::SetDescriptors(fdread,fderror);

    //Wait for a network event or timeout in 3 seconds
    timeval block;
    block.tv_sec = 0;
    block.tv_usec = 0;
    int selres = select(n+1, &fdread, 0, &fderror, &block);

    //Some kind of error occured, it is usually possible to recover from this.
    if (selres <= 0) {
        return;
    }
    
    dsb::rpc::Connection::CheckStatus(fdread,fderror);
}
