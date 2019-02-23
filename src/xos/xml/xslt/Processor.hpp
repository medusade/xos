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
///   File: Processor.hpp
///
/// Author: $author$
///   Date: 4/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_XML_XSLT_PROCESSOR_HPP
#define _XOS_XML_XSLT_PROCESSOR_HPP

#include "xos/base/Writer.hpp"
#include "xos/base/Reader.hpp"
#include "xos/base/String.hpp"

namespace xos {
namespace xml {
namespace xslt {

typedef InterfaceBase ProcessorImplement;
typedef ExportBase ProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Processor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Processor: virtual public ProcessorImplement, public ProcessorExtend {
public:
    typedef ProcessorImplement Implements;
    typedef ProcessorExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Processor() {
    }
    virtual ~Processor() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        bool success = true;
        return success;
    }
    virtual bool Finish()  {
        bool success = true;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetLiteralParameter(const String& name, const String& value) {
        bool success = false;
        return success;
    }
    virtual bool SetParameter(const String& name, const String& expression) {
        bool success = false;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessXsltFile
    (CharWriter& err, CharWriter& out, const String& xsltFileName,
     CharReader& xml, const String& xmlFileNameOrUri) {
        bool success = false;
        return success;
    }
    virtual bool ProcessXmlFile
    (CharWriter& err, CharWriter& out, CharReader& xslt,
     const String& xsltFileNameOrUri, const String& xmlFileName) {
        bool success = false;
        return success;
    }
    virtual bool ProcessFiles
    (CharWriter& err, CharWriter& out,
     const String& xsltFileName, const String& xmlFileName) {
        bool success = false;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process
    (CharWriter& err, CharWriter& out, const String& xsltFileNameOrUri,
     CharReader& xml, const String& xmlFileNameOrUri) {
        bool success = false;
        return success;
    }
    virtual bool Process
    (CharWriter& err, CharWriter& out, CharReader& xslt,
     const String& xsltFileNameOrUri, const String& xmlFileNameOrUri) {
        bool success = false;
        return success;
    }
    virtual bool Process
    (CharWriter& err, CharWriter& out,
     const String& xsltFileNameOrUri, const String& xmlFileNameOrUri) {
        bool success = false;
        return success;
    }
    virtual bool Process
    (CharWriter& err, CharWriter& out,
     CharReader& xslt, const String& xsltFileNameOrUri,
     CharReader& xml, const String& xmlFileNameOrUri) {
        bool success = false;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace xslt 
} // namespace xml 
} // namespace xos 

#endif // _XOS_XML_XSLT_PROCESSOR_HPP 
