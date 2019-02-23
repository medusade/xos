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
///   File: MainBase.cpp
///
/// Author: $author$
///   Date: Jul 31, 2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/MainBase.hpp"

namespace xos {

static MainBase* theMain = 0;
int MainBase::TheMain(int argc, char** argv, char** env) {
    int err = 1;
    if ((theMain)) {
        MainBase& main = *theMain;
        err = main(argc, argv, env);
    }
    return err;
}
void MainBase::SetTheMain(MainBase* toTheMain){ theMain = toTheMain; }
MainBase* MainBase::GetTheMain(){ return theMain; }

} // namespace xos
