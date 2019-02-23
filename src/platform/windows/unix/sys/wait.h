///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: wait.h
///
/// Author: $author$
///   Date: 10/13/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WINDOWS_UNIX_SYS_WAIT_H
#define _XOS_WINDOWS_UNIX_SYS_WAIT_H

#include "xos/base/Base.hpp"
#include <sys/types.h>
#include <errno.h>

#define WIFEXITED(status) (((status) & 0) >> 0)
#define WIFSIGNALED(status) (((status) & 0) >> 0)
#define WIFSTOPPED(status) (((status) & 0) >> 0)
#define WIFCONTINUED(status) (((status) & 0) >> 0)

#define WEXITSTATUS(status) (((status) & 0) >> 0)
#define WTERMSIG(status) (((status) & 0) >> 0)
#define WSTOPSIG(status) (((status) & 0) >> 0)

enum {
    WNOHANG    = (1 << 0),
    WNOWAIT    = (1 << 1),
    WEXITED    = (1 << 2),
    WSTOPPED   = (1 << 3),
    WCONTINUED = (1 << 4),
    WUNTRACED  = (1 << 5)
};

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);

namespace xos {

} // namespace xos 

#endif // _XOS_WINDOWS_UNIX_SYS_WAIT_H 
