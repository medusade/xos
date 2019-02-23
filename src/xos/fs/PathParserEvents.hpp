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
///   File: PathParserEvents.hpp
///
/// Author: $author$
///   Date: 10/28/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_PATHPARSEREVENTS_HPP
#define _XOS_FS_PATHPARSEREVENTS_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace fs {

template <typename TChar = char, class TImplement = InterfaceBase>

class _EXPORT_CLASS PathParserEventsT: virtual public TImplement {
public:
    typedef TImplement Implements;

    virtual bool OnInit() {
        return true;
    }
    virtual bool OnFini() {
        return true;
    }
    virtual bool OnHost(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnVolume(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnDirectory(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnParentDirectory(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnCurrentDirectory(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnRootDirectory(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnRootParentDirectory(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnRootCurrentDirectory(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnRootFileName(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnFileName(const TChar* chars, ssize_t length = -1) {
        return true;
    }
    virtual bool OnFileExtension(const TChar* chars, ssize_t length = -1) {
        return true;
    }
};

typedef PathParserEventsT<char> PathParserEvents;
typedef PathParserEventsT<wchar_t> WPathParserEvents;
typedef PathParserEventsT<tchar_t> TPathParserEvents;

} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_PATHPARSEREVENTS_HPP 
