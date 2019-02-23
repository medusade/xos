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
///   File: Main.cpp
///
/// Author: $author$
///   Date: 7/29/2013
///////////////////////////////////////////////////////////////////////
#include "app/gui/qt/crypto/hash/Main.hpp"
#include "xos/crypto/hash/mxde/Sha1.hpp"
#include "app/gui/qt/crypto/hash/Main.cpp"

namespace xos {
namespace app {
namespace gui {
namespace qt {
namespace crypto {
namespace hash {

///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
static xos::crypto::hash::mxde::Sha1 g_hash;
xos::crypto::hash::Interface& Main::GetHash() const {
    return g_hash;
}
const char* Main::GetHashName() const {
    return "SHA1";
}

} // namespace hash 
} // namespace crypto 
} // namespace qt 
} // namespace gui 
} // namespace app 
} // namespace xos 
