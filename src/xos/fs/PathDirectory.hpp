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
///   File: PathDirectory.hpp
///
/// Author: $author$
///   Date: 10/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_PATHDIRECTORY_HPP
#define _XOS_FS_PATHDIRECTORY_HPP

#include "xos/base/String.hpp"

#if defined(WINDOWS) 
// Windows 
#define FORIEGN_PATH_DIRECTORY_SEPARATOR_CHAR '/'
#define NATIVE_PATH_DIRECTORY_SEPARATOR_CHAR '\\'
#define NORMAL_PATH_DIRECTORY_SEPARATOR_CHAR FORIEGN_PATH_DIRECTORY_SEPARATOR_CHAR

#define FORIEGN_PATH_DIRECTORY_SEPARATOR_CHARS "/"
#define NATIVE_PATH_DIRECTORY_SEPARATOR_CHARS "\\"
#define NORMAL_PATH_DIRECTORY_SEPARATOR_CHARS FORIEGN_PATH_DIRECTORY_SEPARATOR_CHARS

#define FORIEGN_PATH_VOLUME_SEPARATOR_CHAR '/'
#define NATIVE_PATH_VOLUME_SEPARATOR_CHAR ':'
#define NORMAL_PATH_VOLUME_SEPARATOR_CHAR NATIVE_PATH_VOLUME_SEPARATOR_CHAR

#define FORIEGN_PATH_VOLUME_SEPARATOR_CHARS "/"
#define NATIVE_PATH_VOLUME_SEPARATOR_CHARS ":"
#define NORMAL_PATH_VOLUME_SEPARATOR_CHARS NATIVE_PATH_VOLUME_SEPARATOR_CHARS
#else // defined(WINDOWS) 
// Unix 
#define FORIEGN_PATH_DIRECTORY_SEPARATOR_CHAR '\\'
#define NATIVE_PATH_DIRECTORY_SEPARATOR_CHAR '/'
#define NORMAL_PATH_DIRECTORY_SEPARATOR_CHAR NATIVE_PATH_DIRECTORY_SEPARATOR_CHAR

#define FORIEGN_PATH_DIRECTORY_SEPARATOR_CHARS "\\"
#define NATIVE_PATH_DIRECTORY_SEPARATOR_CHARS "/"
#define NORMAL_PATH_DIRECTORY_SEPARATOR_CHARS NATIVE_PATH_DIRECTORY_SEPARATOR_CHARS

#define FORIEGN_PATH_VOLUME_SEPARATOR_CHAR ':'
#define NATIVE_PATH_VOLUME_SEPARATOR_CHAR '/'
#define NORMAL_PATH_VOLUME_SEPARATOR_CHAR FORIEGN_PATH_VOLUME_SEPARATOR_CHAR

#define FORIEGN_PATH_VOLUME_SEPARATOR_CHARS ":"
#define NATIVE_PATH_VOLUME_SEPARATOR_CHARS "/"
#define NORMAL_PATH_VOLUME_SEPARATOR_CHARS FORIEGN_PATH_VOLUME_SEPARATOR_CHARS
#endif // defined(WINDOWS) 

#define PATH_DIRECTORY_WILDCARD_CHAR '*'
#define PATH_DIRECTORY_WILDCARD_CHARS "*"

namespace xos {
namespace fs {

class _EXPORT_CLASS PathDirectoryImplement {
public:
    class _EXPORT_CLASS Type {
    public:
        enum Id {
            Named = 0,
            Current,
            Parent,
            Root,

            Next,
            First = Named,
            Last = (Next - 1),
            Count = (Last - First + 1)
        };
        Type(const Type& copy): m_id(copy.m_id) {
        }
        Type(Id id = Named): m_id(id) {
        }
        operator Id() const {
            return m_id;
        }
    protected:
        Id m_id;
    };
};

template <typename TChar = char, class TExtend = String, class TImplement = PathDirectoryImplement>

class _EXPORT_CLASS PathDirectoryT: virtual public TImplement, public TExtend {
public:
    typedef TExtend Extends;

    PathDirectoryT(PathDirectoryImplement::Type type, const char* name, size_t length): Extends(name, length), m_type(type) {
    }
    PathDirectoryT(PathDirectoryImplement::Type type, const char* name): Extends(name), m_type(type) {
    }
    PathDirectoryT(PathDirectoryImplement::Type type, const wchar_t* name, size_t length): Extends(name, length), m_type(type) {
    }
    PathDirectoryT(PathDirectoryImplement::Type type, const wchar_t* name): Extends(name), m_type(type) {
    }
    PathDirectoryT(const PathDirectoryT& copy): Extends(copy), m_type(copy.m_type) {
    }
protected:
    PathDirectoryImplement::Type m_type;
};

typedef PathDirectoryT<char, String> PathDirectory;
typedef PathDirectoryT<wchar_t, WString> WPathDirectory;
typedef PathDirectoryT<tchar_t, TString> TPathDirectory;

} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_PATHDIRECTORY_HPP 
