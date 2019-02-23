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
///   File: MainWindow.hh
///
/// Author: $author$
///   Date: 2/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_MAINWINDOW_HH
#define _XOS_GUI_COCOA_MAINWINDOW_HH

#include "iHash.hh"
#include "../../../crypto/hash/MainWindow.hpp"
#include "xos/os/os/Thread.hpp"
#include "xos/os/os/Semaphore.hpp"
#include "xos/base/Waiter.hpp"

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace cocoa {

typedef xos::os::Thread Thread;
typedef xos::os::Semaphore Semaphore;
typedef xos::Waiter<Semaphore> Waiter;
///////////////////////////////////////////////////////////////////////
///  Class: ThreadRun
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ThreadRun: public Thread::Run {
public:
    typedef Thread::Run Extends;
    ThreadRun(iHashMainWindow* mainWindow): m_mainWindow(mainWindow), m_done(false) {
    }
    virtual void operator()() {
        for (bool done = false; !done;) {
            try {
                volatile Waiter waitr(m_updateFileHash);
                XOS_LOG_DEBUG("...waited on m_updateFileHash");
                if (!(done = m_done)) {
                    [m_mainWindow performSelectorOnMainThread:@selector(updateFileHash:) withObject:m_mainWindow waitUntilDone:NO];
                }
            } catch (const WaitInterface::Status& status) {
                XOS_LOG_DEBUG("...failed wait m_updateFileHash");
                done = true;
            } catch (const Error& error) {
                XOS_LOG_ERROR("...failed " << error << " on wait m_updateFileHash");
                done = true;
            }
        }
    }
    void Stop() {
        m_done = true;
        m_updateFileHash.Release();
        m_updateFileHash.Destroy();
    }
    void UpdateFileHash() {
        m_updateFileHash.Release();
    }
protected:
    iHashMainWindow* m_mainWindow;
    bool m_done;
    Semaphore m_updateFileHash;
};

typedef hash::MainWindow<ExportBase> MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow: public MainWindowExtend {
public:
    typedef MainWindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainWindow()
    : Extends(GetTheHash(), GetTheHashName()),
      m_controlView(0),
      m_threadRun(0),
      m_thread(0) {
    }
    virtual ~MainWindow() {
        if (!(Finish()))
            XOS_LOG_ERROR("failed on Finish()");
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(iHashMainWindow* mainWindow) {
        if ((mainWindow) && (m_threadRun = new ThreadRun(mainWindow))) {
            if ((m_thread = new Thread(*m_threadRun)))
                return true;
            delete m_threadRun;
            m_threadRun = 0;
        }
        return false;
    }
    virtual bool Finish() {
        if ((m_threadRun))
            m_threadRun->Stop();
        if ((m_thread)) {
            try {
                delete m_thread;
                m_thread = 0;
            } catch (Error error) {
                XOS_LOG_ERROR("caught Error error = " << error << " on delete m_thread");
                return false;
            }
        }
        if ((m_threadRun)) {
            delete m_threadRun;
            m_threadRun = 0;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Hash() {
        String s;
        if (GetHashText(s)) {
            XOS_LOG_DEBUG("text = \"" << s << "\"");
            if (0 < s.Length())
                return Extends::HashText();
        }
        if (GetHashFileName(s)) {
            XOS_LOG_DEBUG("file = \"" << s << "\"");
            if (0 < s.Length())
                return Extends::HashFile();
        }
        return Extends::HashBlank();
    }
    virtual bool HashFileUpdate() {
        return Extends::HashFileUpdate();
    }
    virtual bool HashCancel() {
        return Extends::HashCancel();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsUpperX(bool to = true) {
        return Extends::SetIsUpperX(to);
    }
    virtual bool GetIsUpperX() const {
        return Extends::GetIsUpperX();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline iHashControlView* SetControl(iHashControlView* control) {
        return m_controlView = control;
    }
    inline iHashControlView* GetControl() const {
        return m_controlView;
    }
    inline iHashControlView*& control() const {
        return (iHashControlView*&)(m_controlView);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static xos::crypto::hash::Interface& GetTheHash();
    static const char* GetTheHashName();
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetHashText(String& hashText) {
        if ((m_controlView)) {
            [m_controlView getText:hashText];
            return true;
        }
        return false;
    }
    virtual bool GetHashFileName(String& fileName) {
        if ((m_controlView)) {
            [m_controlView getFile:fileName];
            return true;
        }
        return false;
    }
    virtual bool PostUpdateFileHashEvent() {
        if ((m_thread) && (m_threadRun)) {
            m_threadRun->UpdateFileHash();
            return true;
        }
        return false;
    }
    virtual bool ShowHash(const String& hashX) {
        if ((m_controlView)) {
            [m_controlView setHash:hashX];
            return true;
        }
        return false;
    }
    virtual bool ClearHash() {
        if ((m_controlView)) {
            String hashText;
            [m_controlView setHash:hashText];
            return true;
        }
        return false;
    }
    virtual bool ShowProgress(size_t maximum, size_t amount) {
        if ((m_controlView)) {
            [m_controlView showProgress:maximum amount:amount];
            return true;
        }
        return false;
    }
    virtual bool UpdateProgress(size_t amount) {
        if ((m_controlView)) {
            [m_controlView updateProgress:amount];
            return true;
        }
        return false;
    }
    virtual bool HideProgress() {
        if ((m_controlView)) {
            [m_controlView hideProgress];
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    iHashControlView* m_controlView;
    ThreadRun* m_threadRun;
    Thread* m_thread;
};

} // namespace cocoa
} // namespace hash
} // namespace crypto
} // namespace gui
} // namespace xos

#endif // _XOS_GUI_COCOA_MAINWINDOW_HH
        

