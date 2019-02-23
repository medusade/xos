########################################################################
# Copyright (c) 1988-2014 $organization$
#
# This software is provided by the author and contributors ``as is'' 
# and any express or implied warranties, including, but not limited to, 
# the implied warranties of merchantability and fitness for a particular 
# purpose are disclaimed. In no event shall the author or contributors 
# be liable for any direct, indirect, incidental, special, exemplary, 
# or consequential damages (including, but not limited to, procurement 
# of substitute goods or services; loss of use, data, or profits; or 
# business interruption) however caused and on any theory of liability, 
# whether in contract, strict liability, or tort (including negligence 
# or otherwise) arising in any way out of the use of this software, 
# even if advised of the possibility of such damage.
#
#   File: mgXosServletd.pro
#
# Author: $author$
#   Date: 2/24/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../lib/libXosCore.pri)
include(../../../../QtCreator/lib/libXosMongoose.pri)
include(../../lib/libXosMongoose.pri)

TARGET = mgXosServletd

INCLUDEPATH += \
$${libXosMongoose_INCLUDEPATH} \
$${libXosCore_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \
$${libXosMongoose_DEFINES} \

########################################################################

HEADERS += \
$${XOS_SRC}/xos/inet/http/Form.hpp \
$${XOS_SRC}/xos/inet/http/UrlEncodedReader.hpp \
$${XOS_SRC}/xos/inet/http/FormReader.hpp \
$${XOS_SRC}/xos/inet/http/Request.hpp \
$${XOS_SRC}/xos/inet/http/Response.hpp \
$${XOS_SRC}/xos/inet/http/server/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/hello/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/javax/ServletRequest.hpp \
$${XOS_SRC}/xos/inet/http/server/javax/ServletResponse.hpp \
$${XOS_SRC}/xos/inet/http/server/javax/ServletProcessor.hpp \
$${XOS_SRC}/xos/inet/http/server/mongoose/Daemon.hpp \

SOURCES += \
$${XOS_SRC}/xos/inet/http/Form.cpp \
$${XOS_SRC}/xos/inet/http/UrlEncodedReader.cpp \
$${XOS_SRC}/xos/inet/http/FormReader.cpp \
$${XOS_SRC}/xos/inet/http/Request.cpp \
$${XOS_SRC}/xos/inet/http/Response.cpp \
$${XOS_SRC}/xos/inet/http/server/hello/Processor.cpp \
$${XOS_SRC}/xos/inet/http/server/javax/ServletRequest.cpp \
$${XOS_SRC}/xos/inet/http/server/javax/ServletResponse.cpp \
$${XOS_SRC}/xos/inet/http/server/javax/ServletProcessor.cpp \
$${XOS_SRC}/xos/inet/http/server/javax/ServletProcessor_instance.cpp \
$${XOS_SRC}/xos/inet/http/server/mongoose/Daemon.cpp \
$${XOS_SRC}/xos/inet/http/server/mongoose/Daemon_instance.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/RootHttpServlet_instance.cpp \
$${XOS_SRC}/xos/os/Main_main.cpp \

########################################################################

HEADERS += \
$${XOS_SRC}/xos/jdk/webapps/examples/servlets/HelloWorld.hpp \

SOURCES += \
$${XOS_SRC}/xos/jdk/webapps/examples/servlets/HelloWorld.cpp \

########################################################################

HEADERS += \
$${XOS_SRC}/xos/jdk/javax/servlet/http/Cookie.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/Part.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpSession.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpUpgradeHandler.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletRequestWrapper.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletRequest.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletResponseWrapper.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletResponse.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServlet.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/RootHttpServlet.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/GenericServlet.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/DispatcherType.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/AsyncContext.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletInputStream.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletOutputStream.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletContext.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletConfig.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ProtocolHandler.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/RequestDispatcher.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletRequestWrapper.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletRequest.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletResponseWrapper.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletResponse.hpp \
$${XOS_SRC}/xos/jdk/javax/servlet/Servlet.hpp \
$${XOS_SRC}/xos/jdk/java/lang/Class.hpp \
$${XOS_SRC}/xos/jdk/java/lang/Enum.hpp \
$${XOS_SRC}/xos/jdk/java/lang/Object.hpp \
$${XOS_SRC}/xos/jdk/java/lang/String.hpp \
$${XOS_SRC}/xos/jdk/java/lang/StringBuffer.hpp \
$${XOS_SRC}/xos/jdk/java/lang/CharSequence.hpp \
$${XOS_SRC}/xos/jdk/java/lang/Comparable.hpp \
$${XOS_SRC}/xos/jdk/java/io/Reader.hpp \
$${XOS_SRC}/xos/jdk/java/io/Writer.hpp \
$${XOS_SRC}/xos/jdk/java/io/BufferedReader.hpp \
$${XOS_SRC}/xos/jdk/java/io/BufferedWriter.hpp \
$${XOS_SRC}/xos/jdk/java/io/PrintWriter.hpp \
$${XOS_SRC}/xos/jdk/java/io/InputStream.hpp \
$${XOS_SRC}/xos/jdk/java/io/OutputStream.hpp \
$${XOS_SRC}/xos/jdk/java/io/Serializable.hpp \
$${XOS_SRC}/xos/jdk/java/security/Principal.hpp \
$${XOS_SRC}/xos/jdk/java/util/Collection.hpp \
$${XOS_SRC}/xos/jdk/java/util/Enumeration.hpp \
$${XOS_SRC}/xos/jdk/java/util/Iterator.hpp \
$${XOS_SRC}/xos/jdk/java/util/List.hpp \
$${XOS_SRC}/xos/jdk/java/util/Locale.hpp \
$${XOS_SRC}/xos/jdk/java/util/Map.hpp \
$${XOS_SRC}/xos/jdk/java/util/Array.hpp \
$${XOS_SRC}/xos/jdk/java/Types.hpp \

SOURCES += \
$${XOS_SRC}/xos/jdk/javax/servlet/http/Cookie.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/Part.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpSession.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpUpgradeHandler.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletRequestWrapper.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletRequest.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletResponseWrapper.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServletResponse.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/HttpServlet.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/http/RootHttpServlet.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/GenericServlet.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/DispatcherType.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/AsyncContext.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletInputStream.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletOutputStream.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletContext.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletConfig.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ProtocolHandler.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/RequestDispatcher.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletRequestWrapper.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/ServletResponseWrapper.cpp \
$${XOS_SRC}/xos/jdk/javax/servlet/Servlet.cpp \
$${XOS_SRC}/xos/jdk/java/lang/Class.cpp \
$${XOS_SRC}/xos/jdk/java/lang/Enum.cpp \
$${XOS_SRC}/xos/jdk/java/lang/Object.cpp \
$${XOS_SRC}/xos/jdk/java/lang/String.cpp \
$${XOS_SRC}/xos/jdk/java/lang/StringBuffer.cpp \
$${XOS_SRC}/xos/jdk/java/lang/CharSequence.cpp \
$${XOS_SRC}/xos/jdk/java/lang/Comparable.cpp \
$${XOS_SRC}/xos/jdk/java/io/Reader.cpp \
$${XOS_SRC}/xos/jdk/java/io/Writer.cpp \
$${XOS_SRC}/xos/jdk/java/io/BufferedReader.cpp \
$${XOS_SRC}/xos/jdk/java/io/BufferedWriter.cpp \
$${XOS_SRC}/xos/jdk/java/io/PrintWriter.cpp \
$${XOS_SRC}/xos/jdk/java/io/InputStream.cpp \
$${XOS_SRC}/xos/jdk/java/io/OutputStream.cpp \
$${XOS_SRC}/xos/jdk/java/io/Serializable.cpp \
$${XOS_SRC}/xos/jdk/java/security/Principal.cpp \
$${XOS_SRC}/xos/jdk/java/util/Collection.cpp \
$${XOS_SRC}/xos/jdk/java/util/Enumeration.cpp \
$${XOS_SRC}/xos/jdk/java/util/Iterator.cpp \
$${XOS_SRC}/xos/jdk/java/util/List.cpp \
$${XOS_SRC}/xos/jdk/java/util/Locale.cpp \
$${XOS_SRC}/xos/jdk/java/util/Map.cpp \
$${XOS_SRC}/xos/jdk/java/util/Array.cpp \
$${XOS_SRC}/xos/jdk/java/Types.cpp \

########################################################################

LIBS += \
$${libXosMongoose_LIBS} \
$${libXosCore_LIBS} \
-lpthread \
-ldl \


