#include <dsb/dsb.h>
#include <dsb/nodeset.h>
#include <iostream>
#include <string.h>
#include <dsb/rpc/rpc.h>
#include <dsb/rpc/connection.h>

bool dsb::Initialise() {
    dsb::rpc::Initialise();
}

void dsb::Finalise() {
    dsb::rpc::Finalise();
}

bool dsb::Connect(const char *address, int port) {
    new dsb::rpc::Connection(address, port);
    return true;
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
