///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Process.cpp
///
/// Author: $author$
///   Date: 10/6/2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/os/Process.hpp"

namespace xos {

Process* Process::New(const char* path, char** argv, char** env, bool isDetached) {
    Process* p = new os::Process(path, argv, env, isDetached);
    return p;
}
Process* Process::New(const char* path, char** argv, bool isDetached) {
    Process* p = new os::Process(path, argv, isDetached);
    return p;
}
void Process::Delete(Process* p) {
    delete p;
}

} // namespace xos 

namespace xos {
namespace os {

} // namespace os 
} // namespace xos 
