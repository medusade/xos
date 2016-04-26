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
///   File: Connection.hpp
///
/// Author: $author$
///   Date: 4/26/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_CONNECTION_HPP
#define _XOS_INET_TLS_CONNECTION_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

typedef io::Stream ConnectionImplements;
typedef Extend ConnectionExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Connection
: virtual public ConnectionImplements, public ConnectionExtends {
public:
    typedef ConnectionImplements Implements;
    typedef ConnectionExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Connection(io::Reader& reader, io::Writer& writer)
    : m_reader(reader), m_writer(writer) {
    }
    Connection(const Connection& copy)
    : m_reader(copy.m_reader), m_writer(copy.m_writer) {
    }
    virtual ~Connection() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    io::Reader& m_reader;
    io::Writer& m_writer;
};

} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_CONNECTION_HPP 
