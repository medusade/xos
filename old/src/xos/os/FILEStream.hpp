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
///   File: FILEStream.hpp
///
/// Author: $author$
///   Date: Aug 25, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FILESTREAM_HPP_
#define _XOS_FILESTREAM_HPP_

#include "xos/base/Stream.hpp"
#include "xos/base/Coded.hpp"
#include "xos/os/Logger.hpp"

namespace xos {

typedef Stream FILEStreamImplement;
typedef Attached<FILE*, int> FILEStreamExtend;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TImplement = FILEStreamImplement,
 class TExtend = FILEStreamExtend,
 typename TWhat = void,
 typename TWhence = StreamLockedInterface::Whence,
 TWhence VFromBegin = StreamLockedInterface::FromBegin,
 TWhence VFromEnd = StreamLockedInterface::FromEnd,
 typename TStatus = LockedInterface::Status,
 TStatus VSuccess = LockedInterface::Success>

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS FILEStreamT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    FILEStreamT(FILE* detached=0, LockedInterface* locked=0, bool noLogging=false)
    : Extends(detached),m_locked(locked),m_noLogging(noLogging){}
    virtual ~FILEStreamT(){}

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(TWhat* what, size_t size){
        ssize_t count = -Error::Failed;
        if ((this->m_attachedTo)) {
        if (0 >= (count = fread(what, 1, size, this->m_attachedTo))){
            if (!(m_noLogging)) {
                XOS_LOG_ERROR("failed on fread()");
            }
            count = -Error::Failed;
        }
        }
        return count;
    }
    virtual ssize_t Write(const TWhat* what, ssize_t size = -1){
        ssize_t count = -Error::Failed;
        if ((this->m_attachedTo)) {
            if (0 > (size)) {
                size = strlen((const char*)(what));
            }
            if (0 >= (count = fwrite(what, 1, size, this->m_attachedTo))){
                if (!(m_noLogging)) {
                    XOS_LOG_ERROR("failed on fwrite()");
                }
                count = -Error::Failed;
            }
        }
        return count;
    }
    virtual ssize_t WriteFormattedV(const char* format, va_list va) {
        ssize_t count = -Error::Failed;
        if ((this->m_attachedTo)) {
            if (0 > (count = vfprintf(this->m_attachedTo, format, va))) {
                if (!(m_noLogging)) {
                    XOS_LOG_ERROR("failed on vfprintf()");
                }
                count = -Error::Failed;
            }
        }
        return count;
    }

    virtual ssize_t Fill(){ return 0; }
    virtual ssize_t Flush(){
        ssize_t count = -Error::Failed;
        int err;
        if ((this->m_attachedTo)) {
        if ((err = fflush(this->m_attachedTo))){
            if (!(m_noLogging)) {
                XOS_LOG_ERROR("failed " << err << " on fflush()");
            }
        } else {
            count = 0;
        }
        }
        return count;
    }

    virtual ssize_t Seek(size_t size, TWhence whence = VFromBegin){
        int origin = (VFromBegin != whence)?((VFromEnd != whence)?(SEEK_CUR):(SEEK_END)):(SEEK_SET);
        ssize_t count = -Error::Failed;
        int err;
        if ((this->m_attachedTo)) {
        if ((err = fseek(this->m_attachedTo, size, origin))){
            if (!(m_noLogging)) {
                XOS_LOG_ERROR("failed " << err << " on fseek()");
            }
        } else {
            count = size;
        }
        }
        return count;
    }
    virtual ssize_t Tell() const{
        ssize_t count = -Error::Failed;
        if ((this->m_attachedTo)) {
        if (0 > (count = ftell(this->m_attachedTo))){
            if (!(m_noLogging)) {
                XOS_LOG_ERROR("failed on ftell()");
            }
            count = -Error::Failed;
        }
        }
        return count;
    }

    virtual bool Lock(){ return m_locked.Lock(); }
    virtual bool Unlock(){ return m_locked.Unlock(); }
    virtual TStatus TryLock(){ return m_locked.TryLock(); }
    virtual TStatus TimedLock(mseconds_t waitMilliseconds){
        return m_locked.TimedLock(waitMilliseconds); }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    LockedAttached m_locked;
    bool m_noLogging;
};

typedef FILEStreamT<FILEStreamImplement, FILEStreamExtend> FILEStream;
typedef Coded<char, FILEStreamImplement> CodedFILEStreamImplement;
typedef FILEStreamT<CodedFILEStreamImplement, FILEStreamExtend> CodedFILEStream;

} // namespace xos

#endif // _XOS_FILESTREAM_HPP_ 
