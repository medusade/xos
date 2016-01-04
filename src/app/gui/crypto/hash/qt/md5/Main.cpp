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
///   File: Main.cpp
///
/// Author: $author$
///   Date: 1/27/2014
///////////////////////////////////////////////////////////////////////
#include "xos/crypto/hash/Md5.hpp"
#include "app/gui/crypto/hash/qt/Main.cpp"

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace qt {

///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
xos::crypto::hash::Interface& Main::GetHash() const {
    static xos::crypto::hash::Md5 the_hash;
    return the_hash;
}
const char* Main::GetHashName() const {
    return "MD5";
}

} // namespace qt
} // namespace hash 
} // namespace crypto 
} // namespace gui 
} // namespace xos 
