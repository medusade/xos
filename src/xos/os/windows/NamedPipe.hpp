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
///   File: NamedPipe.hpp
///
/// Author: $author$
///   Date: 10/1/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_NAMEDPIPE_HPP
#define _XOS_OS_WINDOWS_NAMEDPIPE_HPP

#include "xos/base/Opened.hpp"
#include "xos/base/Attached.hpp"
#include "xos/base/Base.hpp"
#include "xos/os/Logger.hpp"

#define XOS_OS_WINDOWS_NAMEDPIPE_PREFIX "\\\\.\\pipe\\"
#define XOS_OS_WINDOWS_NAMEDPIPE_BUFFER_SIZE 4096

namespace xos {
namespace os {
namespace windows {

typedef InterfaceBase NamedPipeImplement;
typedef Attached<HANDLE, int, -1, ExportBase, NamedPipeImplement> NamedPipeAttached;
typedef Opened<HANDLE, int, -1, NamedPipeAttached, NamedPipeImplement> NamedPipeExtend;

class _EXPORT_CLASS NamedPipe
: virtual public NamedPipeImplement,
  public NamedPipeExtend
{
public:
    typedef NamedPipeImplement Implements;
    typedef NamedPipeExtend Extends;

    NamedPipe() 
    : m_isConnected(false),
      m_namePrefix(_T(XOS_OS_WINDOWS_NAMEDPIPE_PREFIX)),
      m_bSlash(_T("\\")),
      m_fSlash(_T("/")),
      m_bufferSize(XOS_OS_WINDOWS_NAMEDPIPE_BUFFER_SIZE)
    {
    }
    virtual ~NamedPipe() {
        if ((m_isConnected)) {
            if (!(Disconnect())) {
                XOS_LOG_ERROR("failed on Disconnect()");
            }
        }
        if ((IsOpen())) {
            if (!(Close())) {
                XOS_LOG_ERROR("failed on Close()");
            }
        }
    }

    virtual bool Create(const tchar_t* named) {
        std::basic_string<tchar_t> name(MakeName(named));
        bool isOpen = false;
        HANDLE detached = INVALID_HANDLE_VALUE;
        DWORD dwOpenMode = PIPE_ACCESS_DUPLEX;
        DWORD dwPipeMode = PIPE_WAIT | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE;
        DWORD dwMaxInstances = PIPE_UNLIMITED_INSTANCES;
        DWORD dwOutBufferSize = m_bufferSize;
        DWORD dwInBufferSize = m_bufferSize;
        DWORD dwDefaultTimeOut = 0;
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
        if ((isOpen = (INVALID_HANDLE_VALUE != (detached = CreateNamedPipe
            (name.c_str(), dwOpenMode, dwPipeMode, dwMaxInstances, 
             dwOutBufferSize, dwInBufferSize, dwDefaultTimeOut, lpSecurityAttributes))))) {
            Attach(detached, isOpen);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << GetLastError() << " on CreateNamedPipe()");
        }
        return false;
    }
    virtual bool Open(const tchar_t* named) {
        std::basic_string<tchar_t> name(MakeName(named));
        bool isOpen = false;
        HANDLE detached = INVALID_HANDLE_VALUE;
        DWORD dwOpenMode = GENERIC_READ | GENERIC_WRITE;
        DWORD dwShareMode = 0;
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
        DWORD dwCreationDisposition = OPEN_EXISTING;
        DWORD dwFlagsAndAttributes = 0;
        HANDLE hTemplateFile = 0;
        if ((isOpen = (INVALID_HANDLE_VALUE != (detached = CreateFile
            (name.c_str(), dwOpenMode, dwShareMode, lpSecurityAttributes,
             dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile))))) {
            Attach(detached, isOpen);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << GetLastError() << " on CreateFile()");
        }
        return false;
    }
    virtual bool Close() {
        bool isOpen = false;
        HANDLE detached = INVALID_HANDLE_VALUE;
        if (INVALID_HANDLE_VALUE != (detached = Detach(isOpen))) {
            if ((CloseHandle(detached))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on CloseHandle()");
            }
        }
        return false;
    }

    virtual bool Connect() {
        HANDLE hPipe = INVALID_HANDLE_VALUE;
        LPOVERLAPPED lpOverlapped = 0;
        if (INVALID_HANDLE_VALUE != (hPipe = m_attachedTo)) {
            if ((ConnectNamedPipe(hPipe, lpOverlapped))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on ConnectNamedPipe()");
            }
        }
        return false;
    }
    virtual bool Disconnect() {
        HANDLE hPipe = INVALID_HANDLE_VALUE;
        if (INVALID_HANDLE_VALUE != (hPipe = m_attachedTo)) {
            if ((DisconnectNamedPipe(hPipe))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on DisonnectNamedPipe()");
            }
        }
        return false;
    }
    virtual AttachedT Detach(bool& isOpen) {
        m_isConnected = false;
        return Extends::Detach(isOpen);
    }
    virtual AttachedT AttachConnected(AttachedT detached) {
        AttachedT attached;
        if (INVALID_HANDLE_VALUE != (attached = Attach(detached))) {
            m_isConnected = true;
        }
        return attached;
    }

    virtual ssize_t Read(void* buf, size_t len) {
        ssize_t count = -1;
        HANDLE hPipe = 0;
        DWORD size = 0;
        if ((hPipe = m_attachedTo)) {
            if ((ReadFile(hPipe, buf, len, &size, NULL))) {
                count = size;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on ReadFile()");
            }
        }
        return count;
    }
    virtual ssize_t Write(const void* buf, size_t len) {
        ssize_t count = -1;
        HANDLE hPipe = 0;
        DWORD size = 0;
        if ((hPipe = m_attachedTo)) {
            if ((WriteFile(hPipe, buf, len, &size, NULL))) {
                count = size;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on WriteFile()");
            }
        }
        return count;
    }
    virtual std::basic_string<tchar_t> MakeName(const tchar_t* named) const {
        std::basic_string<tchar_t> name(m_namePrefix);
        if ((m_bSlash[0] == (named[0])) || (m_fSlash[0] == (named[0])))
            ++named;
        name.append(named);
        return name;
    }

protected:
    bool m_isConnected;
    const tchar_t* m_namePrefix;
    const tchar_t* m_bSlash;
    const tchar_t* m_fSlash;
    DWORD m_bufferSize;
};

} // namespace windows 
} // namespace os 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_NAMEDPIPE_HPP 
        

