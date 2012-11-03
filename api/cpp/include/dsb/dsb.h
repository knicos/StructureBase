#ifndef _DSB_DSB_H_
#define _DSB_DSB_H_

#include <memory>

namespace dsb {
    class NID;
    class NodeSet;
	
	bool Initialise();
    bool Connect(const char *address, int port);
    void Finalise();
	
	std::unique_ptr<dsb::NodeSet> Follow(const dsb::NodeSet &s1, const dsb::NodeSet &s2);
	void Define(const dsb::NodeSet &s1, const dsb::NodeSet &s2, const dsb::NodeSet &d);
	
};

#endif
