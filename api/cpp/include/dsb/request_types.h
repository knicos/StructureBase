/* 
 * File:   request_types.h
 * Author: nick
 *
 * Created on 03 November 2012, 22:01
 */

#ifndef REQUEST_TYPES_H
#define	REQUEST_TYPES_H

namespace dsb {
    enum request_t {RT_NOP,RT_TEST,RT_LAST};
    struct request_entry {
        const char *name;
        int params;
    };
    extern request_entry requests[];
};

#endif	/* REQUEST_TYPES_H */

