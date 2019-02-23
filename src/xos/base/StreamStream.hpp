///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: StreamStream.hpp
///
/// Author: $author$
///   Date: 3/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STREAMSTREAM_HPP
#define _XOS_BASE_STREAMSTREAM_HPP

#include "xos/base/Stream.hpp"
#include "xos/base/Wrapper.hpp"
#include "xos/base/Coded.hpp"
#include "xos/os/Logger.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: StreamStreamT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 typename TStream = Stream,
 class TImplement = Stream,
 class TExtend = Wrapper<TStream, ExportBase, TImplement>,
 typename TWhat = void,
 typename TWhence = StreamLockedInterface::Whence,
 TWhence VFromBegin = StreamLockedInterface::FromBegin,
 TWhence VFromEnd = StreamLockedInterface::FromEnd,
 typename TStatus = LockedInterface::Status,
 TStatus VSuccess = LockedInterface::Success>

class _EXPORT_CLASS StreamStreamT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StreamStreamT(TStream& wrapped, LockedInterface* locked=0, bool noLogging=false)
    : Extends(wrapped), m_locked(locked), m_noLogging(noLogging) {
    }
    virtual ~StreamStreamT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const TWhat* what, ssize_t size = -1) {
        ssize_t count = 0;
        const char* chars;
        if ((chars = (const char*)(what))) {
            TChar c;
            if (0 <= (size)) {
                for (ssize_t i = 0; i < size; ++i, ++chars, ++count) {
                    c = (TChar)(*chars);
                    this->m_wrapped.Write(&c, 1);
                }
            } else {
                for (char cc = *chars; cc != 0; cc = *(++chars), ++count) {
                    c = (TChar)(cc);
                    this->m_wrapped.Write(&c, 1);
                }
            }
        }
        return count;
    }
    virtual ssize_t Read(TWhat* what, size_t size) { return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Fill(){ return 0; }
    virtual ssize_t Flush(){ return 0; }
    virtual ssize_t Seek(size_t size, TWhence whence = VFromBegin) { return 0; }
    virtual ssize_t Tell() const { return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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

typedef StreamStreamT<char, CharStreamBase, Stream> StreamStream;
typedef StreamStreamT<char, CharStreamBase, Coded<char, Stream> > CodedStreamStream;

typedef StreamStreamT<tchar_t, TCharStreamBase, Stream> TStreamStream;
typedef StreamStreamT<tchar_t, TCharStreamBase, Coded<tchar_t, Stream> > CodedTStreamStream;

typedef StreamStreamT<wchar_t, WCharStreamBase, Stream> WStreamStream;
typedef StreamStreamT<wchar_t, WCharStreamBase, Coded<wchar_t, Stream> > CodedWStreamStream;

} // namespace xos

#endif // _XOS_BASE_STREAMSTREAM_HPP 
