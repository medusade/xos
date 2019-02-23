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
///   File: Plaintext.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_PLAINTEXT_HPP
#define _XOS_TLS_PLAINTEXT_HPP

#include "xos/inet/tls/ContentType.hpp"
#include "xos/inet/tls/ProtocolVersion.hpp"

namespace xos {
namespace tls {

/* RFC 2246
    struct {
        ContentType type;
        ProtocolVersion version;
        uint16 length;
        opaque fragment[TLSPlaintext.length];
    } TLSPlaintext;
*/

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Plaintext: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;

    typedef Vector<opaque_t, sizeof(uint16_t), uint16_t> Fragment;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS FragmentReader
    : virtual public io::ReaderImplement, public io::Reader {
    public:
        typedef io::ReaderImplement Implements;
        typedef io::Reader Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        FragmentReader(const Fragment& fragment)
        : m_fragment(fragment),
          m_opaque(0), m_length(0), m_tell(0) {
        }
        FragmentReader(const FragmentReader& copy)
        : m_fragment(copy.m_fragment),
          m_opaque(0), m_length(0), m_tell(0) {
        }
        virtual ~FragmentReader() {}
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t Read(WhatT* what, size_t size) {
            opaque_t* to = 0;
            if ((to = (opaque_t*)what)) {
                opaque_t* from = 0;
                if ((from = opaque())) {
                    if (m_length < (m_tell + size)) {
                        size = m_length - m_tell;
                    }
                    if ((size)) {
                        Opaques::Copy(to, from + m_tell, size);
                        m_tell += size;
                    }
                    return size;
                }
            }
            return 0;
        }
        virtual ssize_t Seek(size_t size, io::Whence whence = io::FromBegin) {
            if ((opaque())) {
                switch(whence) {
                case io::FromBegin:
                    if (m_length < (m_tell = size)) {
                        m_tell = m_length;
                    }
                    break;
                case io::FromEnd:
                    if (m_length < (size)) {
                        m_tell = 0;
                    } else {
                        m_tell = m_length - size;
                    }
                    break;
                case io::FromCurrent:
                    if (m_length < (m_tell += size)) {
                        m_tell = m_length;
                    }
                    break;
                default:
                    return -1;
                    break;
                }
                return m_tell;
            }
            return -1;
        }
        virtual ssize_t Tell() const {
            return m_tell;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual opaque_t* opaque() {
            if (!(m_opaque)) {
                m_opaque = m_fragment.contents().Elements();
                m_length = m_fragment.contents().Length();
                m_tell = 0;
            }
            return m_opaque;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        const Fragment& m_fragment;
        opaque_t* m_opaque;
        size_t m_length, m_tell;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Plaintext(const ContentType& type, const ProtocolVersion& version)
    : m_type(type), m_version(version), m_fragment_reader(m_fragment) {}
    Plaintext(): m_fragment_reader(m_fragment) {}
    virtual ~Plaintext() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::Read()...");
        if (0 < (amount = ReadType(reader))) {
            count += amount;
            if (0 < (amount = m_version.Read(reader))) {
                count += amount;
                if (0 < (amount = ReadFragment(reader))) {
                    count += amount;
                    XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::Read()");
                }
            }
        }
        return count;
    }
    virtual ssize_t ReadFragment(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        uint16_t fragment_length = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::ReadMsb()...");
        if (0 < (amount = ReadMsb(reader, fragment_length, sizeof(fragment_length)))) {
            opaque_t* fragment_contents = 0;
            count += amount;
            XOS_LOG_MESSAGE_DEBUG("...fragment_length = " << fragment_length << " on " << __XOS_LOGGER_CLASS__ << "::ReadMsb()");
            if ((fragment_contents = m_fragment.set_contents_length(fragment_length))) {
                if (0 < (amount = ReadOpaque(reader, fragment_contents, fragment_length))) {
                    count += amount;
                }
            }
        }
        return count;
    }
    virtual ssize_t ReadType(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (0 < (amount = ReadMsb(reader, m_type, sizeof(m_type)))) {
            count += amount;
            switch (m_type) {
            case CONTENT_TYPE_CHANGE_CIPHER_SPEC:
                XOS_LOG_MESSAGE_DEBUG("...CONTENT_TYPE_CHANGE_CIPHER_SPEC = " << m_type << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case CONTENT_TYPE_ALERT:
                XOS_LOG_MESSAGE_DEBUG("...CONTENT_TYPE_ALERT = " << m_type << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case CONTENT_TYPE_HANDSHAKE:
                XOS_LOG_MESSAGE_DEBUG("...CONTENT_TYPE_HANDSHAKE = " << m_type << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case CONTENT_TYPE_APPLICATION_DATA:
                XOS_LOG_MESSAGE_DEBUG("...CONTENT_TYPE_APPLICATION_DATA = " << m_type << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case CONTENT_TYPE_HEARTBEAT:
                XOS_LOG_MESSAGE_DEBUG("...ONTENT_TYPE_HEARTBEAT = " << m_type << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            default:
                XOS_LOG_MESSAGE_DEBUG("...unexpected type = " << m_type << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                count = 0;
                break;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::Write()...");
        if (0 < (amount = WriteMsb(writer, m_type, sizeof(m_type)))) {
            count += amount;
            if (0 < (amount = m_version.Write(writer))) {
                count += amount;
                if (0 < (amount = m_fragment.Write(writer))) {
                    count += amount;
                    XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::Write()");
                }
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer, Implement& fragment) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::Write()...");
        if (0 < (amount = WriteMsb(writer, m_type, sizeof(m_type)))) {
            count += amount;
            if (0 < (amount = m_version.Write(writer))) {
                count += amount;
                if (0 < (amount = fragment.SizeOf())) {
                    uint16_t length = (uint16_t)(amount);
                    XOS_LOG_MESSAGE_DEBUG("fragment length = " << length << "");
                    if (0 < (amount = WriteMsb(writer, length, sizeof(uint16_t)))) {
                        count += amount;
                        if (0 < (amount = fragment.Write(writer))) {
                            count += amount;
                            XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::Write()");
                        }
                    }
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ContentType& set_type(const ContentType& to) {
        m_type = to;
        return m_type;
    }
    virtual const ContentType& type() const {
        return m_type;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Fragment& set_fragment(const Fragment& to) {
        m_fragment.Assign(to);
        return m_fragment;
    }
    virtual const Fragment& fragment() const {
        return m_fragment;
    }
    virtual FragmentReader& fragment_reader() const {
        return (FragmentReader&)m_fragment_reader;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += sizeof(m_type);
        count += m_version.SizeOf();
        count += m_fragment.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ContentType m_type;
    ProtocolVersion m_version;
    Fragment m_fragment;
    FragmentReader m_fragment_reader;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_PLAINTEXT_HPP 
