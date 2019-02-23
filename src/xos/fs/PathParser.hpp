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
///   File: PathParser.hpp
///
/// Author: $author$
///   Date: 10/28/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_PATHPARSER_HPP
#define _XOS_FS_PATHPARSER_HPP

#include "xos/fs/PathParserEvents.hpp"
#include "xos/base/String.hpp"

namespace xos {
namespace fs {

template <typename TChar = char, class TEvents = PathParserEvents, class TExtend = ExportBase, class TImplement = InterfaceBase>

class _EXPORT_CLASS PathParserT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef PathParserT Derives, CDerives;

    PathParserT(TEvents& events)
    : m_dot('.'), m_events(events), 
      m_put(0), m_oldPut(0), m_final(0) {}
    virtual ~PathParserT() {}

    virtual bool Init() {
        m_oldPut = (m_put = &Derives::InitialPut);
        m_final = &Derives::Final;
        m_token.Clear();
        m_token2.Clear();
        return m_events.OnInit();
    }
    virtual bool Fini() {
        bool isTrue = false;
        if ((m_final)) {
            if ((isTrue = (this->*m_final)())) {
                isTrue = m_events.OnFini();
            }
        }
        m_oldPut = (m_put = 0);
        m_final = 0;
        m_token.Clear();
        m_token2.Clear();
        return isTrue;
    }

    virtual bool Write(const TChar* chars, ssize_t length = -1) {
        if ((chars)) {
            if (0 < (length)) {
                while (0 < (length--)) {
                    if (!(Put(*chars++))) {
                        return false;
                    }
                }
                return true;
            } else {
                for (length = 0; *chars != (TChar)(0); length++) {
                    if (!(Put(*chars++))) {
                        return false;
                    }
                }
                return (0 < (length));
            }
        }
        return false;
    }
    virtual bool Put(const TChar& c) {
        if ((m_put)) {
            return (this->*m_put)(c);
        }
        return false;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    //
    // Final
    //
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // E
    ///////////////////////////////////////////////////////////////////////
    bool Final() {
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/''/'A*E
    ///////////////////////////////////////////////////////////////////////
    bool HostFinal() {
        size_t length = 0;
        const TChar* chars;
        if ((chars = m_token.Chars(length)))
            m_events.OnHost(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/''.'E
    ///////////////////////////////////////////////////////////////////////
    bool RootCurrentFinal() {
        size_t length = 0;
        const TChar* chars;
        m_token.Append(&m_dot, 1);
        if ((chars = m_token.Chars(length)))
            m_events.OnRootCurrentDirectory(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/''.''.'E
    ///////////////////////////////////////////////////////////////////////
    bool RootParentFinal() {
        size_t length = 0;
        const TChar* chars;
        m_token.Append(&m_dot, 1);
        m_token.Append(&m_dot, 1);
        if ((chars = m_token.Chars(length)))
            m_events.OnRootParentDirectory(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '.'E
    ///////////////////////////////////////////////////////////////////////
    bool CurrentFinal() {
        size_t length = 0;
        const TChar* chars;
        m_token.Append(&m_dot, 1);
        if ((chars = m_token.Chars(length)))
            m_events.OnCurrentDirectory(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '.''.'E
    ///////////////////////////////////////////////////////////////////////
    bool ParentFinal() {
        size_t length = 0;
        const TChar* chars;
        m_token.Append(&m_dot, 1);
        m_token.Append(&m_dot, 1);
        if ((chars = m_token.Chars(length)))
            m_events.OnParentDirectory(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+'.'A+E
    ///////////////////////////////////////////////////////////////////////
    bool RootNameExtensionFinal() {
        size_t length = 0;
        const TChar* chars;
        if ((chars = m_token.Chars(length)))
            m_events.OnRootFileName(chars, length);
        if ((chars = m_token2.Chars(length)))
            m_events.OnFileExtension(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/'A+E
    ///////////////////////////////////////////////////////////////////////
    bool RootNameFinal() {
        size_t length = 0;
        const TChar* chars;
        if ((chars = m_token.Chars(length)))
            m_events.OnRootFileName(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/'A+'.'E
    ///////////////////////////////////////////////////////////////////////
    bool RootNameDotFinal() {
        size_t length = 0;
        const TChar* chars;
        m_token.Append(&m_dot, 1);
        if ((chars = m_token.Chars(length)))
            m_events.OnRootFileName(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+'.'A+E
    ///////////////////////////////////////////////////////////////////////
    bool NameExtensionFinal() {
        size_t length = 0;
        const TChar* chars;
        if ((chars = m_token.Chars(length)))
            m_events.OnFileName(chars, length);
        if ((chars = m_token2.Chars(length)))
            m_events.OnFileExtension(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+E
    ///////////////////////////////////////////////////////////////////////
    bool NameFinal() {
        size_t length = 0;
        const TChar* chars;
        if ((chars = m_token.Chars(length)))
            m_events.OnFileName(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+'.'E
    ///////////////////////////////////////////////////////////////////////
    bool NameDotFinal() {
        size_t length = 0;
        const TChar* chars;
        m_token.Append(&m_dot, 1);
        if ((chars = m_token.Chars(length)))
            m_events.OnFileName(chars, length);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+'.'A+E
    ///////////////////////////////////////////////////////////////////////
    bool ExtensionFinal() {
        size_t length = 0;
        const TChar* chars;
        if ((chars = m_token.Chars(length)))
            m_events.OnFileExtension(chars, length);
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    //
    // Put
    //
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // A*?
    ///////////////////////////////////////////////////////////////////////
    bool InitialPut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                // A+'/'
                m_events.OnDirectory(chars, length);
                m_token.Clear();
                m_put = &CDerives::NamePut;
                m_final = &CDerives::Final;
            }
            else 
            {
                // '/'
                m_put = &CDerives::HostPut;
                m_final = &CDerives::RootNameFinal;
            }
            break;
        case ':':
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                // A+':'
                m_events.OnVolume(chars, length);
                m_token.Clear();
            }
            m_put = &CDerives::RootPut;
            m_final = &CDerives::Final;
            break;
        case '.':
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                // A+'.'
                m_oldPut = &CDerives::NamePut;
                m_put = &CDerives::ExtensionPut;
                m_final = &CDerives::NameDotFinal;
            }
            else
            {
                // '.' 
                m_put = &CDerives::CurrentPut;
                m_final = &CDerives::CurrentFinal;
            }
            break;
        default:
            // A
            m_token.Append(&c, 1);
            m_final = &CDerives::NameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+'/'+?
    ///////////////////////////////////////////////////////////////////////
    bool DirectoryPut(const TChar& c) {
        switch((char)(c))
        {
        case '/':
        case '\\':
            // A+'/'+'/'
            break;
        case '.':
            // A+'/'+'.'
            m_put = &CDerives::CurrentPut;
            m_final = &CDerives::CurrentFinal;
            break;
        default:
            // A+'/'+A
            m_token.Append(&c, 1);
            m_put = &CDerives::NamePut;
            m_final = &CDerives::NameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/'?
    ///////////////////////////////////////////////////////////////////////
    bool HostPut(const TChar& c) {
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '/''/'
            m_put = &CDerives::HostNamePut;
            m_final = &CDerives::Final;
            break;
        case '.':
            // '/''.'
            m_put = &CDerives::RootCurrentPut;
            m_final = &CDerives::RootCurrentFinal;
            break;
        default:
            // '/'A
            m_token.Append(&c, 1);
            m_put = &CDerives::RootNamePut;
            m_final = &CDerives::RootNameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/''/'A*?
    ///////////////////////////////////////////////////////////////////////
    bool HostNamePut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '/''/'A*'/'
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnHost(chars, length);
                m_token.Clear();
            }
            m_put = &CDerives::RootNamePut;
            m_final = &CDerives::Final;
            break;
        default:
            // '/''/'A+
            m_token.Append(&c, 1);
            m_final = &CDerives::HostFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '.'?
    ///////////////////////////////////////////////////////////////////////
    bool CurrentPut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '.''/'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnCurrentDirectory(chars, length);
                m_token.Clear();
            }
            m_put = &CDerives::DirectoryPut;
            m_final = &CDerives::Final;
            break;
        case '.':
            // '.''.'
            m_put = &CDerives::ParentPut;
            m_final = &CDerives::ParentFinal;
            break;
        default:
            // '.'A
            m_token.Append(&m_dot, 1);
            m_token.Append(&c, 1);
            m_put = &CDerives::NamePut;
            m_final = &CDerives::NameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/''.'?
    ///////////////////////////////////////////////////////////////////////
    bool RootCurrentPut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '/''.''/'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnRootCurrentDirectory(chars, length);
                m_token.Clear();
            }
            m_put = &CDerives::DirectoryPut;
            m_final = &CDerives::Final;
            break;
        case '.':
            // '/''.''.'
            m_put = &CDerives::RootParentPut;
            m_final = &CDerives::RootParentFinal;
            break;
        default:
            // '/''.'A
            m_token.Append(&m_dot, 1);
            m_token.Append(&c, 1);
            m_put = &CDerives::RootNamePut;
            m_final = &CDerives::RootNameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '.''.'?
    ///////////////////////////////////////////////////////////////////////
    bool ParentPut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '.''.''/'
            m_token.Append(&m_dot, 1);
            m_token.Append(&m_dot, 1);
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnParentDirectory(chars, length);
                m_token.Clear();
            }
            m_put = &CDerives::DirectoryPut;
            m_final = &CDerives::Final;
            break;
        case '.':
            // '.''.''.'
        default:
            // '.''.'A
            m_token.Append(&m_dot, 1);
            m_token.Append(&m_dot, 1);
            m_token.Append(&c, 1);
            m_put = &CDerives::NamePut;
            m_final = &CDerives::NameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/''.''.'?
    ///////////////////////////////////////////////////////////////////////
    bool RootParentPut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '/''.''.''/'
            m_token.Append(&m_dot, 1);
            m_token.Append(&m_dot, 1);
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnRootParentDirectory(chars, length);
                m_token.Clear();
            }
            m_put = &CDerives::DirectoryPut;
            m_final = &CDerives::Final;
            break;
        case '.':
            // '/''.''.''.'
        default:
            // '/''.''.'A
            m_token.Append(&m_dot, 1);
            m_token.Append(&c, 1);
            m_put = &CDerives::RootNamePut;
            m_final = &CDerives::RootNameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+':'?
    ///////////////////////////////////////////////////////////////////////
    bool RootPut(const TChar& c) {
        switch((char)(c))
        {
        case '/':
        case '\\':
            // A+':''/'
            m_put = &CDerives::RootNamePut;
            m_final = &CDerives::Final;
            break;
        case '.':
            // A+':''.'
            m_put = &CDerives::ParentPut;
            m_final = &CDerives::CurrentFinal;
            break;
        default:
            // A+':'A
            m_token.Append(&c, 1);
            m_put = &CDerives::NamePut;
            m_final = &CDerives::NameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/'A+?
    ///////////////////////////////////////////////////////////////////////
    bool RootNamePut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '/'A+'/'
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnRootDirectory(chars, length);
                m_token.Clear();
            }
            m_put = &CDerives::NamePut;
            m_final = &CDerives::Final;
            break;
        case '.':
            // '/'A+'.'
            m_oldPut = &CDerives::RootNamePut;
            m_put = &CDerives::RootExtensionPut;
            m_final = &CDerives::RootNameDotFinal;
            break;
        default:
            // '/'A+
            m_token.Append(&c, 1);
            m_final = &CDerives::RootNameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+?
    ///////////////////////////////////////////////////////////////////////
    bool NamePut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // A+'/'
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnDirectory(chars, length);
                m_token.Clear();
            }
            m_final = &CDerives::Final;
            break;
        case '.':
            // A+'.'
            m_oldPut = &CDerives::NamePut;
            m_put = &CDerives::ExtensionPut;
            m_final = &CDerives::NameDotFinal;
            break;
        default:
            // A+
            m_token.Append(&c, 1);
            m_final = &CDerives::NameFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+'.'?
    ///////////////////////////////////////////////////////////////////////
    bool ExtensionPut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // A+'.''/'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnDirectory(chars, length);
                m_token.Clear();
            }
            m_put = m_oldPut;
            break;
        case '.':
            // A+'.''.'
            m_token.Append(&m_dot, 1);
            m_token.Append(&m_dot, 1);
            m_put = m_oldPut;
            m_final = &CDerives::NameFinal;
            break;
        default:
            // A+'.'A
            m_token2.Append(&c, 1);
            m_put = &CDerives::ExtensionNamePut;
            m_final = &CDerives::NameExtensionFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // A+'.'A+?
    ///////////////////////////////////////////////////////////////////////
    bool ExtensionNamePut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // A+'.'A+'/'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token2.Chars
                (length)) && (0 < length))
            {
                m_token.Append(chars, length);
                m_token2.Clear();
            }
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnDirectory(chars, length);
                m_token.Clear();
            }
            m_put = m_oldPut;
            break;
        case '.':
            // A+'.'A+'.'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token2.Chars
                (length)) && (0 < length))
            {
                m_token.Append(chars, length);
                m_token2.Clear();
            }
            m_final = &CDerives::NameDotFinal;
            break;
        default:
            // A+'.'A+
            m_token2.Append(&c, 1);
            m_final = &CDerives::NameExtensionFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/'A+'.'?
    ///////////////////////////////////////////////////////////////////////
    bool RootExtensionPut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '/'A+'.''/'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnRootDirectory(chars, length);
                m_token.Clear();
            }
            m_put = m_oldPut;
            break;
        case '.':
            // '/'A+'.''.'
            m_token.Append(&m_dot, 1);
            m_token.Append(&m_dot, 1);
            m_put = m_oldPut;
            m_final = &CDerives::RootNameFinal;
            break;
        default:
            // '/'A+'.'A
            m_token2.Append(&c, 1);
            m_put = &CDerives::RootExtensionNamePut;
            m_final = &CDerives::RootNameExtensionFinal;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    // '/'A+'.'A+?
    ///////////////////////////////////////////////////////////////////////
    bool RootExtensionNamePut(const TChar& c) {
        size_t length = 0;
        const TChar* chars;
        switch((char)(c))
        {
        case '/':
        case '\\':
            // '/'A+'.'A+'/'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token2.Chars
                (length)) && (0 < length))
            {
                m_token.Append(chars, length);
                m_token2.Clear();
            }
            if ((chars = m_token.Chars
                (length)) && (0 < length))
            {
                m_events.OnRootDirectory(chars, length);
                m_token.Clear();
            }
            m_put = m_oldPut;
            break;
        case '.':
            // '/'A+'.'A+'.'
            m_token.Append(&m_dot, 1);
            if ((chars = m_token2.Chars
                (length)) && (0 < length))
            {
                m_token.Append(chars, length);
                m_token2.Clear();
            }
            m_final = &CDerives::RootNameDotFinal;
            break;
        default:
            // '/'A+'.'A+
            m_token2.Append(&c, 1);
            m_final = &CDerives::RootNameExtensionFinal;
        }
        return true;
    }

protected:
    typedef bool (Derives::*MPut)(const TChar& c);
    typedef bool (Derives::*MFinal)();

    const char m_dot;

    TEvents& m_events;
    MPut m_put;
    MPut m_oldPut;
    MFinal m_final;
    StringT<TChar> m_token;
    StringT<TChar> m_token2;
};

typedef PathParserT<char, PathParserEvents> PathParser;
typedef PathParserT<wchar_t, WPathParserEvents> WPathParser;
typedef PathParserT<tchar_t, TPathParserEvents> TPathParser;

} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_PATHPARSER_HPP 
