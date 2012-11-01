#ifndef _DSB_RPC_PACKET_H_
#define _DSB_RPC_PACKET_H_

namespace dsb::rpc {
struct Header;

class Packet {
	public:
	Packet(void *data, int max)
	 : data_(data), max_(max), position_(0) {};
	~Packet() {};
	
	dsb::rpc::Header *Header() {
		return static_cast<dsb::rpc::Header*>(data_);
	};
	
	void *GetSpace(int amount);
	void *Raw() { return data_; };
	
	private:
	void *data_;
	int max_;
	int position_;
};
};

#endif
