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
///   File: Writer.hpp
///
/// Author: $author$
///   Date: 4/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_WRITER_HPP
#define _XOS_CRYPTO_WRITER_HPP

#include "xos/os/Main.hpp"

namespace xos {
namespace crypto {

typedef InterfaceBase WriterImplement;
///////////////////////////////////////////////////////////////////////
///  Class: Writer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Writer: virtual public WriterImplement {
public:
    typedef WriterImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const BYTE* bytes, size_t size) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_WRITER_HPP 
