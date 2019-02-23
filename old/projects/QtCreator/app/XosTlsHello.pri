########################################################################
# Copyright (c) 1988-2016 $organization$
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
#   File: XosTlsHello.pri
#
# Author: $author$
#   Date: 4/20/2016
########################################################################

XosTlsHello_INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \

XosTlsHello_DEFINES += \
$${libXosCore_DEFINES} \

########################################################################
XosTlsHello_HEADERS += \
$${XOS_SRC}/xos/network/SocketWriter.hpp \
$${XOS_SRC}/xos/network/SocketReader.hpp \
$${XOS_SRC}/xos/network/os/Socket.hpp \
$${XOS_SRC}/xos/os/MainOpt.hpp \
$${XOS_SRC}/xos/os/Logger.hpp \

XosTlsHello_SOURCES += \
$${XOS_SRC}/xos/network/SocketWriter.cpp \
$${XOS_SRC}/xos/network/SocketReader.cpp \
$${XOS_SRC}/xos/os/Logger.cpp \

########################################################################
XosTlsHello_HEADERS += \
$${XOS_SRC}/xos/io/socket/Reader.hpp \
$${XOS_SRC}/xos/io/socket/Writer.hpp \
$${XOS_SRC}/xos/io/socket/Sequence.hpp \

XosTlsHello_SOURCES += \
$${XOS_SRC}/xos/io/socket/Reader.cpp \
$${XOS_SRC}/xos/io/socket/Writer.cpp \
$${XOS_SRC}/xos/io/socket/Sequence.cpp \

########################################################################
XosTlsHello_HEADERS += \
$${XOS_SRC}/xos/inet/tls/v12/ClientHello.hpp \
$${XOS_SRC}/xos/inet/tls/v12/HeartbeatExtension.hpp \
$${XOS_SRC}/xos/inet/tls/v12/ProtocolVersion.hpp \

XosTlsHello_SOURCES += \
$${XOS_SRC}/xos/inet/tls/v12/ClientHello.cpp \
$${XOS_SRC}/xos/inet/tls/v12/HeartbeatExtension.cpp \
$${XOS_SRC}/xos/inet/tls/v12/ProtocolVersion.cpp \

########################################################################
XosTlsHello_HEADERS += \
$${XOS_SRC}/xos/inet/tls/Client.hpp \
$${XOS_SRC}/xos/inet/tls/HeartbeatMessage.hpp \
$${XOS_SRC}/xos/inet/tls/Extension.hpp \
$${XOS_SRC}/xos/inet/tls/ServerHello.hpp \
$${XOS_SRC}/xos/inet/tls/ClientHello.hpp \
$${XOS_SRC}/xos/inet/tls/Handshake.hpp \
$${XOS_SRC}/xos/inet/tls/CipherSuites.hpp \
$${XOS_SRC}/xos/inet/tls/CipherSuite.hpp \
$${XOS_SRC}/xos/inet/tls/CompressionMethods.hpp \
$${XOS_SRC}/xos/inet/tls/CompressionMethod.hpp \
$${XOS_SRC}/xos/inet/tls/Plaintext.hpp \
$${XOS_SRC}/xos/inet/tls/ProtocolVersion.hpp \
$${XOS_SRC}/xos/inet/tls/GmtUnixTime.hpp \
$${XOS_SRC}/xos/inet/tls/Random.hpp \
$${XOS_SRC}/xos/inet/tls/Connection.hpp \
$${XOS_SRC}/xos/inet/tls/Base.hpp \
$${XOS_SRC}/xos/inet/tls/Protocol.hpp \

XosTlsHello_SOURCES += \
$${XOS_SRC}/xos/inet/tls/Client.cpp \
$${XOS_SRC}/xos/inet/tls/ServerHello.cpp \
$${XOS_SRC}/xos/inet/tls/HeartbeatMessage.cpp \
$${XOS_SRC}/xos/inet/tls/CipherSuites.cpp \
$${XOS_SRC}/xos/inet/tls/CipherSuite.cpp \
$${XOS_SRC}/xos/inet/tls/CompressionMethods.cpp \
$${XOS_SRC}/xos/inet/tls/CompressionMethod.cpp \
$${XOS_SRC}/xos/inet/tls/Extension.cpp \
$${XOS_SRC}/xos/inet/tls/GmtUnixTime.cpp \
$${XOS_SRC}/xos/inet/tls/Random.cpp \
$${XOS_SRC}/xos/inet/tls/Connection.cpp \
$${XOS_SRC}/xos/inet/tls/Base.cpp \

########################################################################
XosTlsHello_HEADERS += \
$${XOS_SRC}/xos/inet/tls/hello/Main.hpp \
$${XOS_SRC}/xos/inet/tls/hello/MainOpt.hpp \

XosTlsHello_SOURCES += \
$${XOS_SRC}/xos/inet/tls/hello/Main.cpp \
$${XOS_SRC}/xos/inet/tls/hello/Main_instance.cpp \
$${XOS_SRC}/xos/os/Main_main.cpp \

########################################################################

XosTlsHello_LIBS += \
$${libXosCore_LIBS} \


