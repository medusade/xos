///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: Token.hpp
///
/// Author: $author$
///   Date: 10/19/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_TOKEN_HPP
#define _XOS_WEBRTC_CLIENT_TOKEN_HPP

#include "xos/base/String.hpp"

namespace xos {
namespace webrtc {
namespace client {

class _EXPORT_CLASS Token {
public:
    Token(const std::string& peerName): m_peerName(peerName) {
    }
    Token(const char* peerName = 0) {
        if ((peerName)) m_peerName = peerName;
    }
    virtual ~Token() {}

    virtual bool Make(std::string& name) {
        if ((CombineFields(GetPeerFields(), name))) {
            //
            // Structured name
            //
            return true;
        } else {
            if ((0 < (m_peerName.length()))) {
                //
                // String name
                //
                name = m_peerName;
                return true;
            }
        }
        return false;
    }
    virtual bool CheckIsValid(const std::string& name) {
        std::string peerName;
        if ((SeparateFields(GetFields(), name))) {
            //
            // Structured name
            //
            if ((CombineFields(GetPeerFields(), peerName))) {
                return peerName != name;
            }
        } else {
            if ((0 < (name.length())) && (0 < (m_peerName.length()))) {
                //
                // String name
                //
                return m_peerName != name;
            }
        }
        return false;
    }

    virtual void Clear() {
        m_peerName.clear();
    }
    virtual void SetPeerName(const char* chars) {
        if ((chars)) {
            Clear();
            m_peerName.assign(chars);
        }
    }
    virtual const char* GetPeerName() const {
        const char* chars = 0;
        chars = m_peerName.c_str();
        return chars;
    }

    virtual void PrintFields(std::string& text) {
        Fields& fields = GetFields();
        fields.Print(text);
    }

protected:
    class _EXPORT_CLASS Fields {
    public:
        virtual ~Fields(){}
        virtual void Print(std::string& text) {
        }
    };

    virtual bool CombineFields(const Fields& fields, std::string& name) {
        return false;
    }
    virtual bool SeparateFields(Fields& fields, const std::string& name) {
        return false;
    }
    virtual Fields& GetPeerFields() const {
        return (Fields&)(m_peerFields);
    }
    virtual Fields& GetFields() const {
        return (Fields&)(m_fields);
    }

protected:
    std::string m_peerName;
    Fields m_peerFields;
    Fields m_fields;
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_TOKEN_HPP 
