/* 
 * File:   rpc.h
 * Author: nick
 *
 * Created on 03 November 2012, 08:37
 */

#ifndef RPC_H
#define	RPC_H

namespace dsb {
    namespace rpc {
        bool Initialise();
        bool Finalise();
        void Poll();
    };
};

#endif	/* RPC_H */

