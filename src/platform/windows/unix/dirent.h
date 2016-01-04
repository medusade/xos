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
///   File: dirent.h
///
/// Author: $author$
///   Date: 11/1/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WINDOWS_UNIX_DIRENT_H
#define _XOS_WINDOWS_UNIX_DIRENT_H

#include "xos/base/Base.hpp"

struct dirent {
    ino_t	       d_ino;	    // inode number 
    off_t	       d_off;	    // offset to the next dirent 
    unsigned short d_reclen;    // length of this record 
    unsigned char  d_type;	    // type of file; not supported by all file system types 
    char	       d_name[256]; // filename 
};
struct DIR;

DIR* opendir(const char *name);
DIR* fdopendir(int fd);
int closedir(DIR* dirp);
void rewinddir(DIR *dirp);
struct dirent* readdir(DIR *dirp);
int readdir_r(DIR* dirp, struct dirent* entry, struct dirent** result);

namespace xos {
namespace windows {
namespace unix {

} // namespace unix 
} // namespace windows 
} // namespace xos 

#endif // _XOS_WINDOWS_UNIX_DIRENT_H 
        

