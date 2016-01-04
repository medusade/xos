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
///   File: Directory.hpp
///
/// Author: $author$
///   Date: 10/27/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_DIRECTORY_HPP
#define _XOS_FS_DIRECTORY_HPP

#include "xos/fs/Entry.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace fs {

typedef InterfaceBase DirectoryImplement;
typedef ExportBase DirectoryExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Directory: virtual public DirectoryImplement, public DirectoryExtend {
public:
    typedef DirectoryImplement Implements;
    typedef DirectoryExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Directory() {
    }
    virtual ~Directory() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const std::string& name) {
        const char* chars;
        if ((chars = name.c_str()))
            return Open(chars);
        return false;
    }
    virtual bool Open(const wchar_t* name) {
        return false;
    }
    virtual bool Open(const char* name) {
        return false;
    }
    virtual bool Close() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Entry* GetFirst() {
        return 0;
    }
    virtual Entry* GetNext() {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_DIRECTORY_HPP 
