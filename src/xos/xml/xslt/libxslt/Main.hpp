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
///   Date: 4/7/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_XML_XSLT_LIBXSLT_MAIN_HPP
#define _XOS_XML_XSLT_LIBXSLT_MAIN_HPP

#include "xos/xml/xslt/libxslt/Processor.hpp"
#include "xos/os/Main.hpp"
#include "xos/os/FILEWriter.hpp"
#include "xos/base/StringWriter.hpp"

namespace xos {
namespace xml {
namespace xslt {
namespace libxslt {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;
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
    virtual int Run(int argc, char **argv, char **env) {
        String strErr, strOut;
        StringWriter strErrWriter(strErr), strOutWriter(strOut);
        CharFILEWriter stdErrWriter(StdErr()), stdOutWriter(StdOut());
        CharWriter &errWriter = stdErrWriter, &outWriter = stdOutWriter;
        Processor xslt;
        const char* chars;
        size_t length;

        if (optind < (argc - 1)) {
            String xsltFileName(argv[optind]), xmlFileName(argv[optind+1]);
            if ((xslt.Init())) {
                if ((xslt.ProcessFiles(errWriter, outWriter, xsltFileName, xmlFileName))) {
                    if ((chars = strOut.HasChars(length))) {
                        Out(chars, length);
                    }
                } else {
                    if ((chars = strErr.HasChars(length))) {
                        Err(chars, length);
                    }
                }
                xslt.Finish();
            }
        } else {
            Usage(argc, argv, env);
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace libxslt 
} // namespace xslt 
} // namespace xml 
} // namespace xos 

#endif // _XOS_XML_XSLT_LIBXSLT_MAIN_HPP 
