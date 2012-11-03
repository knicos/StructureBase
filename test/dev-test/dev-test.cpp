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
  
  unique_ptr<dsb::DSB> mydsb(new dsb::DSB("test"));
  mydsb->Initialise();
  
  dsb::SingletonNS myns(dsb::NID(5));
  
  dsb::rpc::Packet *mypacket = new dsb::rpc::Packet(new char[20], 20);
  mypacket->Push(&myns);
  
  dsb::rpc::Initialise();
  new dsb::rpc::Connection("127.0.0.1",8081);
  dsb::rpc::Finalise();
  
  
  mypacket->Reset();
  unique_ptr<dsb::NodeSet> resultns(mypacket->Pop());
  
  cout << "NS: " << (int)resultns->Get(0) << endl;
}
