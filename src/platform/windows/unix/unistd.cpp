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
///   File: unistd.cpp
///
/// Author: $author$
///   Date: 10/13/2012
///////////////////////////////////////////////////////////////////////
#include "xos/base/Base.hpp"
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

pid_t fork(void) {
    pid_t pid = (pid_t)(EINVAL);
    return pid;
}
pid_t vfork(void) {
    pid_t pid = (pid_t)(EINVAL);
    return pid;
}

int execl(const char *path, const char *arg, ...) {
    errno = EINVAL;
    return -1;
}
int execlp(const char *file, const char *arg, ...) {
    errno = EINVAL;
    return -1;
}
int execle(const char *path, const char *arg, ...) {
    errno = EINVAL;
    return -1;
}
int execv(const char *path, char *const argv[]) {
    errno = EINVAL;
    return -1;
}
int execvp(const char *file, char *const argv[]) {
    errno = EINVAL;
    return -1;
}
int execvpe(const char *file, char *const argv[], char *const envp[]) {
    errno = EINVAL;
    return -1;
}

pid_t wait(int *status) { 
    pid_t p = (pid_t)(EINVAL);
    return p; 
}
pid_t waitpid(pid_t pid, int *status, int options) { 
    pid_t p = (pid_t)(EINVAL);
    return p; 
}
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options) { 
    return EINVAL; 
}

void usleep(useconds_t useconds) {
    Sleep(useconds/1000);
}

namespace xos {
namespace windows {
namespace unix {

} // namespace unix 
} // namespace windows 
} // namespace xos 
