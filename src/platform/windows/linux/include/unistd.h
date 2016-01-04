/**
 **********************************************************************
 * Copyright (c) 1988-2012 $organization$
 *
 * This software is provided by the author and contributors ``as is'' 
 * and any express or implied warranties, including, but not limited to, 
 * the implied warranties of merchantability and fitness for a particular 
 * purpose are disclaimed. In no event shall the author or contributors 
 * be liable for any direct, indirect, incidental, special, exemplary, 
 * or consequential damages (including, but not limited to, procurement 
 * of substitute goods or services; loss of use, data, or profits; or 
 * business interruption) however caused and on any theory of liability, 
 * whether in contract, strict liability, or tort (including negligence 
 * or otherwise) arising in any way out of the use of this software, 
 * even if advised of the possibility of such damage.
 *
 *   File: unistd.h
 *
 * Author: $author$
 *   Date: 9/2/2012
 **********************************************************************
 */
#ifndef _XOS_WINDOWS_LINUX_UNISTD_H
#define _XOS_WINDOWS_LINUX_UNISTD_H

#include "xos/base/Platform.hpp"
#include <linux/stat.h>

#if !defined(S_IFBLK)
#define S_IFBLK 0
#endif // !defined(S_IFBLK)

#if !defined(S_IFIFO)
#define S_IFIFO 0
#endif // !defined(S_IFIFO)

#if !defined(S_IFLNK)
#define S_IFLNK 0
#endif // !defined(S_IFLNK)

#if !defined(S_IFSOCK)
#define S_IFSOCK 0
#endif // !defined(S_IFSOCK)

typedef unsigned int key_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef void* pid_t;
typedef void* id_t;
typedef void* idtype_t;
typedef void* siginfo_t;

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

pid_t vfork(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _XOS_WINDOWS_LINUX_UNISTD_H */
        

