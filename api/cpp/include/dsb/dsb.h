#ifndef _DSB_DSB_H_
#define _DSB_DSB_H_

#include <memory>

namespace dsb {
class NID;
class NodeSet;

namespace rpc{
    class Connection;
};

class DSB {
public:
	DSB(const char *address, int port);
	~DSB();
	
	bool Initialise();
	
	std::unique_ptr<dsb::NodeSet> Follow(const dsb::NodeSet &s1, const dsb::NodeSet &s2);
	void Define(const dsb::NodeSet &s1, const dsb::NodeSet &s2, const dsb::NodeSet &d);
	
	static DSB *DSBInstance() { return self_; };
	
private:
    dsb::rpc::Connection *connection_;
	bool initialised_;
    int port_;
    const char *address_;
	
	static DSB *self_;
};
};

#endif
