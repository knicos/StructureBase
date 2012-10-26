#ifndef _DSB_SINGLETONNS_H_
#define _DSB_SINGLETONNS_H_

#include <dsb/nodeset.h>

namespace dsb {
class SingletonNS : public NodeSet {
	public:
	SingletonNS() : nid_(dsb::Null) {};
	SingletonNS(const dsb::NID &nid) : nid_(nid) {};
	~SingletonNS() {};
	
	int Count() { return 1; };
	/*int Pack(void *data, int max) {
	    if (sizeof(nid_) > max) return 0;
		*static_cast<dsb::NID*>(data) = nid_;
		return sizeof(nid_);
	};
	void UnPack(void *data, int size) {
		if (size != sizeof(nid_)) return;
		nid_ = *static_cast<dsb::NID*>(data);
	};*/
	
	dsb::NID Get(int i) { return (i==0) ? nid_ : dsb::Null; };
	
	private:
	dsb::NID nid_;
};
};

#endif
