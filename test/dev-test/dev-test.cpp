#include <dsb/dsb.h>
#include <dsb/nid.h>
#include <dsb/singletonns.h>
#include <dsb/rpc/packet.h>
#include <iostream>
#include <memory>
#include <string.h>

using namespace std;

int main() {
  cout << "Hello World.\n";
  
  unique_ptr<dsb::DSB> mydsb(new dsb::DSB("test"));
  mydsb->Initialise();
  
  dsb::SingletonNS myns(dsb::NID(5));
  
  dsb::rpc::Packet *mypacket = new dsb::rpc::Packet(new char[20], 20);
  mypacket->Push(&myns);
  mypacket->Reset();
  unique_ptr<dsb::NodeSet> resultns(mypacket->Pop());
  
  cout << "NS: " << (int)resultns->Get(0) << endl;
}
