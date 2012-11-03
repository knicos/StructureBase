#include <dsb/rpc/rpc.h>
#include <dsb/rpc/connection.h>
#include "rpc.h"
#include "server.h"
#include <iostream>

bool dsbd::rpc::Initialise() {
    dsb::rpc::Connection::Initialise();
    return true;
}

bool dsbd::rpc::Finalise() {
    dsb::rpc::Connection::Finalise();
}

void dsbd::rpc::Run() {
    fd_set fdread;
    fd_set fderror;
    
    while (true) {
        FD_ZERO(&fdread);
        FD_ZERO(&fderror);
        int n1 = dsbd::rpc::Server::GetServer()->SetDescriptors(fdread,fderror);
        int n2 = dsb::rpc::Connection::SetDescriptors(fdread,fderror);
        int n = (n1 > n2) ? n1 : n2;

        //Wait for a network event
        int selres = select(n+1, &fdread, 0, &fderror,0);

        //Some kind of error occured, it is usually possible to recover from this.
        if (selres <= 0) {
            return;
        }
        
        std::cout << "DSBD: SOMETHING\n";

        dsbd::rpc::Server::GetServer()->CheckStatus(fdread,fderror);
        dsb::rpc::Connection::CheckStatus(fdread,fderror);
    }
}

void dsbd::rpc::Poll() {
    fd_set fdread;
    fd_set fderror;
    
    FD_ZERO(&fdread);
    FD_ZERO(&fderror);
    int n1 = dsbd::rpc::Server::GetServer()->SetDescriptors(fdread,fderror);
    int n2 = dsb::rpc::Connection::SetDescriptors(fdread,fderror);
    int n = (n1 > n2) ? n1 : n2;

    //Wait for a network event or timeout in 3 seconds
    timeval block;
    block.tv_sec = 0;
    block.tv_usec = 0;
    int selres = select(n+1, &fdread, 0, &fderror, &block);

    //Some kind of error occured, it is usually possible to recover from this.
    if (selres <= 0) {
        return;
    }

    dsbd::rpc::Server::GetServer()->CheckStatus(fdread,fderror);
    dsb::rpc::Connection::CheckStatus(fdread,fderror);
}
