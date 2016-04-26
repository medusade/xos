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
///   File: Base.hpp
///
/// Author: $author$
///   Date: 4/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_BASE_HPP
#define _XOS_TLS_BASE_HPP

#include "xos/inet/tls/Protocol.hpp"
#include "xos/io/Stream.hpp"
#include "xos/io/Reader.hpp"
#include "xos/io/Writer.hpp"
#include "xos/base/String.hpp"
#include "xos/base/Array.hpp"
#include "xos/base/Types.hpp"
#include "xos/base/Base.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace tls {

typedef uint8_t opaque_t;
typedef TypesT<opaque_t> Opaques;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Implement: virtual public InterfaceBase {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadLsb(io::Reader& r, uint8_t& value, size_t size) {
        ssize_t count = 0;
        uint32_t value32 = 0;
        if (0 < (count = ReadLsb(r, value32, size)))
            value = value32;
        return count;
    }
    virtual ssize_t ReadLsb(io::Reader& r, uint16_t& value, size_t size) {
        ssize_t count = 0;
        uint32_t value32 = 0;
        if (0 < (count = ReadLsb(r, value32, size)))
            value = value32;
        return count;
    }
    virtual ssize_t ReadLsb(io::Reader& r, uint32_t& value, size_t size) {
        ssize_t count = 0;
        uint8_t bytes[sizeof(uint32_t)];

        if (sizeof(uint32_t) <= (size)) {
            size = sizeof(uint32_t);
        }
        value = 0;
        if (0 < (size)) {
            if (0 < (count = r.Read(bytes, size))) {
                XString x(bytes, size);
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << " read " << x << "");
                for (size_t i = size; size; --size, --i) {
                    value <<= 8; value |= bytes[i-1];
                }
            }
        }
        return count;
    }
    virtual ssize_t WriteLsb(io::Writer& w, uint32_t value, size_t size) {
        ssize_t count = 0;
        uint8_t bytes[sizeof(uint32_t)];

        if (sizeof(uint32_t) <= (size))
            size = sizeof(uint32_t);

        for (size_t i = 0; i < size; ++i, value >>= 8)
            bytes[i] = (value & 0xFF);

        if (0 < (size)) {
            XString x(bytes, size);
            XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << " write " << x << "...");
            if (0 < (count = w.Write(bytes, size))) {
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << " wrote " << x << "");
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadMsb(io::Reader& r, uint8_t& value, size_t size) {
        ssize_t count = 0;
        uint32_t value32 = 0;
        if (0 < (count = ReadMsb(r, value32, size)))
            value = value32;
        return count;
    }
    virtual ssize_t ReadMsb(io::Reader& r, uint16_t& value, size_t size) {
        ssize_t count = 0;
        uint32_t value32 = 0;
        if (0 < (count = ReadMsb(r, value32, size)))
            value = value32;
        return count;
    }
    virtual ssize_t ReadMsb(io::Reader& r, uint32_t& value, size_t size) {
        ssize_t count = 0;
        uint8_t bytes[sizeof(uint32_t)];

        if (sizeof(uint32_t) <= (size)) {
            size = sizeof(uint32_t);
        }
        value = 0;
        if (0 < (size)) {
            if (0 < (count = r.Read(bytes, size))) {
                XString x(bytes, size);
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << " read " << x << "");
                for (size_t i = 0; i < size; ++i) {
                    value <<= 8; value |= bytes[i];
                }
            }
        }
        return count;
    }
    virtual ssize_t WriteMsb(io::Writer& w, uint32_t value, size_t size) {
        ssize_t count = 0;
        uint8_t bytes[sizeof(uint32_t)];

        if (sizeof(uint32_t) <= (size))
            size = sizeof(uint32_t);

        for (size_t i = 0; i < size; ++i, value >>= 8)
            bytes[(sizeof(uint32_t)-1)-i] = (value & 0xFF);

        if (0 < (size)) {
            size_t i = sizeof(uint32_t)-size;
            XString x(bytes+i, size);
            XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << " write " << x << "...");
            if (0 < (count = w.Write(bytes+i, size))) {
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << " wrote " << x << "");
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadOpaque(io::Reader& r, uint8_t* bytes, size_t size) {
        ssize_t count = 0;
        if ((bytes) && (size)) {
            if (0 < (count = r.Read(bytes, size))) {
                XString x(bytes, size);
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << " read " << x << "");
            }
        }
        return count;
    }
    virtual ssize_t WriteOpaque(io::Writer& w, const uint8_t* bytes, size_t size) {
        ssize_t count = 0;
        if ((bytes) && (size)) {
            XString x(bytes, size);
            XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << " write " << x << "...");
            if (0 < (count = w.Write(bytes, size))) {
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << " wrote " << x << "");
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        return count;
    }
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Extend: virtual public Implement, public ExportBase {
public:
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Base: virtual public Implement, public Extend {
public:
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Uint24: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Uint24(uint32_t value = 0): m_value(value) {}
    virtual ~Uint24() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = ReadMsb(reader, m_value, 3);
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = WriteMsb(writer, m_value, 3);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 3;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t SetValue(uint32_t to) {
        m_value = to;
        return m_value;
    }
    virtual uint32_t Value() const {
        return m_value;
    }
    virtual operator uint32_t() const {
        return m_value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint32_t m_value;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template <typename TWhat, size_t VLengthSize, typename TLength = size_t>
class _EXPORT_CLASS Vector: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    typedef Array<TWhat> TContents;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Vector(const TWhat* values, TLength count): m_length(0)  {
        if (0 < (m_length = (sizeof(TWhat)*count))) {
            m_contents.Assign(values, count);
        }
    }
    Vector(const TWhat& value, TLength count): m_length(0)  {
        if (0 < (m_length = (sizeof(TWhat)*count))) {
            m_contents.Set(value, count);
        }
    }
    Vector(const Vector& copy)
    : m_length(copy.length()), m_contents(copy.contents()) {
    }
    Vector(): m_length(0) {}
    virtual ~Vector() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Assign(const Vector& copy) {
        size_t count = 0;
        if (0 < (count = set_length(copy.length()))) {
            set_contents(copy.contents());
            return count;
        } else {
            clear_contents();
        }
        return 0;
    }
    virtual size_t Assign(const TWhat* values, TLength count) {
        if (0 < (m_length = (sizeof(TWhat)*count))) {
            return m_contents.Assign(values, count);
        }
        return 0;
    }
    virtual size_t Set(const TWhat& value, TLength count) {
        if (0 < (m_length = (sizeof(TWhat)*count))) {
            return m_contents.Set(value, count);
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        uint8_t* bytes;
        size_t length;
        if (0 < (amount = this->ReadMsb(reader, m_length, VLengthSize))) {
            count += amount;
            if (0 < (m_length)) {
                if ((bytes = (uint8_t*)(set_contents_length(m_length)))) {
                    if (0 < (amount = this->ReadOpaque(reader, bytes, length*sizeof(TWhat)))) {
                        count += amount;
                    }
                }
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        const uint8_t* bytes;
        size_t length;
        if (0 < (amount = this->WriteMsb(writer, m_length, VLengthSize))) {
            count += amount;
            if ((bytes = (const uint8_t*)(m_contents.Elements())) && (length = m_contents.Length())) {
                if (0 < (amount = this->WriteOpaque(writer, bytes, length*sizeof(TWhat)))) {
                    count += amount;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TLength set_length(TLength to) {
        m_length = to;
        return m_length;
    }
    virtual TLength length() const {
        return m_length;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TContents& set_contents(const TWhat* to, TLength count) {
        m_contents.Assign(to, count);
        return m_contents;
    }
    virtual TContents& set_contents(const TContents& to) {
        m_contents.Assign(to.Elements(), to.Length());
        return m_contents;
    }
    virtual TContents& clear_contents() {
        m_contents.Clear();
        return m_contents;
    }
    virtual const TContents& contents() const {
        return m_contents;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TWhat* set_contents_length(TLength to) {
        m_contents.SetLength(to);
        return m_contents.Elements();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += VLengthSize;
        count += m_contents.Length()*VLengthSize;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TLength m_length;
    TContents m_contents;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_BASE_HPP 
