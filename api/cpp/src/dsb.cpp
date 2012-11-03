#include <dsb/dsb.h>
#include <dsb/nodeset.h>
#include <iostream>
#include <string.h>
#include <dsb/rpc/rpc.h>
#include <dsb/rpc/connection.h>

dsb::DSB *dsb::DSB::self_ = 0;

dsb::DSB::DSB(const char *address, int port) {
    initialised_ = false;
    address_ = address;
    port_ = port;
}

dsb::DSB::~DSB() {
    dsb::rpc::Finalise();
  initialised_ = false;
  self_ = 0;
}

bool dsb::DSB::Initialise() {
  std::cout << "DSB Initialising... ";
  if (self_ == 0) {
    initialised_ = true;
    self_ = this;
    dsb::rpc::Initialise();
    connection_ = new dsb::rpc::Connection(address_, port_);
    std::cout << "success.\n";
    return true;
  }
  std::cout << "failed.\n";
  return false;
}

/*std::unique_ptr<dsb::NodeSet> dsb::DSB::Follow(const dsb::NodeSet &s1, const dsb::NodeSet &s2) {
  //Check local cache if there is one.
  //Otherwise send to server to get result.
  //Need to get a buffer from a particular connection.
  dsb::Connection *dsb::Connection::ChooseBest();
  dsb::CommandBuffer buffer = connection->GetCommandBuffer(s1.Size()+s2.Size());
  //Generate a follow header.
  dsb::CommandHeader *header = buffer.Header();
  header->type = dsb::CT_FOLLOW;
  header->ns_count = 2;
  
  //Add s1 to buffer
  s1.Pack(buffer);
  //Add s2 to buffer
  s2.Pack(buffer);
  
  dsb::ResultBuffer rbuffer = connection->Send(buffer, dsb::NET_BLOCK);
  dsb::NodeSet *results = dsb::NodeSet::Generate(rbuffer);
  return std::unique_ptr<dsb::NodeSet>(results);
}*/
