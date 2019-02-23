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
#   File: libXosLibjson.pro
#
# Author: $author$
#   Date: 1/11/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

libJson_PKG = $${XOS_PKG}/../libjson/libjson
libJson_SRC = $${libJson_PKG}
libJson_BLD = ../$${libJson_PKG}/build/macosx/QtCreator/Debug
libJson_LIB = $${libJson_BLD}/libjson

TARGET = XosLibjson

TEMPLATE = lib

CONFIG += staticlib

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${libJson_SRC} \

DEFINES += \

HEADERS += \
$${XOS_SRC}/xos/inet/json/Node.hpp \
$${XOS_SRC}/xos/inet/json/Text.hpp \
$${XOS_SRC}/xos/inet/json/libjson/Text.hpp \
$${XOS_SRC}/xos/inet/json/libjson/ToVariant.hpp \

SOURCES += \
$${XOS_SRC}/xos/inet/json/Node.cpp \
$${XOS_SRC}/xos/inet/json/libjson/Text.cpp \
$${XOS_SRC}/xos/inet/json/libjson/ToVariant.cpp \
