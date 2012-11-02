#include <dsb/rpc/packet.h>
#include <dsb/singletonns.h>

int dsb::SingletonNS::Pack(dsb::rpc::Packet *data) {
    dsb::NID* space = static_cast<dsb::NID*>(data->GetSpace(sizeof(nid_)));
    if (space == 0) return 0;
    *space = nid_;
    return sizeof(nid_);
}

void dsb::SingletonNS::UnPack(dsb::rpc::Packet *data) {
    dsb::NID* space = static_cast<dsb::NID*>(data->GetSpace(sizeof(nid_)));
    if (space == 0) return;
    nid_ = *space;
}
