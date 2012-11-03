/* 
 * File:   rpc.h
 * Author: nick
 *
 * Created on 03 November 2012, 08:37
 */

#ifndef DSBD_RPC_H
#define	DSBD_RPC_H

namespace dsbd {
    namespace rpc {
        bool Initialise();
        bool Finalise();
        void Poll();
        void Run();
    };
};

#endif	/* DSBD_RPC_H */

