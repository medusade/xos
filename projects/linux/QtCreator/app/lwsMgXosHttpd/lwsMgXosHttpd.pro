########################################################################
# Copyright (c) 1988-2013 $organization$
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
#   File: lwsMgXosHttpd.pro
#
# Author: $author$
#   Date: 12/8/2013
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

libWebsockets_PKG = ../../../../../../libwebsockets/libwebsockets
libWebsockets_SRC = $${libWebsockets_PKG}/lib
libWebsockets_BLD = ../$${libWebsockets_PKG}/build
libWebsockets_LIB = $${libWebsockets_BLD}/lib

Mongoose_PKG = ../../../../../../mongoose/mongoose
Mongoose_SRC = ../$${Mongoose_PKG}
Mongoose_BLD = ../$${Mongoose_PKG}/build
Mongoose_LIB = $${Mongoose_BLD}/linux/QtCreator/Debug/libmongoose

TARGET = lwsMgXosHttpd

INCLUDEPATH += \
$${Mongoose_SRC} \
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
$${XOS_SRC}/xos/inet/http/server/libwebsockets/mongoose/Daemon.hpp \

SOURCES += \
$${XOS_SRC}/xos/inet/http/Form.cpp \
$${XOS_SRC}/xos/inet/http/UrlEncodedReader.cpp \
$${XOS_SRC}/xos/inet/http/FormReader.cpp \
$${XOS_SRC}/xos/inet/http/Request.cpp \
$${XOS_SRC}/xos/inet/http/Response.cpp \
$${XOS_SRC}/xos/inet/http/server/Processor.cpp \
$${XOS_SRC}/xos/inet/http/server/hello/Processor_instance.cpp \
$${XOS_SRC}/xos/inet/http/server/libwebsockets/mongoose/Daemon.cpp \
$${XOS_SRC}/xos/inet/http/server/libwebsockets/mongoose/Daemon_instance.cpp \
$${XOS_SRC}/xos/os/Main_main.cpp \

LIBS += \
-L$${Mongoose_LIB} \
-lmongoose \
-L$${libWebsockets_LIB} \
-lwebsockets \
$${libXosCore_LIBS} \
-lssl \
-lcrypto \
-lpthread \
-ldl \
-lz \



        

