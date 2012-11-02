#include <dsb/nodeset_types.h>
#include <dsb/nodeset.h>
#include <dsb/singletonns.h>

dsb::NodeSet *dsb::NodeSet::Generate(nodeset_t type) {
    switch(type) {
        case NS_SINGLETON: return new SingletonNS();
    };
    return 0;
}
