#ifndef _DSB_NID_H_
#define _DSB_NID_H_

#include <dsb/node_types.h>

namespace dsb {
class NID {
	//friend class NID;

	public:
	NID();
	NID(dsb::node_type_t type, unsigned int v)
	  : type_(type), v_(v) {};
	NID(int v) : type_(NT_INTEGER), v_(v) {};
	
	bool operator==(const dsb::NID &other) const {
		return (other.type_ == type_) && (other.v_ == v_);
	};
	
	operator int() const {
		if (type_ == NT_INTEGER)
		return static_cast<int>(v_);
                return 0;
	};
	
	private:
	node_type_t type_;
	unsigned int v_;
};

static const NID Null = NID(NT_SPECIAL,0);
};

#endif
