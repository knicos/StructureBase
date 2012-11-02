#include <dsb/rpc/packet.h>
#include <dsb/singletonns.h>

int dsb::SingletonNS::Pack(char *data, int max) {
    if (max < sizeof(nid_)) return 0;
    dsb::NID* space = reinterpret_cast<dsb::NID*>(data);
    *space = nid_;
    return sizeof(nid_);
}

int dsb::SingletonNS::UnPack(char *data) {
    dsb::NID* space = reinterpret_cast<dsb::NID*>(data);
    nid_ = *space;
    return sizeof(nid_);
}
