#ifndef _DSB_NODESET_H_
#define _DSB_NODESET_H_

#include <memory>
#include <vector>

using namespace std;

namespace dsb {
class NID;
class NodeSet {
	public:
	NodeSet() {};
	virtual ~NodeSet() {};
	
	virtual int Count() = 0;
	//virtual int Pack(dsb::Buffer &data) { return 0; };
	//virtual void UnPack(dsb::Buffer &data) {};
	virtual dsb::NID Get(int i) = 0;
	
	//Requires a generator.
};
};

#endif
