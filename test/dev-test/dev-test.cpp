#include <dsb/dsb.h>
#include <dsb/nid.h>
#include <dsb/singletonns.h>
#include <dsb/rpc/packet.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <dsb/rpc/rpc.h>
#include <dsb/rpc/connection.h>

using namespace std;

int main() {
    cout << "Hello World.\n";

    dsb::Initialise();
    dsb::Connect("localhost", 8081);

    dsb::rpc::Connection *mycon = dsb::rpc::Connection::FindBest();
    mycon->Send(dsb::RT_TEST, (dsb::NID[]){dsb::NID(),dsb::NID(),dsb::NID()});
    
    dsb::Finalise();
}
