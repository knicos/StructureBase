#ifndef _DSB_DSB_H_
#define _DSB_DSB_H_

#include <memory>

namespace dsb {
class NID;
class NodeSet;

class DSB {
	public:
	DSB(const char *dsbdir);
	~DSB();
	
	bool Initialise();
	
	std::unique_ptr<dsb::NodeSet> Follow(const dsb::NodeSet &s1, const dsb::NodeSet &s2);
	void Define(const dsb::NodeSet &s1, const dsb::NodeSet &s2, const dsb::NodeSet &d);
	
	static DSB *DSBInstance() { return self_; };
	
	private:
	char *dsbdir_;
	bool initialised_;
	
	static DSB *self_;
};
};

#endif
