#ifndef _DSB_SINGLETONNS_H_
#define _DSB_SINGLETONNS_H_

#include <dsb/nodeset.h>
#include <dsb/nodeset_types.h>
#include <dsb/nid.h>

namespace dsb {
namespace rpc {
class Packet;
};
class SingletonNS : public dsb::NodeSet {
	public:
	SingletonNS() : nid_(dsb::Null) {};
	SingletonNS(const dsb::NID &nid) : nid_(nid) {};
	~SingletonNS() {};
	
	int Count() { return 1; };
	int Pack(char *data, int max);
	int UnPack(char *data);
	dsb::NID Get(int i) { return (i==0) ? nid_ : dsb::Null; };
        char Type() { return NS_SINGLETON; };
	
	private:
	dsb::NID nid_;
};
};

#endif
