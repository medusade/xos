///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: NULLStream.hpp
///
/// Author: $author$
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_NULLSTREAM_HPP
#define _XOS_BASE_NULLSTREAM_HPP

#include "xos/base/Stream.hpp"
#include "xos/os/Logger.hpp"

namespace xos {

typedef Stream NULLStreamImplement;
typedef ExportBase NULLStreamExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NULLStream
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NULLStream
: virtual public NULLStreamImplement, public NULLStreamExtend {
public:
    typedef NULLStreamImplement Implements;
    typedef NULLStreamExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: NULLStream
    ///////////////////////////////////////////////////////////////////////
    NULLStream(LockedInterface* locked=0, bool noLogging=false)
    : m_locked(locked),m_noLogging(noLogging) {
    }
    virtual ~NULLStream() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        return 0; }
    virtual ssize_t Write(const WhatT* what, ssize_t size = -1) {
        return 0; }
    virtual ssize_t WriteFormattedV(const char* format, va_list va) {
        return 0; }
    virtual ssize_t Fill(){ 
        return 0; }
    virtual ssize_t Flush(){
        return 0; }
    virtual ssize_t Seek(size_t size, Whence whence = FromBegin){
        return 0; }
    virtual ssize_t Tell() const{
        return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock(){ return m_locked.Lock(); }
    virtual bool Unlock(){ return m_locked.Unlock(); }
    virtual Status TryLock(){ return m_locked.TryLock(); }
    virtual Status TimedLock(mseconds_t waitMilliseconds){ 
        return m_locked.TimedLock(waitMilliseconds); }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    LockedAttached m_locked;
    bool m_noLogging;
};

} // namespace xos 

#endif // _XOS_BASE_NULLSTREAM_HPP 
