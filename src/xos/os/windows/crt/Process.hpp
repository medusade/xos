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
///   File: Process.hpp
///
/// Author: $author$
///   Date: 10/7/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_CRT_PROCESS_HPP
#define _XOS_OS_WINDOWS_CRT_PROCESS_HPP

#include "xos/os/windows/Process.hpp"

namespace xos {
namespace windows {
namespace crt {

typedef xos::Process ProcessImplement;
typedef Attached<intptr_t, int, 0, ExportBase, ProcessImplement> ProcessAttached;
typedef Created<intptr_t, int, 0, ProcessAttached, ProcessImplement> ProcessExtend;

class _EXPORT_CLASS Process: virtual public ProcessImplement, public ProcessExtend {
public:
    typedef ProcessImplement Implements;
    typedef ProcessExtend Extends;

    Process(const char* path, char** argv, char** env, bool isDetached = false) {
        if (!(Create(path, argv, env, isDetached))) {
            XOS_LOG_ERROR("failed on Create()");
            throw(Error(Error::Failed));
        }
    }
    Process(const char* path, char** argv, bool isDetached = false) {
        if (!(Create(path, argv, isDetached))) {
            XOS_LOG_ERROR("failed on Create()");
            throw(Error(Error::Failed));
        }
    }
    Process(intptr_t detached, bool isCreated = false)
    : Extends(detached, isCreated) {}
    virtual ~Process() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()");
        }
    }

    virtual bool Create(const char* path, char** argv, char** env, bool isDetached = false) {
        bool isCreated = false;
        intptr_t detached = 0;
        int mode = (isDetached)?(_P_DETACH):(_P_NOWAIT);
        if (!(Destroyed())) {
            return false;
        }
        if ((isCreated = (0 != (detached = _spawnvpe(mode, path, argv, env))))) {
            Attach(detached, isCreated  && !isDetached);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << errno << " on _spawnvpe(..., \"" << path << "\", ...)");
        }
        return false; }
    virtual bool Create(const char* path, char** argv, bool isDetached = false) {
        bool isCreated = false;
        intptr_t detached = 0;
        int mode = (isDetached)?(_P_DETACH):(_P_NOWAIT);
        if (!(Destroyed())) {
            return false;
        }
        if ((isCreated = (0 != (detached = _spawnvp(mode, path, argv))))) {
            Attach(detached, isCreated  && !isDetached);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << errno << " on _spawnvp(..., \"" << path << "\", ...)");
        }
        return false; }
    virtual bool Destroy() {
        if ((Join())) {
            return true;
        }
        return false; }

    virtual bool Join() {
        bool isCreated = false;
        intptr_t detached = 0;
        if ((detached = Detach(isCreated))) {
            intptr_t err = 0;
            int result = 0;
            if (detached == (err = _cwait(&result, detached, 0))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << errno << " on _cwait()");
            }
        }
        return false; }
    virtual bool Separate() {
        Detach();
        return true; }

    virtual Status TryJoin() {
        return Invalid; }
    virtual Status TimedJoin(mseconds_t waitMilliSeconds) {
        return Invalid; }
};

} // namespace crt 
} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_CRT_PROCESS_HPP 
