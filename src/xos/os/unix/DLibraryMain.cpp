///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: DLibraryMain.cpp
///
/// Author: $author$
///   Date: 10/5/2016
///////////////////////////////////////////////////////////////////////
#include "xos/os/unix/DLibraryMain.hpp"
#include "xos/base/String.hpp"

#define XOS_STDERR_LOG_TRACE(_message) XOS_STDERR_LOG(_message)
#define XOS_STDERR_LOG_DEBUG(_message) XOS_STDERR_LOG(_message)
#define XOS_STDERR_LOG_ERROR(_message) XOS_STDERR_LOG(_message)
#define XOS_STDERR_LOG(_message) \
{   ::xos::String msg; msg << _message; \
    fprintf(stderr, "%s: %s\n", __FUNCTION__, msg.c_str()); }

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void DLIBRARY_INIT _init() {
    ::xos::DLibraryMain* theDLibraryMain = 0;

    XOS_STDERR_LOG_DEBUG("::xos::DLibraryMain::GetTheDLibraryMain()...");
    if ((theDLibraryMain = ::xos::DLibraryMain::GetTheDLibraryMain())) {

        XOS_STDERR_LOG_DEBUG("theDLibraryMain->Init()...");
        if (!(theDLibraryMain->Init())) {
            XOS_STDERR_LOG_ERROR("...failed on theDLibraryMain->Init()");
        }
    } else {
        XOS_STDERR_LOG_ERROR("...failed ::xos::DLibraryMain::GetTheDLibraryMain()");
    }
}
void DLIBRARY_FINI _fini() {
    ::xos::DLibraryMain* theDLibraryMain = 0;

    XOS_STDERR_LOG_DEBUG("::xos::DLibraryMain::GetTheDLibraryMain()...");
    if ((theDLibraryMain = ::xos::DLibraryMain::GetTheDLibraryMain())) {

        XOS_STDERR_LOG_DEBUG("theDLibraryMain->Fini()...");
        if (!(theDLibraryMain->Init())) {
            XOS_STDERR_LOG_ERROR("...failed on theDLibraryMain->Fini()");
        }
    } else {
        XOS_STDERR_LOG_ERROR("...failed ::xos::DLibraryMain::GetTheDLibraryMain()");
    }
}
