#include <dsb/rpc/handlers.h>
#include <dsb/rpc/connection.h>
#include <dsb/nid.h>

dsb::rpc::handler_t *dsb::rpc::Handlers::handlers_;

void dsb::rpc::Handlers::Initialise() {
    handlers_ = new handler_t[dsb::RT_LAST];
    for (int i=0; i<RT_LAST; ++i) {
        handlers_[i] = 0;
    }
}

void dsb::rpc::Handlers::Finalise() {
    delete [] handlers_;
}

void dsb::rpc::Handlers::Register(dsb::request_t request, dsb::rpc::handler_t handler) {
    handlers_[request] = handler;
}

void dsb::rpc::Handlers::Call(dsb::request_t request, dsb::rpc::Connection *connection, dsb::NID *params) {
    if (handlers_[request] == 0) return;
    handlers_[request](connection,params);
}
