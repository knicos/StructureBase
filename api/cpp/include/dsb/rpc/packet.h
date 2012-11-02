#ifndef _DSB_RPC_PACKET_H_
#define _DSB_RPC_PACKET_H_

#include <dsb/rpc/header.h>
#include <memory>

namespace dsb {
class NodeSet;
namespace rpc {

class Packet {
    public:
    Packet(void *data, int max)
     : data_(data),
       max_(max),
       position_(sizeof(dsb::rpc::Header)) {};
     ~Packet() {};

     void SetFunction(int function) {
         dsb::rpc::Header *header = static_cast<Header*>(data_);
         header->function = function;
     };
     bool Push(NodeSet *set);
     std::unique_ptr<NodeSet> Pop();
	
     void *Raw() { return data_; };
     void Reset() { position_ = sizeof(dsb::rpc::Header); };
	
    private:
    void *data_;
    int max_;
    int position_;
};
};
};

#endif
