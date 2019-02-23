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
#   File: XosCgi.pro
#
# Author: $author$
#   Date: 3/5/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

TARGET = XosCgi

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${XOS_PKG}/../libxml2/libxslt-1.2.26 \
$${XOS_PKG}/../libxml2/libxml2-2.7.8/include \

DEFINES += \
$${libXosCore_DEFINES} \

HEADERS += \
$${XOS_SRC}/xos/inet/http/server/xslt/libxslt/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/xslt/Processor.hpp \
$${XOS_SRC}/xos/xml/xslt/libxslt/Processor.hpp \
$${XOS_SRC}/xos/xml/xslt/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/hello/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/Processor.hpp \
$${XOS_SRC}/xos/inet/http/cgi/processor/Main.hpp \
$${XOS_SRC}/xos/inet/http/cgi/Content.hpp \
$${XOS_SRC}/xos/inet/http/cgi/Arguments.hpp \
$${XOS_SRC}/xos/inet/http/cgi/Environment.hpp \
$${XOS_SRC}/xos/inet/http/cgi/Main.hpp \
$${XOS_SRC}/xos/inet/http/cgi/Main_main.hpp \
$${XOS_SRC}/xos/inet/http/Version.hpp \
$${XOS_SRC}/xos/inet/http/Header.hpp \
$${XOS_SRC}/xos/inet/http/Content.hpp \
$${XOS_SRC}/xos/inet/http/Message.hpp \
$${XOS_SRC}/xos/inet/http/Request.hpp \
$${XOS_SRC}/xos/inet/http/Response.hpp \
$${XOS_SRC}/xos/os/Main.hpp \
$${XOS_SRC}/xos/os/Main_main.hpp \
$${XOS_SRC}/xos/base/StringStream.hpp \
$${XOS_SRC}/xos/base/StreamStream.hpp \
$${XOS_SRC}/xos/base/FormattedStream.hpp \

#$${XOS_SRC}/xos/inet/http/server/hello/Processor.cpp \
#$${XOS_SRC}/xos/inet/http/server/hello/Processor_instance.cpp \
#$${XOS_SRC}/xos/os/Daemon_instance.cpp \

SOURCES += \
$${XOS_SRC}/xos/inet/http/server/xslt/libxslt/Processor.cpp \
$${XOS_SRC}/xos/inet/http/server/xslt/libxslt/Processor_instance.cpp \
$${XOS_SRC}/xos/inet/http/cgi/processor/Main.cpp \
$${XOS_SRC}/xos/inet/http/cgi/processor/Main_instance.cpp \
$${XOS_SRC}/xos/inet/http/cgi/Arguments.cpp \
$${XOS_SRC}/xos/inet/http/cgi/Environment.cpp \
$${XOS_SRC}/xos/inet/http/cgi/Main_main.cpp \
$${XOS_SRC}/xos/inet/http/Version.cpp \
$${XOS_SRC}/xos/inet/http/Header.cpp \
$${XOS_SRC}/xos/inet/http/Content.cpp \
$${XOS_SRC}/xos/inet/http/Message.cpp \
$${XOS_SRC}/xos/inet/http/Request.cpp \
$${XOS_SRC}/xos/inet/http/Response.cpp \
$${XOS_SRC}/xos/base/StringStream.cpp \
$${XOS_SRC}/xos/base/StreamStream.cpp \
$${XOS_SRC}/xos/base/FormattedStream.cpp \

LIBS += \
$${libXosCore_LIBS} \
-L$${HOME}/build/lib \
-lexslt \
-lxslt \
-lxml2 \
-lpthread \
-ldl \
