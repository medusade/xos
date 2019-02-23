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
///   File: iSha512.mm
///
/// Author: $author$
///   Date: 2/7/2014
///////////////////////////////////////////////////////////////////////
#include "MainWindow.hh"
#include "xos/crypto/hash/Sha512.hpp"

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace cocoa {

///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
xos::crypto::hash::Interface& MainWindow::GetTheHash() {
    static xos::crypto::hash::Sha512 the_hash;
    return the_hash;
}
const char* MainWindow::GetTheHashName() {
    return "Sha512";
}

} // namespace cocoa
} // namespace hash
} // namespace crypto
} // namespace gui
} // namespace xos
