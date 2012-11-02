#include <dsb/rpc/packet.h>

void *dsb::rpc::Packet::GetSpace(int amount) {
    if (position_ + amount > max_) return 0;
    void *result = data_+position_;
    position_ += amount;
    return result;
};
