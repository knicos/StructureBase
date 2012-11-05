/* 
Copyright (c) 2012, Nicolas Pope
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
 */

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

