/* 
 * File:   rpc.h
 * Author: nick
 *
 * Created on 03 November 2012, 08:37
 */

#ifndef RPC_H
#define	RPC_H

namespace dsb {
    class NodeSet;
};

namespace dsb {  
    namespace rpc {
        class Connection;
        typedef bool (*handler_t)(dsb::rpc::Connection*, dsb::NodeSet**, int);
        
        bool Initialise();
        bool Finalise();
        void Poll();
        
        bool Call(dsb::rpc::Connection *connection,
                  int function,
                  NodeSet **parameters,
                  int pcount);
        bool AddHandler(int function, handler_t fptr);
    };
};

#endif	/* RPC_H */

