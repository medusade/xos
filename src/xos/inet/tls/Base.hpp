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
#include "xos/io/Reader.hpp"
#include "xos/io/Writer.hpp"
#include "xos/base/String.hpp"
#include "xos/base/Array.hpp"
#include "xos/base/Types.hpp"
#include "xos/base/Base.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace tls {

typedef uint8_t opaque;
typedef TypesT<opaque> Opaque;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Implement: virtual public InterfaceBase {
public:
    virtual ssize_t WriteLsb(io::Writer& w, uint32_t value, size_t size) {
        ssize_t count = 0;
        uint8_t bytes[sizeof(uint32_t)];

        if (sizeof(uint32_t) <= (size))
            size = sizeof(uint32_t);

        for (size_t i = 0; i < size; ++i, value >>= 8)
            bytes[i] = (value & 0xFF);

        if (0 < (size)) {
            XString x(bytes, size);
            XOS_LOG_DEBUG("write " << x << "...");
            if (0 < (count = w.Write(bytes, size))) {
                XOS_LOG_DEBUG("...wrote " << x << "");
            }
        }
        return count;
    }
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

        if (sizeof(uint32_t) <= (size))
            size = sizeof(uint32_t);

        if (0 < (size)) {
            size_t i = sizeof(uint32_t)-size;
            if (0 < (count = r.Read(bytes+i, size))) {
                XString x(bytes+i, size);
                XOS_LOG_DEBUG("...read " << x << "");
                for (size_t i = 0; i < size; ++i, value <<= 8)
                    value |= bytes[(sizeof(uint32_t)-1)-i];
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
            XOS_LOG_DEBUG("write " << x << "...");
            if (0 < (count = w.Write(bytes+i, size))) {
                XOS_LOG_DEBUG("...wrote " << x << "");
            }
        }
        return count;
    }
    virtual ssize_t WriteOpaque(io::Writer& w, const uint8_t* bytes, size_t size) {
        ssize_t count = 0;
        if ((bytes) && (size)) {
            XString x(bytes, size);
            XOS_LOG_DEBUG("write " << x << "...");
            if (0 < (count = w.Write(bytes, size))) {
                XOS_LOG_DEBUG("...wrote " << x << "");
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        return count;
    }
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Extend: virtual public Implement, virtual public ExportBase {
public:
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Base: virtual public Implement, virtual public Extend {
public:
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template <typename TWhat, size_t VLengthSize, typename TSize = size_t>
class _EXPORT_CLASS Vector: virtual public Implement, virtual public Extend {
public:
    Vector(const TWhat* values, TSize count) {
        if (0 < (m_length = (sizeof(TWhat)*count)))
            m_contents.Assign(values, count);
    }
    Vector(const TWhat& value, TSize count) {
        if (0 < (m_length = (sizeof(TWhat)*count)))
            m_contents.Set(value, count);
    }
    Vector(): m_length(0) {}
    virtual ~Vector() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Assign(const TWhat* values, TSize count) {
        if (0 < (m_length = (sizeof(TWhat)*count)))
            return m_contents.Assign(values, count);
        return 0;
    }
    virtual size_t Set(const TWhat& value, TSize count) {
        if (0 < (m_length = (sizeof(TWhat)*count)))
            return m_contents.Set(value, count);
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount;
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
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += VLengthSize;
        count += m_contents.Length()*VLengthSize;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TSize m_length;
    Array<TWhat> m_contents;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Uint24: virtual public Implement, virtual public Extend {
public:
    Uint24(uint32_t value = 0): m_value(value) {}
    virtual ~Uint24() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = WriteMsb(writer, m_value, 3);
        return count;
    }
    virtual ssize_t SizeOf() const {
        ssize_t count = 3;
        return count;
    }
    virtual uint32_t SetValue(uint32_t to) {
        m_value = to;
        return m_value;
    }
    virtual uint32_t Value() const {
        return m_value;
    }
protected:
    uint32_t m_value;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_BASE_HPP 
