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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 4/20/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_HELLO_MAIN_HPP
#define _XOS_IO_HELLO_MAIN_HPP

#include "xos/io/file/Stream.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Main.hpp"

namespace xos {
namespace io {
namespace hello {

typedef MainImplement MainImplement;
typedef Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement,public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        ssize_t n;
        char m[10];
        AttachedT<FILE*, int, 0, file::Stream> i(StdIn());
        AttachedT<FILE*, int, 0, file::Stream> o(StdOut());
        o.Write("Hello \n");
        n = i.ReadFormatted("%s", m);
        XOS_LOG_TRACE("read n = " << n);
        if (0 < (n)) {
            o.WriteFormatted("%s\n", m);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace hello 
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_HELLO_MAIN_HPP 
