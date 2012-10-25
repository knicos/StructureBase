#ifndef _DSB_NID_H_
#define _DSB_NID_H_

namespace dsb {
class NID {
	friend class NID;

	public:
	NID();
	NID(unsigned int v) : nid_(v) {};
	
	bool operator==(const dsb::NID &other) const {
		return other.nid_ == nid_;
	};
	
	private:
	unsigned int nid_;
};
};

#endif
