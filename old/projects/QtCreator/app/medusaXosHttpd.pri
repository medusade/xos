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
#   File: medusaXosHttpd.pri
#
# Author: $author$
#   Date: 1/8/2016
########################################################################

medusaXosHttpd_INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \

medusaXosHttpd_DEFINES += \
$${libXosCore_DEFINES} \

########################################################################
medusaXosHttpd_HEADERS += \
$${XOS_SRC}/xos/network/unix/Socket.hpp \
$${XOS_SRC}/xos/network/Socket.hpp \
$${XOS_SRC}/xos/io/File.hpp \
$${XOS_SRC}/xos/io/Reader2Reader.hpp \
$${XOS_SRC}/xos/mt/Queue.hpp \
$${XOS_SRC}/xos/os/MainImplement.hpp \
$${XOS_SRC}/xos/os/MainBaseImplement.hpp \
$${XOS_SRC}/xos/base/SizedReader.hpp \
$${XOS_SRC}/xos/base/Reference.hpp \

medusaXosHttpd_SOURCES += \
$${XOS_SRC}/xos/io/File.cpp \
$${XOS_SRC}/xos/io/Reader2Reader.cpp \
$${XOS_SRC}/xos/mt/Queue.cpp \
$${XOS_SRC}/xos/os/MainImplement.cpp \
$${XOS_SRC}/xos/os/MainBaseImplement.cpp \
$${XOS_SRC}/xos/os/Main_main.cpp \
$${XOS_SRC}/xos/base/SizedReader.hpp \

########################################################################
medusaXosHttpd_HEADERS += \
$${XOS_SRC}/xos/inet/http/server/Processors_instance.hpp \
$${XOS_SRC}/xos/inet/http/server/Processors.hpp \
$${XOS_SRC}/xos/inet/http/server/path/HelloProcessor.hpp \
$${XOS_SRC}/xos/inet/http/server/path/ByeProcessor.hpp \
$${XOS_SRC}/xos/inet/http/server/path/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/hello/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/bye/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/Daemon.hpp \
$${XOS_SRC}/xos/inet/http/server/Processor.hpp \
$${XOS_SRC}/xos/inet/http/Response.hpp \
$${XOS_SRC}/xos/inet/http/Request.hpp \
$${XOS_SRC}/xos/inet/http/Message.hpp \
$${XOS_SRC}/xos/inet/http/Mime.hpp \

medusaXosHttpd_SOURCES += \
$${XOS_SRC}/xos/inet/http/server/path/HelloProcessor.cpp \
$${XOS_SRC}/xos/inet/http/server/path/ByeProcessor.cpp \
$${XOS_SRC}/xos/inet/http/server/path/Processor.cpp \
$${XOS_SRC}/xos/inet/http/server/Processors.cpp \
$${XOS_SRC}/xos/inet/http/server/Processors_instance.cpp \
$${XOS_SRC}/xos/inet/http/Message.cpp \
$${XOS_SRC}/xos/inet/http/Mime.cpp \

########################################################################
medusaXosHttpd_HEADERS += \
$${XOS_SRC}/xos/inet/http/server/medusa/method/GetProcessor.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/method/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/request/HeadersReader.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/request/HeaderReader.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/request/LineReader.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpServerConfig.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpServer.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpAccept.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpConnection.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpService.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/ServerConfig.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Server.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Service.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Processor.hpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Daemon.hpp \

medusaXosHttpd_SOURCES += \
$${XOS_SRC}/xos/inet/http/server/medusa/method/GetProcessor.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/request/HeadersReader.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/request/HeaderReader.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/request/LineReader.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpServerConfig.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpServer.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpConnection.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpAccept.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/TcpService.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/ServerConfig.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Server.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Service.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Daemon.cpp \
$${XOS_SRC}/xos/inet/http/server/medusa/Daemon_instance.cpp \

########################################################################
medusaXosHttpd_LIBS += \
$${libXosCore_LIBS} \
