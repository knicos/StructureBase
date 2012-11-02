#ifndef _DSB_NODESET_H_
#define _DSB_NODESET_H_

#include <dsb/nid.h>

namespace dsb {
namespace rpc {
class Packet;
};

class NodeSet {
	public:
	NodeSet() {};
	virtual ~NodeSet() {};
	
	virtual int Count() = 0;
	virtual int Pack(dsb::rpc::Packet *data) { return 0; };
	virtual void UnPack(dsb::rpc::Packet *data) {};
	virtual dsb::NID Get(int i) = 0;
	
	//Requires a generator.
};
};

#endif
