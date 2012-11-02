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
  
  dsb::rpc::Packet *mypacket = new dsb::rpc::Packet(new char[20], 20);
  unique_ptr<dsb::SingletonNS> myns(new dsb::SingletonNS(dsb::NID(5)));
  myns->Pack(mypacket);
  cout << "NS: " << (int)(*static_cast<dsb::NID*>(mypacket->Data())) << endl;
}
