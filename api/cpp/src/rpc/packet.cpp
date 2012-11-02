#include <dsb/rpc/packet.h>
#include <dsb/nodeset.h>
#include <memory>

using namespace std;

bool dsb::rpc::Packet::Push(dsb::NodeSet *set) {
    dsb::rpc::Header *header = static_cast<Header*>(data_);
    header->pcount++;
    char *current = static_cast<char*>(data_+position_);
    *current = set->Type();
    current++;
    position_ += set->Pack(current, max_ - position_ - 1)+1;
    return true;
}

unique_ptr<dsb::NodeSet> dsb::rpc::Packet::Pop() {
    dsb::NodeSet *result;
    dsb::rpc::Header *header = static_cast<Header*>(data_);
    header->pcount--;
    char *current = static_cast<char*>(data_+position_);
    result = dsb::NodeSet::Generate(static_cast<nodeset_t>(*current));
    current++;
    position_ += result->UnPack(current)+1;
    return unique_ptr<NodeSet>(result);
}
