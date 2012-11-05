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

#ifndef _DSB_CONNECTION_H_
#define _DSB_CONNECTION_H_

#include <unistd.h>
#include <sys/types.h>
#include <dsb/request_types.h>

namespace dsb {
    class NID;
    namespace rpc {

        class Connection {
        public:
            Connection(int socket);
            Connection(const char *address, int port);
            ~Connection();

            int Socket() { return socket_; };
            bool Connect(const char *address, int port);
            void Close();
            void Flush();
            
            bool Send(dsb::request_t request, dsb::NID *params);
            
            static void Initialise();
            static void Finalise();
            
            static Connection *FindBest();
            static int SetDescriptors(fd_set &fdread, fd_set &fderror);
            static void CheckStatus(fd_set &fdread, fd_set &fderror);

            static const unsigned int MAX_CONNECTIONS = 50;
            static const unsigned int BUFFER_SIZE = 10000;
            static const unsigned int MAX_NID_PARAMS = 10;

        private:
            void Data();
            void Error();
            
            int socket_;
            bool active_;
            unsigned char outbuffer_[BUFFER_SIZE];
            int outposition_;
            unsigned char inbuffer_[BUFFER_SIZE];
            int inposition_;
            dsb::NID *in_nid_array_;
            
            static int FindFree();

            static dsb::rpc::Connection *connections_[dsb::rpc::Connection::MAX_CONNECTIONS];

        };
    };
};

#endif
