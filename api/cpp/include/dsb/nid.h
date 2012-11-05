/* 
Copyright (c) 2012, Nicolas Pope
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
 */

#ifndef _DSB_NID_H_
#define _DSB_NID_H_

#include <dsb/node_types.h>

namespace dsb {
class NID {
	//friend class NID;

	public:
	NID() : type_(NT_SPECIAL),v_(0) {};
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
