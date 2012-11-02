#ifndef _DSB_NODESET_H_
#define _DSB_NODESET_H_

#include <dsb/nid.h>
#include <dsb/nodeset_types.h>

namespace dsb {
namespace rpc {
class Packet;
};

class NodeSet {
	public:
	NodeSet() {};
	virtual ~NodeSet() {};
	
	virtual int Count() = 0;
	virtual int Pack(char *data, int max) { return 0; };
	virtual int UnPack(char *data) { return 0; };
	virtual dsb::NID Get(int i) = 0;
        virtual char Type() { return 0; };
	
	static NodeSet *Generate(nodeset_t type);
};
};

#endif
