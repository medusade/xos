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
///   File: StreamLogger.hpp
///
/// Author: $author$
///   Date: Aug 15, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_STREAMLOGGER_HPP_
#define _XOS_STREAMLOGGER_HPP_

#include "xos/os/Logger.hpp"
#include "xos/base/Stream.hpp"
#include "xos/base/Attached.hpp"
#include "xos/base/Locker.hpp"

#define XOS_STREAMLOGGER_LEVELS_ENABLED XOS_DEFAULT_LOGGING_LEVELS

namespace xos {

typedef Logger StreamLoggerImplement;
typedef Attached<Stream*, int, 0> StreamLoggerExtend;

class EXPORT_CLASS StreamLogger
: virtual public StreamLoggerImplement,
  public StreamLoggerExtend
{
  public:
    typedef StreamLoggerImplement Implements;
    typedef StreamLoggerExtend Extends;

    StreamLogger
    (Stream* attachedTo = 0,
     Level::Enable levelEnabled = XOS_STREAMLOGGER_LEVELS_ENABLED)
    : Extends(attachedTo),
      m_levelEnabled(levelEnabled)
    {}
    virtual bool Init(){ return true; }
    virtual bool Fini(){ return true; }
    virtual void Log
    (const Level& level, const Message& message, const Location& location){
        Log(level, location, message);
    }
    virtual void Log
    (const Level& level, const Location& location, const Message& message){
        Stream* s = 0;
        if ((IsEnabledFor(level)) && (s = m_attachedTo)){
            Locker<Stream> locker(*s);
            Log(s, location);
            s->Write(message.c_str());
            s->Write("\n");
            s->Flush();
        }
    }
    virtual void LogFormatted
    (const Level& level, const Location& location, const char* format, ...){
        Stream* s = 0;
        if ((IsEnabledFor(level)) && (s = m_attachedTo)){
            Locker<Stream> locker(*s);
            Log(s, location);
            if ((format)) {
                va_list va;
                va_start(va, format);
                s->WriteFormattedV(format, va);
                va_end(va);
            }
            s->Write("\n");
            s->Flush();
        }
    }
    virtual void Log
    (const Level& level, const Message& message){
        Stream* s = 0;
        if ((IsEnabledFor(level)) && (s = m_attachedTo)){
            Locker<Stream> locker(*s);
            s->Write(message.c_str());
            s->Write("\n");
            s->Flush();
        }
    }
    virtual void LogFormatted
    (const Level& level, const char* format, ...){
        Stream* s = 0;
        if ((IsEnabledFor(level)) && (s = m_attachedTo)){
            Locker<Stream> locker(*s);
            if ((format)) {
                va_list va;
                va_start(va, format);
                s->WriteFormattedV(format, va);
                va_end(va);
            }
            s->Write("\n");
            s->Flush();
        }
    }
    virtual void EnableFor(const Level& level) {
        m_levelEnabled = level;
    }
    virtual Level EnabledFor() const {
        return m_levelEnabled;
    }
    virtual bool IsEnabledFor(const Level& level) const {
        Level::Enable enabled = m_levelEnabled;
        Level::Enable enable = level;
        bool isTrue = ((enabled & enable) == enable);
        return isTrue;
    }
protected:
    virtual void Log(Stream* s, const Location& location){
        if ((s)) {
            s->Write(location.getFileName().c_str());
            s->Write("[");
            s->Write(location.getLineNumber().c_str());
            s->Write("]");
            s->Write(" ");
            s->Write(location.getFunctionName().c_str());
            s->Write(" ");
        }
    }
protected:
    Level m_levelEnabled;
};

} // namespace xos

#endif // _XOS_STREAMLOGGER_HPP_ 
