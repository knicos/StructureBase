#ifndef _DSB_DSB_H_
#define _DSB_DSB_H_

namespace dsb {
class NID;

class DSB {
	public:
	DSB(const char *dsbdir);
	~DSB();
	
	bool Initialise();
	
	dsb::NID Follow(const dsb::NID &s1, const dsb::NID &s2);
	void Define(const dsb::NID &s1, const dsb::NID &s2, const dsb::NID &d);
	
	static DSB *DSBInstance() { return self_; };
	
	private:
	char *dsbdir_;
	bool initialised_;
	
	static DSB *self_;
};
};

#endif
