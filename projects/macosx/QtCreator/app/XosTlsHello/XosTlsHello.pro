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
#   File: XosTlsHello.pro
#
# Author: $author$
#   Date: 4/23/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

TARGET = XosTlsHello

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

HEADERS += \
$${XOS_SRC}/xos/inet/tls/ClientHello.hpp \
$${XOS_SRC}/xos/inet/tls/Handshake.hpp \
$${XOS_SRC}/xos/inet/tls/Plaintext.hpp \
$${XOS_SRC}/xos/inet/tls/ProtocolVersion.hpp \
$${XOS_SRC}/xos/inet/tls/Base.hpp \
$${XOS_SRC}/xos/inet/tls/Protocol.hpp \
$${XOS_SRC}/xos/io/socket/Reader.hpp \
$${XOS_SRC}/xos/io/socket/Writer.hpp \
$${XOS_SRC}/xos/io/socket/Sequence.hpp \
$${XOS_SRC}/xos/inet/tls/hello/Main.hpp \

SOURCES += \
$${XOS_SRC}/xos/inet/tls/Base.cpp \
$${XOS_SRC}/xos/inet/tls/hello/Main.cpp \
$${XOS_SRC}/xos/inet/tls/hello/Main_instance.cpp \
$${XOS_SRC}/xos/io/socket/Reader.cpp \
$${XOS_SRC}/xos/io/socket/Writer.cpp \
$${XOS_SRC}/xos/io/socket/Sequence.cpp \
$${XOS_SRC}/xos/os/Main_main.cpp \

LIBS += \
$${libXosCore_LIBS} \
-lpthread \
-ldl \
