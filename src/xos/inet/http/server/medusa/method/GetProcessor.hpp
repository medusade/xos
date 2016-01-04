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
///   File: GetProcessor.hpp
///
/// Author: $author$
///   Date: 6/8/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_HPP

#include "xos/inet/http/server/medusa/method/Processor.hpp"
#include "xos/inet/http/server/medusa/ServerConfig.hpp"
#include "xos/fs/os/Directory.hpp"
#include "xos/fs/os/Entry.hpp"
#include "xos/io/File.hpp"

#define XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_BEGIN \
    "<html><body><ul>"

#define XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_END \
    "</ul></body></html>"

#define XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_ENTRY_BEGIN \
    "<li><a href=\""

#define XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_ENTRY_MIDDLE \
    "\">"

#define XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_ENTRY_END \
    "</a></li>"

namespace xos {
namespace http {
namespace server {
namespace medusa {
namespace method {

typedef ProcessorImplement GetProcessorImplement;
typedef Processor GetProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GetProcessor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GetProcessor: virtual public GetProcessorImplement, public GetProcessorExtend {
public:
    typedef GetProcessorImplement Implements;
    typedef GetProcessorExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    GetProcessor() {
    }
    virtual ~GetProcessor() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        bool processed = false;
        const String& path = request.GetPathTranslated();
        fs::os::Entry entry;

        XOS_LOG_DEBUG("in...");

        if ((entry.Exists(path))) {
            fs::Entry::Type type = entry.GetType();

            switch (type) {
            case fs::Entry::File:
                XOS_LOG_DEBUG("path \"" << path << "\" is a file");
                processed = ProcessFile(response, request, entry, path);
                break;

            case fs::Entry::Directory:
                XOS_LOG_DEBUG("path \"" << path << "\" is a directory");
                processed = ProcessDirectory(response, request, entry, path);
                break;

            default:
                XOS_LOG_DEBUG("path \"" << path << "\" type = " << type);
            }
        } else {
            XOS_LOG_DEBUG("path \"" << path << "\" not found");
        }
        XOS_LOG_DEBUG("...out");
        return processed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessFile
    (Response& response, const Request& request,
     const fs::os::Entry& entry, const String& path) {
        bool processed = false;
        io::File file;

        XOS_LOG_DEBUG("open file \"" << path << "\"...");
        if ((file.Open(path))) {
            const ServerConfig& config = request.GetServerConfig();
            const String contentType = config.GetContentTypeOf(path);
            const size_t contentLength = entry.GetSize();
            CharWriter& writer = response.GetMessageWriter();
            char byte;
            size_t count;
            ssize_t amount;

            XOS_LOG_DEBUG("...opened file \"" << path << "\"");

            if (0 < (contentType.Length())) {
                XOS_LOG_DEBUG("content type = \"" << contentType << "\"");
                response.SetContentType(contentType);
            }

            if (0 < (contentLength)) {
                XOS_LOG_DEBUG("content length = " << contentLength << "");
                response.SetContentLengthNo(contentLength);

                XOS_LOG_DEBUG("writing content[" << contentLength << "]...");
                for (count = 0; count < contentLength; ++count) {
                    if (0 < (amount = file.Read(&byte, 1))) {
                        if (0 < (amount = writer.Write(&byte, 1))) {
                            continue;
                        } else {
                            XOS_LOG_DEBUG("...failed on write")
                        }
                    } else {
                        XOS_LOG_DEBUG("...failed on read");
                    }
                    break;
                }
                if (count >= contentLength) {
                    XOS_LOG_DEBUG("...wrote content[" << contentLength << "]");
                    processed = true;
                }
            } else {
                processed = true;
                XOS_LOG_DEBUG("writing content...");
                while (0 < (amount = file.Read(&byte, 1))) {
                    if (0 >= (amount = writer.Write(&byte, 1))) {
                        XOS_LOG_DEBUG("...failed on write");
                        processed = false;
                        break;
                    }
                }
                if ((processed)) {
                    XOS_LOG_DEBUG("...wrote content");
                }
            }

            XOS_LOG_DEBUG("close file \"" << path << "\"...");
            if ((file.Close())) {
                XOS_LOG_DEBUG("...closed file \"" << path << "\"");
            } else {
                XOS_LOG_DEBUG("...failed to close file \"" << path << "\"");
            }
        } else {
            XOS_LOG_DEBUG("...failed to open file \"" << path << "\"");
        }
        return processed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessDirectory
    (Response& response, const Request& request,
     const fs::os::Entry& entry, const String& path) {
        bool processed = false;
        fs::os::Directory d;

        XOS_LOG_DEBUG("open directory \"" << path << "\"...");
        if ((d.Open(path))) {
            XOS_LOG_DEBUG("...opened directory \"" << path << "\"");

            if ((ProcessDirectoryBegin(response, request, entry, path))) {
                fs::Entry::Type type;

                for (fs::os::Entry* e = d.GetFirst(); e; e = d.GetNext()) {
                    const fs::os::Entry& dEntry = *e;
                    const fs::Entry::Name& dName = dEntry.GetName();

                    switch (type = dEntry.GetType()) {
                    case fs::Entry::File:
                        XOS_LOG_DEBUG("entry \"" << dName << "\" is a file");
                        ProcessDirectoryEntry(response, request, entry, path, dEntry, dName);
                        break;
                    case fs::Entry::Directory:
                        XOS_LOG_DEBUG("entry \"" << dName << "\" is a directory");
                        ProcessDirectoryEntry(response, request, entry, path, dEntry, dName);
                        break;
                    default:
                        XOS_LOG_DEBUG("path \"" << dName << "\" type = " << type);
                    }
                }
                if ((ProcessDirectoryEnd(response, request, entry, path))) {
                    processed = true;
                }
            }
            XOS_LOG_DEBUG("close directory \"" << path << "\"...");
            if ((d.Close())) {
                XOS_LOG_DEBUG("...closed directory \"" << path << "\"");
            } else {
                XOS_LOG_DEBUG("...failed to close directory \"" << path << "\"");
            }
        } else {
            XOS_LOG_ERROR("...failed to open directory \"" << path << "\"");
        }
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessDirectoryBegin
    (Response& response, const Request& request,
     const fs::os::Entry& entry, const String& path) {
        CharWriter& writer = response.GetMessageWriter();
        const char* chars = XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_BEGIN;
        bool processed = true;
        ssize_t amount;
        response.SetContentType(XOS_HTTP_CONTENT_TYPE_NAME_HTML);
        if (0 > (amount = writer.Write(chars))) {
            XOS_LOG_ERROR("failed to write \"" << chars << "\"");
            processed = false;
        }
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessDirectoryEnd
    (Response& response, const Request& request,
     const fs::os::Entry& entry, const String& path) {
        CharWriter& writer = response.GetMessageWriter();
        const char* chars = XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_END;
        bool processed = true;
        ssize_t amount;
        if (0 > (amount = writer.Write(chars))) {
            XOS_LOG_ERROR("failed to write \"" << chars << "\"");
            processed = false;
        }
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessDirectoryEntry
    (Response& response, const Request& request,
     const fs::os::Entry& entry, const String& path,
     const fs::os::Entry& dEntry, const fs::Entry::Name& dName) {
        CharWriter& writer = response.GetMessageWriter();
        const char* bChars = XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_ENTRY_BEGIN;
        const char* mChars = XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_ENTRY_MIDDLE;
        const char* eChars = XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_DIRECTORY_ENTRY_END;
        bool processed = true;
        const char* chars;
        ssize_t amount;
        if (0 > (amount = writer.Write(chars = bChars))) {
            XOS_LOG_ERROR("failed to write \"" << chars << "\"");
            processed = false;
        } else {
            String location(request.GetPath());
            size_t length;
            if ((chars = location.HasChars(length))) {
                if ((chars[length-1] != '/')) {
                    location.Append("/");
                }
            }
            location.Append(dName);
            if (0 > (amount = writer.Write(chars = location.Chars()))) {
                XOS_LOG_ERROR("failed to write \"" << chars << "\"");
                processed = false;
            } else {
                if (0 > (amount = writer.Write(chars = mChars))) {
                    XOS_LOG_ERROR("failed to write \"" << chars << "\"");
                    processed = false;
                } else {
                    if (0 > (amount = writer.Write(chars = dName.Chars()))) {
                        XOS_LOG_ERROR("failed to write \"" << chars << "\"");
                        processed = false;
                    } else {
                        if ((fs::Entry::Directory == (dEntry.GetType()))) {
                            if (0 > (amount = writer.Write(chars = "/"))) {
                                XOS_LOG_ERROR("failed to write \"" << chars << "\"");
                                processed = false;
                            }
                        }
                        if ((processed)) {
                            if (0 > (amount = writer.Write(chars = eChars))) {
                                XOS_LOG_ERROR("failed to write \"" << chars << "\"");
                                processed = false;
                            } else {
                            }
                        }
                    }
                }
            }
        }
        return processed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static Processor& GetTheInstance();
};

} // namespace method 
} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_METHOD_GETPROCESSOR_HPP 
