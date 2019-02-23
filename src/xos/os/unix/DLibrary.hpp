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
///   File: DLibrary.hpp
///
/// Author: $author$
///   Date: 10/24/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_UNIX_DLIBRARY_HPP
#define _XOS_OS_UNIX_DLIBRARY_HPP

#include "xos/os/os/DLibrarySymbol.hpp"
#include "xos/os/DLibrary.hpp"
#include "xos/os/Logger.hpp"
#include "xos/fs/Path.hpp"
#include "xos/base/Opened.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace unix {

typedef DLibraryImplement DLibraryImplementImplement;

typedef AttachedImplement
<DLIBRARY_T, INVALID_DLIBRARY_T, INVALID_DLIBRARY,
 DLibraryImplementImplement> DLibraryImplement;

typedef Attached
<DLIBRARY_T, INVALID_DLIBRARY_T, INVALID_DLIBRARY,
 ExportBase, DLibraryImplement> DLibraryAttached;

typedef Opened
<DLIBRARY_T, INVALID_DLIBRARY_T, INVALID_DLIBRARY,
 DLibraryAttached, DLibraryImplement> DLibraryExtend;
///////////////////////////////////////////////////////////////////////
///  Class: DLibrary
///
/// Author: $author$
///   Date: 8/14/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DLibrary: virtual public DLibraryImplement, public DLibraryExtend {
public:
    typedef DLibraryImplement Implements;
    typedef DLibraryExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DLibrary(DLIBRARY_T attachedTo = INVALID_DLIBRARY, bool isOpen = false)
    : Extends(attachedTo, isOpen) {
    }
    virtual ~DLibrary() {
        if (!(Closed())) {
            Error error = Error::Failed;
            XOS_LOG_ERROR("failed on Closed()");
            throw(error);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open
    (const char* fileName, bool resolve = true, bool global = false) {
        if ((Closed())) {
            DLIBRARY_T detached = INVALID_DLIBRARY;
            if (INVALID_DLIBRARY != (OpenDetached(fileName, resolve, global))) {
                AttachOpened(detached);
                return true;
            }
        }
        return false;
    }
    virtual bool Close() {
        DLIBRARY_T detached = INVALID_DLIBRARY;
        if (INVALID_DLIBRARY != (detached = Detach())) {
            if ((CloseDetached(detached))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual DLIBRARY_T OpenDetached
    (const char* fileName, bool resolve = true, bool global = false) const {
        fs::Path path(fileName);

        if ((path.Separate())) {
            if (!(path.GetFileExtension().HasChars())) {
                path.Append(PATH_EXTENSION_SEPARATOR_CHARS);
                path.Append(DLIBRARY_FILE_EXTENSION_CHARS);
                fileName = path.Chars();
            }
        }

        if ((fileName)) {
            DLIBRARY_T detached = INVALID_DLIBRARY;
            int mode = ((resolve)?(RTLD_NOW):(RTLD_LAZY))
                       | ((global)?(RTLD_GLOBAL):(RTLD_LOCAL));

            XOS_LOG_DEBUG("dlopen(fileName, mode)...");
            if ((detached = dlopen(fileName, mode))) {
                return detached;
            } else {
                char *err = dlerror();
                XOS_LOG_ERROR("...failed err = \"" << err << "\" on dlopen(fileName, mode)");
            }
        }
        return INVALID_DLIBRARY;
    }
    virtual bool CloseDetached(DLIBRARY_T detached) const {
        if (INVALID_DLIBRARY != (detached)) {
        }
        return false;
    }
};

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_DLIBRARY_HPP 
        

