#ifndef _DSB_RPC_HEADER_H_
#define _DSB_RPC_HEADER_H_

namespace dsb {
namespace rpc {
struct Header {
	unsigned int function;
	unsigned char pcount;
};
};
};

#endif
