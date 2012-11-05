/* 
 * File:   handlers.h
 * Author: nick
 *
 * Created on 05 November 2012, 19:31
 */

#ifndef HANDLERS_H
#define	HANDLERS_H

#include <dsb/request_types.h>

namespace dsb {
    class NID;
    namespace rpc {
        class Connection;
        typedef bool (*handler_t)(dsb::rpc::Connection*, dsb::NID*);
        
        class Handlers {
        public:
            static void Initialise();
            static void Finalise();
            static void Register(dsb::request_t request, dsb::rpc::handler_t handler);
            static void Call(dsb::request_t request, dsb::rpc::Connection *connection, dsb::NID *params);
            
        private:
            static handler_t *handlers_;
        };
    };
};

#endif	/* HANDLERS_H */

