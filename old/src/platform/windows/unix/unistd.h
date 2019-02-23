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
///   File: unistd.h
///
/// Author: $author$
///   Date: 11/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WINDOWS_UNIX_UNISTD_H
#define _XOS_WINDOWS_UNIX_UNISTD_H

#include "xos/base/Platform.hpp"

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

pid_t fork(void);
pid_t vfork(void);

int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ...);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);

void usleep(useconds_t useconds);

namespace xos {
namespace windows {
namespace unix {

} // namespace unix 
} // namespace windows 
} // namespace xos 

#endif // _XOS_WINDOWS_UNIX_UNISTD_H 
        

