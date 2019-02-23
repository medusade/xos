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
///   Date: 4/9/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_XML_XSLT_LIBXSLT_CGI_MAIN_HPP
#define _XOS_XML_XSLT_LIBXSLT_CGI_MAIN_HPP

#include "xos/inet/http/cgi/Main.hpp"
#include "xos/xml/xslt/libxslt/Processor.hpp"

#define XOS_XML_XSLT_LIBXSLT_CGI_XML_FILE_EXTENSION "xml"
#define XOS_XML_XSLT_LIBXSLT_CGI_XSLT_FILE_EXTENSION "xslt"

#define XOS_XML_XSLT_LIBXSLT_CGI_FILE_DIRECTORY_SEPARATOR '/'
#define XOS_XML_XSLT_LIBXSLT_CGI_FILE_EXTENSION_SEPARATOR '.'

#define XOS_XML_XSLT_LIBXSLT_CGI_CONTENT_TYPE \
    XOS_HTTP_CONTENT_TYPE_NAME_HTML

#define XOS_XML_XSLT_LIBXSLT_CGI_PARAM_CONTENT_TYPE_NAMES \
    "content_type", "Content-Type"

#define XOS_XML_XSLT_LIBXSLT_CGI_PARAM_XML_FILE_NAMES \
    "document_filename", "document_file", \
    "xml_filename", "xml_file"

#define XOS_XML_XSLT_LIBXSLT_CGI_PARAM_XSLT_FILE_NAMES \
    "template_filename", "template_file", \
    "xslt_filename", "xslt_file", \
    "xsl_filename", "xsl_file"

namespace xos {
namespace xml {
namespace xslt {
namespace libxslt {
namespace cgi {

typedef http::cgi::MainImplement MainImplement;
typedef http::cgi::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef http::cgi::Environment Environment;

    typedef http::FormReader::Observer FormReaderObserverExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: FormReaderObserver
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS FormReaderObserver: public FormReaderObserverExtend {
    public:
        typedef FormReaderObserverExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        FormReaderObserver(Main& main): m_main(main) {
        }
        virtual ~FormReaderObserver() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual void OnRead(const String& name,const String& value) {
            m_main.SetParameterFromForm(name, value);
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Main& m_main;
    };

    typedef CharWriter::Implements WriterImplement;
    typedef CharWriter WriterExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Writer
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Writer: virtual public WriterImplement, public WriterExtend {
    public:
        typedef WriterImplement Implements;
        typedef WriterExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Writer(Main& main): m_main(main) {
        }
        virtual ~Writer() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t WriteFormatted(const What* format, ...) {
            ssize_t count = 0;
            va_list va;
            va_start(va, format);
            count = WriteFormattedV(format, va);
            va_end(va);
            return count;
        }
        virtual ssize_t WriteFormattedV(const What* format, va_list va) {
            ssize_t count = m_main.OutContentFormattedV(format, va);
            return count;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t Write(const What* what, ssize_t length=-1) {
            ssize_t count = m_main.OutContent(what, length);
            return count;
        }
        virtual ssize_t Flush() {
            ssize_t count = m_main.OutContentFlush();
            return count;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Main& m_main;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_fileDirectorySeparator(XOS_XML_XSLT_LIBXSLT_CGI_FILE_DIRECTORY_SEPARATOR),
      m_fileExtensionSeparator(XOS_XML_XSLT_LIBXSLT_CGI_FILE_EXTENSION_SEPARATOR),
      m_xmlFileExtension(XOS_XML_XSLT_LIBXSLT_CGI_XML_FILE_EXTENSION),
      m_xsltFileExtension(XOS_XML_XSLT_LIBXSLT_CGI_XSLT_FILE_EXTENSION) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        int err = 0;

        SetContentType(XOS_XML_XSLT_LIBXSLT_CGI_CONTENT_TYPE);

        if ((m_xslt.Init())) {
            GetPathTranslated(m_env);
            GetQueryFormData(m_env);
            GetMethodFormData(m_env);

            if ((m_xsltFileName.Length()) && m_xmlFileName.Length()) {
                Writer errWriter(*this);
                Writer outWriter(*this);
                m_xslt.ProcessFiles(errWriter, outWriter, m_xsltFileName, m_xmlFileName);
            }
            m_xslt.Finish();
        }
        OutContentFlush();
        return err;
    }
    virtual bool GetPathTranslated(const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::PATH_TRANSLATED];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const char* dirChars = Chars::FindReverse(chars, m_fileDirectorySeparator, length);
            const char* extChars = Chars::FindReverse(chars, m_fileExtensionSeparator, length);

            if ((dirChars) && (0 < (length  = (dirChars - chars)))) {
                m_pathTranslatedDir.Assign(chars, length);
            }

            if ((extChars) && (0 < (length  = (extChars - chars)))) {
                m_pathTranslatedBase.Assign(chars, length);
                m_pathTranslatedExtension.Assign(extChars+1);
                m_xmlFileName.Assign(chars, length);
                m_xsltFileName.Assign(chars, length);

                if (!(m_xmlFileExtension.Compare(m_pathTranslatedExtension))) {
                    m_xmlFileName.Append(extChars);
                    m_xsltFileName.Append(extChars, 1);
                    m_xsltFileName.Append(m_xsltFileExtension);
                } else {
                    m_xsltFileName.Append(extChars);
                    m_xmlFileName.Append(extChars, 1);
                    m_xmlFileName.Append(m_xmlFileExtension);
                }
            }
        }
        return false;
    }
    virtual bool GetUrlEncodedFormData(http::UrlEncodedReader& reader) {
        FormReaderObserver observer(*this);
        http::UrlEncodedFormReader form(reader, observer);
        return true;
    }
    virtual bool SetParameterFromForm(const String& name,const String& value) {
        m_xslt.SetLiteralParameter(name, value);
        const char* chars;
        ssize_t length;
        if ((MatchParameterName(name, ParameterContentTypeNames()))) {
            if (0 < (value.Length())) {
                SetContentType(value);
            }
        } else {
            if ((MatchParameterName(name, ParameterXmlFileNames()))) {
                if ((chars = value.Chars()) && (0 < (length = value.Length()))) {
                    const char* dirChars = Chars::Find(chars, m_fileDirectorySeparator, length);
                    if ((0 < (m_pathTranslatedDir.Length()) && (dirChars != chars))) {
                        String fileName(m_pathTranslatedDir);
                        fileName.Append(&m_fileDirectorySeparator,1);
                        fileName.Append(value);
                        SetXmlFileName(fileName);
                    } else
                    SetXmlFileName(value);
                }
            } else {
                if ((MatchParameterName(name, ParameterXsltFileNames()))) {
                    if ((chars = value.Chars()) && (0 < (length = value.Length()))) {
                        const char* dirChars = Chars::Find(chars, m_fileDirectorySeparator, length);
                        if ((0 < (m_pathTranslatedDir.Length()) && (dirChars != chars))) {
                            String fileName(m_pathTranslatedDir);
                            fileName.Append(&m_fileDirectorySeparator,1);
                            fileName.Append(value);
                            SetXsltFileName(fileName);
                        } else
                        SetXsltFileName(value);
                    }
                } else {
                }
            }
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* SetXmlFileName(const String& to) {
        return SetXmlFileName(to.Chars());
    }
    virtual const char* SetXmlFileName(const char* to) {
        if ((to)) {
            if ((to[0])) {
                m_xmlFileName.Assign(to);
                return m_xmlFileName.Chars();
            }
        }
        return 0;
    }
    virtual const char* GetXmlFileName() const {
        return m_xmlFileName.Chars();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* SetXsltFileName(const String& to) {
        return SetXsltFileName(to.Chars());
    }
    virtual const char* SetXsltFileName(const char* to) {
        if ((to)) {
            if ((to[0])) {
                m_xsltFileName.Assign(to);
                return m_xsltFileName.Chars();
            }
        }
        return 0;
    }
    virtual const char* GetXsltFileName() const {
        return m_xsltFileName.Chars();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool MatchParameterName(const String& name, const char** names) const {
        if ((names)) {
            for (const char* to = *names; to; to = *(++names)) {
                XOS_LOG_TRACE("matching \"" << name << "\" to \"" << to << "\"");
                if (!(name.Compare(to)))
                    return true;
            }
        }
        return false;
    }
    virtual const char** ParameterContentTypeNames() const {
        static const char* names[] = {
            XOS_XML_XSLT_LIBXSLT_CGI_PARAM_CONTENT_TYPE_NAMES
            ,0};
        return names;
    }
    virtual const char** ParameterXmlFileNames() const {
        static const char* names[] = {
            XOS_XML_XSLT_LIBXSLT_CGI_PARAM_XML_FILE_NAMES
            ,0};
        return names;
    }
    virtual const char** ParameterXsltFileNames() const {
        static const char* names[] = {
            XOS_XML_XSLT_LIBXSLT_CGI_PARAM_XSLT_FILE_NAMES
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
    String m_pathTranslatedDir;
    String m_pathTranslatedBase;
    String m_pathTranslatedExtension;
    String m_xmlFileName;
    String m_xsltFileName;
    libxslt::Processor m_xslt;
};

} // namespace cgi 
} // namespace libxslt 
} // namespace xslt 
} // namespace xml 
} // namespace xos 

#endif // _XOS_XML_XSLT_LIBXSLT_CGI_MAIN_HPP 
