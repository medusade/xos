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
#   File: libXosIo.pro
#
# Author: $author$
#   Date: 4/14/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

TARGET = XosIo
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

HEADERS += \
$${XOS_SRC}/xos/io/file/Stream.hpp \
$${XOS_SRC}/xos/io/file/IStream.hpp \
$${XOS_SRC}/xos/io/file/OStream.hpp \
$${XOS_SRC}/xos/io/file/Reader.hpp \
$${XOS_SRC}/xos/io/file/Writer.hpp \
$${XOS_SRC}/xos/io/file/Sequence.hpp \
$${XOS_SRC}/xos/io/Locker.hpp \
$${XOS_SRC}/xos/io/Reader.hpp \
$${XOS_SRC}/xos/io/Writer.hpp \
$${XOS_SRC}/xos/io/IStream.hpp \
$${XOS_SRC}/xos/io/OStream.hpp \
$${XOS_SRC}/xos/io/Stream.hpp \
$${XOS_SRC}/xos/io/Sequence.hpp \
$${XOS_SRC}/xos/base/Logged.hpp \
$${XOS_SRC}/xos/base/Attacher.hpp \
$${XOS_SRC}/xos/base/Opener.hpp \

SOURCES += \
$${XOS_SRC}/xos/io/file/Stream.cpp \
$${XOS_SRC}/xos/io/file/IStream.cpp \
$${XOS_SRC}/xos/io/file/OStream.cpp \
$${XOS_SRC}/xos/io/file/Reader.cpp \
$${XOS_SRC}/xos/io/file/Writer.cpp \
$${XOS_SRC}/xos/io/file/Sequence.cpp \
$${XOS_SRC}/xos/io/Locker.cpp \
$${XOS_SRC}/xos/base/Logged.cpp \
$${XOS_SRC}/xos/base/Opener.cpp \
$${XOS_SRC}/xos/base/Attacher.cpp \

