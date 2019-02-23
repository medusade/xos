///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: ArgList.hpp
///
/// Author: $author$
///   Date: 4/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_ARGLIST_HPP
#define _XOS_GUI_X11_XT_ARGLIST_HPP

#include "xos/gui/x11/xt/ArgArray.hpp"
#include "xos/base/List.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace x11 {
namespace xt {

class _EXPORT_CLASS ArgListItem;
typedef ListItem<ArgListItem> ArgListItemExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ArgListItem
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ArgListItem: public ArgListItemExtend {
public:
    typedef ArgListItemExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ArgListItem
    ///////////////////////////////////////////////////////////////////////
    ArgListItem(XtArg& xtArg, const XtChar* argName = 0, XtArgVal argValue = 0)
    : m_arg(xtArg, argName, argValue) {
    }
    virtual ~ArgListItem() {
    }
protected:
    Arg m_arg;
};

typedef List<ArgListItem> ArgItemListExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ArgItemList
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ArgItemList: public ArgItemListExtend {
public:
    typedef ArgItemListExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ArgItemList
    ///////////////////////////////////////////////////////////////////////
    ArgItemList() {
    }
    virtual ~ArgItemList() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Clear() {
        tItem* item;
        while ((item = PullItem())) {
            try { delete item; }
            catch (...) {
                XOS_LOG_ERROR("...caught exception");
                throw;
            }
        }
    }
};

typedef InterfaceBase ArgListImplement;
typedef ExportBase ArgListExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ArgList
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ArgList
: virtual public ArgListImplement, public ArgListExtend {
public:
    typedef ArgListImplement Implements;
    typedef ArgListExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ArgList
    ///////////////////////////////////////////////////////////////////////
    ArgList(const XtChar* argName, XtArgVal argValue, ...) {
        va_list va;
        va_start(va, argValue);
        AppendV(argName, argValue, va);
        va_end(va);
    }
    ArgList() {
    }
    virtual ~ArgList() {
        Clear();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtArgList SetGetV
    (const XtChar* argName, XtArgVal* argValue, va_list va) {
        XtArgList argList = 0;
        size_t args;
        ArgListItem* argItem;
        ArgElement* argArrayElement;
        size_t argArraySize;
        size_t argArrayLength;

        Clear();

        if ((argName) && (argValue))
        if (0 <= (args = m_argArray.Length()))
        if (args < (argArraySize = m_argArray.Size()))
        if ((argArrayElement = m_argArray.Elements()))
        {
            do {
                if ((argItem = new ArgListItem
                    (argArrayElement[args], argName, (XtArgVal)(argValue)))) {
                    if (0 >= (argArrayLength = m_argArray.SetLength(++args))) {
                        delete argItem;
                        break;
                    }
                    else
                    m_argList.AddItem(*argItem);

                    if ((argName = va_arg(va, const XtChar*)))
                    if ((argValue = va_arg(va, XtArgVal*)))
                        continue;
                }
                break;
            } while ((argName) && (argValue) && (args < argArraySize));

            argList = m_argArray.Elements();
        }
        return argList;
    }
    virtual size_t GetSetV
    (const XtChar* argName, XtArgVal* argValue, va_list va) const {
        size_t count = 0;
        size_t argArrayLength;
        ArgElement* argArrayElement;

        if ((argName) && (argValue))
        if (0 < (argArrayLength = m_argArray.Length()))
        if ((argArrayElement = m_argArray.Elements()))
        {
            do {
                argValue = (XtArgVal*)(argArrayElement[count].value);

                if (argArrayLength > (++count))
                if ((argName = va_arg(va, const XtChar*)))
                if ((argValue = va_arg(va, XtArgVal*)))
                    continue;
                break;
            } while ((argName) && (argValue) && (count < argArrayLength));
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtArgList Set
    (const XtChar* argName, XtArgVal argValue) {
        return SetL(argName, argValue, 0);
    }
    virtual XtArgList SetL
    (const XtChar* argName, XtArgVal argValue, ...) {
        XtArgList argList = 0;
        va_list va;
        va_start(va, argValue);
        argList = SetV(argName, argValue, va);
        va_end(va);
        return argList;
    }
    virtual XtArgList SetV
    (const XtChar* argName, XtArgVal argValue, va_list va) {
        return AssignV(argName, argValue, va);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Get
    (const XtChar** argName, XtArgVal* argValue) const {
        return GetL(argName, argValue, 0);
    }
    virtual size_t GetL
    (const XtChar** argName, XtArgVal* argValue, ...) const {
        size_t count = 0;
        va_list va;
        va_start(va, argValue);
        count = GetV(argName, argValue, va);
        va_end(va);
        return count;
    }
    virtual size_t GetV
    (const XtChar** argName, XtArgVal* argValue, va_list va) const {
        size_t count = 0;
        size_t argArrayLength;
        ArgElement* argArrayElement;

        if ((argName) && (argValue))
        if (0 < (argArrayLength = m_argArray.Length()))
        if ((argArrayElement = m_argArray.Elements()))
        {
            do
            {
                *argName = argArrayElement[count].name;
                *argValue = argArrayElement[count].value;

                if (argArrayLength > (++count))
                if ((argName = va_arg(va, const XtChar**)))
                if ((argValue = va_arg(va, XtArgVal*)))
                    continue;

                break;
            }
            while ((argName) && (argValue) && (count < argArrayLength));
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtArgList Assign
    (const XtChar* argName, XtArgVal argValue) {
        return AssignL(argName, argValue, 0);
    }
    virtual XtArgList AssignL
    (const XtChar* argName, XtArgVal argValue, ...) {
        XtArgList argList = 0;
        va_list va;
        va_start(va, argValue);
        argList = AssignV(argName, argValue, va);
        va_end(va);
        return argList;
    }
    virtual XtArgList AssignV
    (const XtChar* argName, XtArgVal argValue, va_list va) {
        Clear();
        return AppendV(argName, argValue, va);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtArgList Append
    (const XtChar* argName, XtArgVal argValue) {
        return AppendL(argName, argValue, 0);
    }
    virtual XtArgList AppendL
    (const XtChar* argName, XtArgVal argValue, ...) {
        XtArgList argList = 0;
        va_list va;
        va_start(va, argValue);
        argList = AppendV(argName, argValue, va);
        va_end(va);
        return argList;
    }
    virtual XtArgList AppendV
    (const XtChar* argName, XtArgVal argValue, va_list va) {
        XtArgList argList = 0;
        size_t args;
        ArgListItem* argItem;
        ArgElement* argArrayElement;
        size_t argArraySize;
        size_t argArrayLength;

        if (0 <= (args = m_argArray.Length()))
        if (args < (argArraySize = m_argArray.Size()))
        if ((argArrayElement = m_argArray.Elements()))
        {
            do
            {
                if ((argItem = new ArgListItem
                    (argArrayElement[args], argName, argValue)))
                {
                    if (0 > (argArrayLength = m_argArray.SetLength(++args)))
                    {
                        delete argItem;
                        break;
                    }
                    else
                    m_argList.AddItem(*argItem);

                    if ((argName = va_arg(va, const XtChar*)))
                    {
                        argValue = va_arg(va, XtArgVal);
                        continue;
                    }
                }
                break;
            }
            while ((argName) && (args < argArraySize));

            argList = m_argArray.Elements();
        }
        return argList;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Clear() {
        m_argList.Clear();
        m_argArray.Clear();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtArgList List() const {
        size_t length;
        return List(length);
    }
    virtual XtArgList List(size_t& length) const {
        XtArgList argList = 0;
        if (0 < (length = m_argArray.Length()))
        if (!(argList = m_argArray.Elements()))
            length = 0;
        return argList;
    }
    virtual size_t Length() const {
        return m_argArray.Length();
    }
    virtual operator XtArgList() const {
        return List();
    }
protected:
    ArgArray m_argArray;
    ArgItemList m_argList;
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_ARGLIST_HPP 
