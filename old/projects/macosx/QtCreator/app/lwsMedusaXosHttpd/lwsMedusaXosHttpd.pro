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
#   File: lwsMedusaXosHttpd.pro
#
# Author: $author$
#   Date: 6/15/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

libWebsockets_PKG = ../../../../../../libwebsockets/libwebsockets
libWebsockets_SRC = $${libWebsockets_PKG}/lib
libWebsockets_BLD = ../$${libWebsockets_PKG}/build
libWebsockets_LIB = $${libWebsockets_BLD}/lib

TARGET = lwsMedusaXosHttpd

INCLUDEPATH += \
$${libWebsockets_SRC} \
$${libXosCore_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

HEADERS += \
$${XOS_SRC}/xos/inet/http/Form.hpp \
$${XOS_SRC}/xos/inet/http/UrlEncodedReader.hpp \
$${XOS_SRC}/xos/inet/http/FormReader.hpp \
$${XOS_SRC}/xos/inet/http/Request.hpp \
$${XOS_SRC}/xos/inet/http/Response.hpp \
$${XOS_SRC}/xos/inet/http/server/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/libwebsockets/Daemon.hpp \
$${XOS_SRC}/xos/inet/http/server/libwebsockets/medusa/Daemon.hpp \

SOURCES += \
$${XOS_SRC}/xos/inet/http/Form.cpp \
$${XOS_SRC}/xos/inet/http/UrlEncodedReader.cpp \
$${XOS_SRC}/xos/inet/http/FormReader.cpp \
$${XOS_SRC}/xos/inet/http/Request.cpp \
$${XOS_SRC}/xos/inet/http/Response.cpp \
$${XOS_SRC}/xos/inet/http/Mime.cpp \
$${XOS_SRC}/xos/inet/http/server/path/HelloProcessor.cpp \
$${XOS_SRC}/xos/inet/http/server/path/Processor.cpp \
$${XOS_SRC}/xos/inet/http/server/Processors.cpp \
$${XOS_SRC}/xos/inet/http/server/Processors_instance.cpp \
$${XOS_SRC}/xos/inet/http/server/libwebsockets/medusa/Daemon.cpp \
$${XOS_SRC}/xos/inet/http/server/libwebsockets/medusa/Daemon_instance.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/method/GetProcessor.cpp \
$${XOS_SRC}/xos/os/Main_main.cpp \

LIBS += \
-L$${libWebsockets_LIB} \
-lwebsockets \
$${libXosCore_LIBS} \
-lssl \
-lcrypto \
-lpthread \
-ldl \
-lz \
