#include <dsb/dsb.h>
#include <dsb/nodeset.h>
#include <iostream>
#include <string.h>

dsb::DSB *dsb::DSB::self_ = 0;

dsb::DSB::DSB(const char *dsbdir) {
  int length = 0;
  if (dsbdir != 0) length = strlen(dsbdir);
  if (length > 0) {
    dsbdir_ = new char[length];
    strcpy(dsbdir_, dsbdir);
  } else {
    dsbdir_ = 0;
  }
  initialised_ = false;
}

dsb::DSB::~DSB() {
  if (dsbdir_ != 0) delete [] dsbdir_;
  initialised_ = false;
  self_ = 0;
}

bool dsb::DSB::Initialise() {
  std::cout << "DSB Initialising... ";
  if ((self_ == 0) && (dsbdir_ != 0)) {
    initialised_ = true;
    self_ = this;
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
