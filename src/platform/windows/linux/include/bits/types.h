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
 *   File: types.h
 *
 * Author: $author$
 *   Date: 9/2/2012
 **********************************************************************
 */
#ifndef _XOS_WINDOWS_LINUX_BITS_TYPES_H
#define _XOS_WINDOWS_LINUX_BITS_TYPES_H

#include <unistd.h>

typedef ssize_t __ssize_t;
typedef size_t __size_t;
typedef mode_t __mode_t;
typedef time_t __time_t;
typedef key_t __key_t;
typedef uid_t __uid_t;
typedef gid_t __gid_t;
typedef pid_t __pid_t;

#define __ssize_t_defined
#define __size_t_defined
#define __mode_t_defined
#define __time_t_defined
#define __key_t_defined
#define __uid_t_defined
#define __gid_t_defined
#define __pid_t_defined

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _XOS_WINDOWS_LINUX_BITS_TYPES_H */
        

