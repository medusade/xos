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
///   Date: 4/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_XML_XSLT_LIBXSLT_PROCESSOR_HPP
#define _XOS_XML_XSLT_LIBXSLT_PROCESSOR_HPP

#include "xos/xml/xslt/Processor.hpp"
#include "xos/base/Array.hpp"
#include "xos/os/Logger.hpp"

#include <libxslt/xslt.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libxslt/extensions.h>
#include <libxslt/security.h>
#include <libexslt/exslt.h>

#define DEFAULT_XSLT_PARSE_OPTIONS_XML_PARSE_NOERROR XML_PARSE_NOERROR
#define DEFAULT_XSLT_PARSE_OPTIONS_XML_PARSE_NOWARNING XML_PARSE_NOWARNING

namespace xos {
namespace xml {
namespace xslt {
namespace libxslt {

typedef xslt::ProcessorImplement ProcessorImplement;
typedef xslt::Processor ProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Processor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Processor: virtual public ProcessorImplement, public ProcessorExtend {
public:
    typedef ProcessorImplement Implements;
    typedef ProcessorExtend Extends;

    typedef InterfaceBase ParamsImplement;
    typedef ExportBase ParamsExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Params
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Params: virtual public ParamsImplement, public ParamsExtend {
    public:
        typedef ParamsImplement Implements;
        typedef ParamsExtend Extends;
        typedef Array<const char*> CharsArray;
        typedef Array<String*> StringsArray;
        enum Error {
            ErrorNone = 0,
            ErrorAddFailed,
            ErrorAddDuplicate
        };
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Params()
        : m_apos("'"),
          m_nullChars(0),
          m_nullParam(0) {
        }
        virtual ~Params() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Error Add(const String& name, const String& expression) {
            String *paramName, *paramExpression;
            const char *paramNameChars, *paramExpressionChars;
            Error error;
            if (!(error = AddName(name))) {
                if ((paramName = new String(name))) {
                    if ((paramNameChars = paramName->HasChars())) {
                        if ((paramExpression = new String(expression))) {
                            if ((paramExpressionChars = paramExpression->HasChars())) {
                                m_paramsChars.Append(&paramNameChars, 1);
                                m_paramsChars.Append(&paramExpressionChars, 1);
                                m_params.Append(&paramName, 1);
                                m_params.Append(&paramExpression, 1);
                                return ErrorNone;
                            }
                            delete paramExpression;
                        }
                    }
                    delete paramName;
                }
            }
            return error;
        }
        virtual Error AddLiteral(const String& name, const String& value) {
            String literalExpression(m_apos);
            literalExpression.Append(value);
            literalExpression.Append(m_apos);
            return Add(name, literalExpression);
        }
        virtual bool AddEnd() {
            const char** paramsChars;
            const char* paramChars;
            String** params;
            String* param;
            ssize_t length;

            if ((paramsChars = m_paramsChars.Elements())
                 && (0 <= (length = m_paramsChars.Length()))) {
                if (1 > length)
                    m_paramsChars.Append(&m_nullChars, 1);
                else {
                    if ((paramChars = paramsChars[length-1]))
                        m_paramsChars.Append(&m_nullChars, 1);
                }
                if ((params = m_params.Elements())
                    && (0 < (length = m_params.Length()))) {
                    if ((param = params[length-1])) {
                        m_params.Append(&m_nullParam, 1);
                        return true;
                    }
                }
            }
            return false;
        }
        virtual void Clear() {
            String** params;
            String* param;
            ssize_t length;

            m_paramsChars.Clear();

            if ((params = m_params.Elements()) && (length = m_params.Length())) {
                for (ssize_t i = 0; i < length; i++) {
                    if ((param = params[i])) {
                        delete param;
                        params[i] = 0;
                    }
                }
            }
            m_params.Clear();

            if ((params = m_paramNames.Elements()) && (length = m_paramNames.Length())) {
                for (ssize_t i = 0; i < length; i++) {
                    if ((param = params[i])) {
                        delete param;
                        params[i] = 0;
                    }
                }
            }
            m_paramNames.Clear();
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Error AddName(const String& name) {
            String** params;
            String* param;
            ssize_t length;
            int unequal;
            if ((params = m_paramNames.Elements()) && (length = m_paramNames.Length())) {
                for (ssize_t i = 0; i < length; i++) {
                    if ((param = params[i])) {
                        if (!(unequal = param->Compare(name))) {
                            return ErrorAddDuplicate;
                        }
                    }
                }
            }
            if ((param = new String(name))) {
                m_paramNames.Append(&param, 1);
                return ErrorNone;
            }
            return ErrorAddFailed;
        }
        virtual const char** Chars() const {
            return m_paramsChars.Elements();
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        const char* const m_apos;
        const char* const m_nullChars;
        String* const m_nullParam;
        CharsArray m_paramsChars;
        StringsArray m_params;
        StringsArray m_paramNames;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Processor()
    : m_secPrefs(0),
      m_entLoader(0),
      m_xsltParseOptions(XSLT_PARSE_OPTIONS | DEFAULT_XSLT_PARSE_OPTIONS_XML_PARSE_NOERROR | DEFAULT_XSLT_PARSE_OPTIONS_XML_PARSE_NOWARNING),
      m_xmlParseOptions(XML_PARSE_NOENT | XML_PARSE_NOCDATA | XML_PARSE_NOWARNING),
      m_ignoreDuplicateParameterErrors(true) {
    }
    virtual ~Processor() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        bool success = false;
        int err;
        if (!(err = xmlInitMemory())) {
            if ((m_secPrefs = xsltNewSecurityPrefs())) {

                xsltSetDefaultSecurityPrefs(m_secPrefs);

                if ((m_entLoader = xmlGetExternalEntityLoader())) {
                    exsltRegisterAll();
                    return true;

                    xmlSetExternalEntityLoader(m_entLoader);
                    m_entLoader = 0;
                }
                else
                XOS_LOG_ERROR("failed on xmlGetExternalEntityLoader()");

                xsltFreeSecurityPrefs(m_secPrefs);
                m_secPrefs = 0;
            }
            else
            XOS_LOG_ERROR("failed on xsltNewSecurityPrefs()");

            xmlCleanupMemory();
        }
        else
        XOS_LOG_ERROR("failed on xmlInitMemory()");
        return success;
    }
    virtual bool Finish()  {
        bool success = true;
        xmlSetExternalEntityLoader(m_entLoader);
        m_entLoader = 0;
        xsltFreeSecurityPrefs(m_secPrefs);
        m_secPrefs = 0;
        xsltCleanupGlobals();
        xmlCleanupParser();
        xmlCleanupMemory();
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetLiteralParameter(const String& name, const String& value) {
        bool success = false;
        Params::Error error;
        if (!(error = m_xsltParams.AddLiteral(name, value))) {
            success = true;
        } else {
            if (Params::ErrorAddDuplicate == error) {
                XOS_LOG_WARN("duplicate literal parameter \"" << name << "\" = \"" << value << "\"");
                success = m_ignoreDuplicateParameterErrors;
            } else {
                XOS_LOG_ERROR("failed to add literal parameter \"" << name << "\" = \"" << value << "\"");
            }
        }
        return success;
    }
    virtual bool SetParameter(const String& name, const String& expression) {
        bool success = false;
        Params::Error error;
        if (!(error = m_xsltParams.Add(name, expression))) {
            success = true;
        } else {
            if (Params::ErrorAddDuplicate == error) {
                XOS_LOG_ERROR("duplicate parameter \"" << name << "\" = \"" << expression << "\"");
                success = m_ignoreDuplicateParameterErrors;
            } else {
                XOS_LOG_ERROR("failed to add parameter \"" << name << "\" = \"" << expression << "\"");
            }
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessFiles
    (CharWriter& err, CharWriter& out,
     const String& xsltFileName, const String& xmlFileName) {
        bool success = false;
        static const char* nullParams = 0;
        const char** xsltParams = &nullParams;
        const char* xsltFileNameChars;
        const char* xmlFileNameChars;
        xmlDocPtr xsltDoc;
        xmlDocPtr xmlDoc;
        xmlDocPtr resDoc;
        xmlOutputBufferPtr resOutput;
        xmlCharEncodingHandlerPtr resEncoder;
        xsltStylesheetPtr xsltStyle;
        xsltTransformContextPtr xsltCtxt;
        xmlParserCtxtPtr xmlCtxt;
        xmlGenericErrorFunc xsltErrorFunc;
        xmlGenericErrorFunc xmlErrorFunc;

        xsltErrorFunc = XsltGenericError;
        xmlErrorFunc = XmlGenericError;
        xmlSetGenericErrorFunc(&err, xmlErrorFunc);
        xsltSetGenericErrorFunc(&err, xsltErrorFunc);

        XOS_LOG_TRACE("xslt = \"" << xsltFileName << "\" xml = \"" << xmlFileName << "\"");

        if ((xsltFileNameChars = xsltFileName.HasChars())
            && (xmlFileNameChars = xmlFileName.HasChars())) {

            XOS_LOG_TRACE("xmlNewParserCtxt()...");

            if ((xmlCtxt = xmlNewParserCtxt())) {
                xmlInitParserCtxt(xmlCtxt);

                XOS_LOG_TRACE("xmlReadFile(xsltFileName = \"" << xsltFileName << "\")...");

                if ((xsltDoc = xmlReadFile
                    (xsltFileNameChars, 0, m_xsltParseOptions))) {
                //if ((xsltDoc = xmlCtxtReadFile
                //    (xmlCtxt, xsltFileNameChars, 0, m_xsltParseOptions))) {

                    XOS_LOG_TRACE("xmlReadFile(xmlFileName = \"" << xmlFileName << "\")...");

                    if ((xmlDoc = xmlReadFile
                        (xmlFileNameChars, 0, m_xmlParseOptions))) {
                    //if ((xmlDoc = xmlCtxtReadFile
                    //    (xmlCtxt, xmlFileNameChars, 0, m_xmlParseOptions))) {

                        XOS_LOG_TRACE("xsltParseStylesheetDoc(xsltDoc = \"" << xsltFileName << "\")...");

                        if ((xsltStyle = xsltParseStylesheetDoc(xsltDoc))) {

                            XOS_LOG_TRACE("xsltNewTransformContext(xsltStyle = \"" << xsltFileName << "\", xmlDoc = \"" << xmlFileName << "\")...");

                            if ((xsltCtxt = xsltNewTransformContext(xsltStyle, xmlDoc))) {

                                XOS_LOG_TRACE("xsltSetCtxtParseOptions()...");

                                if (0 <= (xsltSetCtxtParseOptions(xsltCtxt, m_xsltParseOptions))) {

                                    m_xsltParams.AddEnd();
                                    if (!(xsltParams = m_xsltParams.Chars()))
                                        xsltParams = &nullParams;

                                    XOS_LOG_TRACE("xsltApplyStylesheetUser(xsltStyle = \"" << xsltFileName << "\", xmlDoc = \"" << xmlFileName << "\",...)...");

                                    if ((resDoc = xsltApplyStylesheetUser
                                        (xsltStyle, xmlDoc, xsltParams, 0, 0, xsltCtxt))) {

                                        XOS_LOG_TRACE("xmlOutputBufferCreateIO()...");

                                        resEncoder = 0;
                                        if ((resOutput = xmlOutputBufferCreateIO
                                            (CharWriterIoWrite, CharWriterIoClose, &out, resEncoder))) {

                                            XOS_LOG_TRACE("xsltSaveResultTo()...");

                                            if (0 <= (xsltSaveResultTo(resOutput, resDoc, xsltStyle))) {
                                                success = true;
                                            } else {
                                                XOS_LOG_ERROR("failed on xsltSaveResultTo()");
                                            }
                                            xmlOutputBufferClose(resOutput);
                                        } else {
                                            XOS_LOG_ERROR("failed on xmlOutputBufferCreateIO()");
                                        }
                                        xmlFreeDoc(resDoc);
                                    } else {
                                        XOS_LOG_ERROR("failed on xsltApplyStylesheetUser()");
                                    }
                                } else {
                                    XOS_LOG_ERROR("failed on xsltSetCtxtParseOptions()");
                                }
                                xsltFreeTransformContext(xsltCtxt);
                            } else {
                                XOS_LOG_ERROR("failed on xsltNewTransformContext()");
                            }
                            xsltFreeStylesheet(xsltStyle);
                            xsltDoc = 0;
                        } else {
                            XOS_LOG_ERROR("failed on xsltParseStylesheetDoc()");
                        }
                        xmlFreeDoc(xmlDoc);
                    } else {
                        XOS_LOG_ERROR("failed on xmlReadFile(xmlFileName = \"" << xmlFileName << "\")");
                    }
                    if ((xsltDoc))
                        xmlFreeDoc(xsltDoc);
                } else {
                    XOS_LOG_ERROR("failed on xmlReadFile(xsltFileName = \"" << xsltFileName << "\")...)");
                }
                xmlFreeParserCtxt(xmlCtxt);
            }
        }
        xsltSetGenericErrorFunc(0,0);
        xmlSetGenericErrorFunc(0,0);
        return success;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void XsltGenericError(void* context, const char* message, ...) {
        CharWriter* errors = 0;
        va_list va;
        va_start(va, message);
        if ((errors = (CharWriter*)(context)))
            errors->WriteFormattedV(message, va);
        va_end(va);
    }
    static void XmlGenericError(void* context, const char* message, ...) {
        CharWriter* errors = 0;
        va_list va;
        va_start(va, message);
        if ((errors = (CharWriter*)(context)))
        if (!(DEFAULT_XSLT_PARSE_OPTIONS_XML_PARSE_NOERROR))
            errors->WriteFormattedV(message, va);
        va_end(va);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static int CharReaderIoRead(void* context, char* buffer, int len) {
        int count = -1;
        CharReader* reader;
        if ((buffer) && (0 <= len))
        if ((reader = (CharReader*)(context)))
        if ((len))
            count = (int)(reader->Read(buffer, len));
        else count = 0;
        return count;
    }
    static int CharReaderIoClose(void* context) {
        int err = 0;
        CharReader* reader;
        if ((reader = (CharReader*)(context)))
            reader->Fill();
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static int CharWriterIoWrite(void* context, const char* buffer, int len) {
        int count = -1;
        CharWriter* writer;
        if ((buffer) && (0 <= len))
        if ((writer = (CharWriter*)(context)))
        if ((count = len))
            len = (int)(writer->Write(buffer, len));
        return count;
    }
    static int CharWriterIoClose(void* context) {
        int err = 0;
        CharWriter* writer;
        if ((writer = (CharWriter*)(context)))
            writer->Flush();
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    xsltSecurityPrefsPtr m_secPrefs;
    xmlExternalEntityLoader m_entLoader;
    int m_xsltParseOptions;
    int m_xmlParseOptions;
    bool m_ignoreDuplicateParameterErrors;
    Params m_xsltParams;
};

} // namespace libxslt 
} // namespace xslt 
} // namespace xml 
} // namespace xos 

#endif // _XOS_XML_XSLT_LIBXSLT_PROCESSOR_HPP 
