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
///   Date: 4/11/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_XSLT_LIBXSLT_PROCESSOR_HPP
#define _XOS_INET_HTTP_SERVER_XSLT_LIBXSLT_PROCESSOR_HPP

#include "xos/inet/http/server/xslt/Processor.hpp"
#include "xos/inet/http/Content.hpp"
#include "xos/xml/xslt/libxslt/Processor.hpp"

#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_XML_FILE_EXTENSION "xml"
#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_XSL_FILE_EXTENSION "xsl"
#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_XSLT_FILE_EXTENSION "xslt"

#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_FILE_DIRECTORY_SEPARATOR '/'
#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_FILE_EXTENSION_SEPARATOR '.'

#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_CONTENT_TYPE \
    XOS_HTTP_CONTENT_TYPE_NAME_HTML

#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_PARAM_CONTENT_TYPE_NAMES \
    "content_type", "Content-Type"

#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_PARAM_XML_FILE_NAMES \
    "document_filename", "document_file", \
    "xml_filename", "xml_file"

#define XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_PARAM_XSLT_FILE_NAMES \
    "template_filename", "template_file", \
    "xslt_filename", "xslt_file", \
    "xsl_filename", "xsl_file"

namespace xos {
namespace http {
namespace server {
namespace xslt {
namespace libxslt {

typedef server::xslt::ProcessorImplement ProcessorImplement;
typedef server::xslt::Processor ProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Processor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Processor: virtual public ProcessorImplement, public ProcessorExtend {
public:
    typedef ProcessorImplement Implements;
    typedef ProcessorExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Processor()
    : m_fileDirectorySeparator(XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_FILE_DIRECTORY_SEPARATOR),
      m_fileExtensionSeparator(XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_FILE_EXTENSION_SEPARATOR),
      m_xmlFileExtension(XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_XML_FILE_EXTENSION),
      m_xsltFileExtension(XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_XSLT_FILE_EXTENSION) {
    }
    virtual ~Processor() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        const String& pathTranslated = request.GetContext().GetPathTranslated();
        http::Form& form = request.form();
        http::Form::Fields fields = form.fields();
        http::Form::Field formField;
        String contentType(XOS_HTTP_CONTENT_TYPE_NAME_HTML);
        String pathTranslatedDir;
        String pathTranslatedExtension;
        String xmlFileName;
        String xsltFileName;
        const char* chars;
        ssize_t length;

        XOS_LOG_TRACE("in...");

        if (0 < (GetField(formField, form, ParameterContentTypeNames()))) {
            const String& fieldValue(formField.GetValue());
            XOS_LOG_TRACE("content type = \"" << fieldValue << "\"");
            contentType.Assign(fieldValue);
        }

        response.SetContentType(contentType);

        if ((chars = pathTranslated.Chars()) && (0 < (length = pathTranslated.Length()))) {
            const char* dirChars = Chars::FindReverse(chars, m_fileDirectorySeparator, length);
            const char* extChars = Chars::FindReverse(chars, m_fileExtensionSeparator, length);

            if ((dirChars) && (0 < (length  = (dirChars - chars)))) {
                pathTranslatedDir.Assign(chars, length);
            }

            if ((extChars) && (0 < (length  = (extChars - chars)))) {
                pathTranslatedExtension.Assign(extChars+1);
                xmlFileName.Assign(chars, length);
                xsltFileName.Assign(chars, length);

                if (!(m_xmlFileExtension.Compare(pathTranslatedExtension))) {
                    xmlFileName.Append(extChars);
                    xsltFileName.Append(extChars, 1);
                    xsltFileName.Append(m_xsltFileExtension);
                } else {
                    xsltFileName.Append(extChars);
                    xmlFileName.Append(extChars, 1);
                    xmlFileName.Append(m_xmlFileExtension);
                }
            }
        }

        if (0 < (GetField(formField, form, ParameterXmlFileNames()))) {
            const String& fieldValue(formField.GetValue());
            XOS_LOG_TRACE("xml file = \"" << fieldValue << "\"");
            SetRelativeFileName(xmlFileName, fieldValue, pathTranslatedDir);
        }

        if (0 < (GetField(formField, form, ParameterXsltFileNames()))) {
            const String& fieldValue(formField.GetValue());
            XOS_LOG_TRACE("xslt file = \"" << fieldValue << "\"");
            SetRelativeFileName(xsltFileName, fieldValue, pathTranslatedDir);
        }

        if ((0 < (xmlFileName.Length())) && (0 < (xsltFileName.Length()))) {
            xml::xslt::libxslt::Processor xslt;
            if ((xslt.Init())) {
                http::Message::Writer writer(response.message());
                http::Form::Fields::const_iterator b  = fields.begin();
                http::Form::Fields::const_iterator e  = fields.end();
                for (http::Form::Fields::const_iterator i = b; i != e; ++i) {
                    const http::Form::Field& f = *i;
                    const String& name = f.name();
                    const String& value = f.value();
                    xslt.SetLiteralParameter(name, value);
                }
                xslt.ProcessFiles(writer, writer, xsltFileName, xmlFileName);
                xslt.Finish();
            }
        }
        XOS_LOG_TRACE("...out");
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String& SetRelativeFileName
    (String& fileName, const String& to, const String& relativeTo) {
        const char* chars;
        ssize_t length;
        if ((chars = to.Chars()) && (0 < (length = to.Length()))) {
            const char* dirChars = Chars::Find(chars, m_fileDirectorySeparator, length);
            if ((0 < (relativeTo.Length()) && (dirChars != chars))) {
                fileName.Assign(relativeTo);
                fileName.Append(&m_fileDirectorySeparator,1);
                fileName.Append(to);
            } else
            fileName.Assign(to);
        }
        return fileName;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t GetField
    (http::Form::Field& formField, const http::Form& form, const char** names) {
        const char* chars;
        ssize_t length;
        for (chars = *names; chars; chars = *(++names)) {
            if ((form.GetField(formField, chars))) {
                const String& fieldValue(formField.GetValue());
                if (0 < (length = fieldValue.Length())) {
                    return length;
                }
            }
        }
        return -1;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char** ParameterContentTypeNames() const {
        static const char* names[] = {
            XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_PARAM_CONTENT_TYPE_NAMES
            ,0};
        return names;
    }
    virtual const char** ParameterXmlFileNames() const {
        static const char* names[] = {
            XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_PARAM_XML_FILE_NAMES
            ,0};
        return names;
    }
    virtual const char** ParameterXsltFileNames() const {
        static const char* names[] = {
            XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_PARAM_XSLT_FILE_NAMES
            ,0};
        return names;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char m_fileDirectorySeparator;
    char m_fileExtensionSeparator;
    String m_xmlFileExtension;
    String m_xsltFileExtension;
};

} // namespace libxslt 
} // namespace xslt 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_XSLT_LIBXSLT_PROCESSOR_HPP 
