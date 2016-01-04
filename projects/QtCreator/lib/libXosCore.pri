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
#   File: libXosCore.pri
#
# Author: $author$
#   Date: 6/8/2013
########################################################################
XOS_PKG = ../../../../..
XOS_BLD = ../..
XOS_PRJ = $${XOS_PKG}
XOS_BIN = $${XOS_BLD}/bin
XOS_LIB = $${XOS_BLD}/lib
XOS_SRC = $${XOS_PKG}/src

libXosCore_INCLUDEPATH += \
$${XOS_SRC} \

libXosCore_DEFINES += \

########################################################################
# gui
libXosCore_HEADERS += \
$${XOS_SRC}/xos/gui/ImageRenderer.hpp \
$${XOS_SRC}/xos/gui/qt/ImageRenderer.hpp \
$${XOS_SRC}/xos/gui/opengl/Context.hpp \
$${XOS_SRC}/xos/gui/opengl/ImageRenderer.hpp \

libXosCore_SOURCES += \
$${XOS_SRC}/xos/gui/ImageRenderers.cpp \
$${XOS_SRC}/xos/gui/opengl/Context.cpp \

########################################################################
# inet
libXosCore_HEADERS += \
$${XOS_SRC}/xos/inet/json/Node.hpp \
$${XOS_SRC}/xos/inet/json/Text.hpp \

libXosCore_SOURCES += \
$${XOS_SRC}/xos/inet/json/Node.cpp \
$${XOS_SRC}/xos/inet/json/Text.cpp \

########################################################################
# network
libXosCore_HEADERS += \
$${XOS_SRC}/xos/network/Addresses.hpp \
$${XOS_SRC}/xos/network/ip/v4/AddressString.hpp \
$${XOS_SRC}/xos/network/Endpoints.hpp \
$${XOS_SRC}/xos/network/Transports.hpp \

libXosCore_SOURCES += \
$${XOS_SRC}/xos/network/Addresses.cpp \
$${XOS_SRC}/xos/network/ip/v4/AddressString.cpp \
$${XOS_SRC}/xos/network/Endpoints.cpp \
$${XOS_SRC}/xos/network/Transports.cpp \

########################################################################
# fs
libXosCore_HEADERS += \
$${XOS_SRC}/xos/fs/Path.hpp \
$${XOS_SRC}/xos/fs/PathDirectory.hpp \
$${XOS_SRC}/xos/fs/PathDirectoryAppender.hpp \
$${XOS_SRC}/xos/fs/PathParser.hpp \
$${XOS_SRC}/xos/fs/PathParserEvents.hpp \
$${XOS_SRC}/xos/fs/Time.hpp \

libXosCore_SOURCES += \
$${XOS_SRC}/xos/fs/Path.cpp \
$${XOS_SRC}/xos/fs/PathDirectory.cpp \
$${XOS_SRC}/xos/fs/PathDirectoryAppender.cpp \
$${XOS_SRC}/xos/fs/PathParser.cpp \
$${XOS_SRC}/xos/fs/PathParserEvents.cpp \

########################################################################
# os
libXosCore_HEADERS += \
$${XOS_SRC}/xos/os/FILEStream.hpp \
$${XOS_SRC}/xos/os/Logger.hpp \
$${XOS_SRC}/xos/os/MainBase.hpp \
$${XOS_SRC}/xos/os/MainOpt.hpp \
$${XOS_SRC}/xos/os/StreamLogger.hpp \
$${XOS_SRC}/xos/os/Mutex.hpp \
$${XOS_SRC}/xos/os/Process.hpp \
$${XOS_SRC}/xos/os/Semaphore.hpp \
$${XOS_SRC}/xos/os/Thread.hpp \
$${XOS_SRC}/xos/os/Time.hpp \

libXosCore_SOURCES += \
$${XOS_SRC}/xos/os/FILEStream.cpp \
$${XOS_SRC}/xos/os/Logger.cpp \
$${XOS_SRC}/xos/os/MainBase.cpp \
$${XOS_SRC}/xos/os/MainOpt.cpp \
$${XOS_SRC}/xos/os/StreamLogger.cpp \

libXosCore_HEADERS += \
$${XOS_SRC}/xos/os/os/Times.hpp \
$${XOS_SRC}/xos/os/os/Time.hpp \

########################################################################
# base
libXosCore_HEADERS += \
$${XOS_SRC}/xos/base/Acquired.hpp \
$${XOS_SRC}/xos/base/Array.hpp \
$${XOS_SRC}/xos/base/Attached.hpp \
$${XOS_SRC}/xos/base/Base.hpp \
$${XOS_SRC}/xos/base/Coded.hpp \
$${XOS_SRC}/xos/base/Created.hpp \
$${XOS_SRC}/xos/base/Creator.hpp \
$${XOS_SRC}/xos/base/Error.hpp \
$${XOS_SRC}/xos/base/ExportBase.hpp \
$${XOS_SRC}/xos/base/InterfaceBase.hpp \
$${XOS_SRC}/xos/base/Join.hpp \
$${XOS_SRC}/xos/base/List.hpp \
$${XOS_SRC}/xos/base/Literal.hpp \
$${XOS_SRC}/xos/base/Variant.hpp \
$${XOS_SRC}/xos/base/Locked.hpp \
$${XOS_SRC}/xos/base/Locker.hpp \
$${XOS_SRC}/xos/base/Named.hpp \
$${XOS_SRC}/xos/base/Opened.hpp \
$${XOS_SRC}/xos/base/Platform.hpp \
$${XOS_SRC}/xos/base/Reference.hpp \
$${XOS_SRC}/xos/base/Readerhpp \
$${XOS_SRC}/xos/base/StringReader.hpp \
$${XOS_SRC}/xos/base/Stream.hpp \
$${XOS_SRC}/xos/base/String.hpp \
$${XOS_SRC}/xos/base/StringBase.hpp \
$${XOS_SRC}/xos/base/Wait.hpp \
$${XOS_SRC}/xos/base/Wrapped.hpp \

libXosCore_SOURCES += \
$${XOS_SRC}/xos/base/Acquired.cpp \
$${XOS_SRC}/xos/base/Array.cpp \
$${XOS_SRC}/xos/base/Attached.cpp \
$${XOS_SRC}/xos/base/Base.cpp \
$${XOS_SRC}/xos/base/Coded.cpp \
$${XOS_SRC}/xos/base/Created.cpp \
$${XOS_SRC}/xos/base/Creator.cpp \
$${XOS_SRC}/xos/base/Error.cpp \
$${XOS_SRC}/xos/base/ExportBase.cpp \
$${XOS_SRC}/xos/base/InterfaceBase.cpp \
$${XOS_SRC}/xos/base/Join.cpp \
$${XOS_SRC}/xos/base/List.cpp \
$${XOS_SRC}/xos/base/Literal.cpp \
$${XOS_SRC}/xos/base/Variant.cpp \
$${XOS_SRC}/xos/base/Locked.cpp \
$${XOS_SRC}/xos/base/Locker.cpp \
$${XOS_SRC}/xos/base/Named.cpp \
$${XOS_SRC}/xos/base/Opened.cpp \
$${XOS_SRC}/xos/base/Platform.cpp \
$${XOS_SRC}/xos/base/Reference.cpp \
$${XOS_SRC}/xos/base/Reader.cpp \
$${XOS_SRC}/xos/base/StringReader.cpp \
$${XOS_SRC}/xos/base/Stream.cpp \
$${XOS_SRC}/xos/base/String.cpp \
$${XOS_SRC}/xos/base/StringBase.cpp \
$${XOS_SRC}/xos/base/Wait.cpp \
$${XOS_SRC}/xos/base/Wrapped.cpp \

libXosCore_HEADERS += \
$${XOS_SRC}/xos/base/Branch.hpp \
$${XOS_SRC}/xos/base/Tree.hpp \
$${XOS_SRC}/xos/base/AvlBranch.hpp \
$${XOS_SRC}/xos/base/RedblackBranch.hpp \
$${XOS_SRC}/xos/base/AvlTree.hpp \
$${XOS_SRC}/xos/base/RedblackTree.hpp \

libXosCore_SOURCES += \
$${XOS_SRC}/xos/base/Branch.cpp \
$${XOS_SRC}/xos/base/Tree.cpp \
$${XOS_SRC}/xos/base/AvlBranch.cpp \
$${XOS_SRC}/xos/base/RedblackBranch.cpp \
$${XOS_SRC}/xos/base/AvlTree.cpp \
$${XOS_SRC}/xos/base/RedblackTree.cpp \

########################################################################
libXosCore_LIBS += \
-L$${XOS_LIB}/libXosCore \
-lXosCore \

########################################################################
# mxde
XOS_MXDE_SRC = \
$${XOS_PRJ}/../mxde/c/src \

XOS_MXDE_LIB = \
$${XOS_BLD}/../../../../../mxde/c/build/macosx/QtCreator/Debug/lib \

XosMxde_INCLUDEPATH += \
$${XOS_SRC}/xos/mxde \
$${XOS_MXDE_SRC}/clib/ccrypto \
$${XOS_MXDE_SRC}/clib/cos/cplatform \
$${XOS_MXDE_SRC}/clib/cos \
$${XOS_MXDE_SRC}/clib/cbase \

########################################################################
# bn
XOS_BN_SRC = \
$${XOS_SRC}/thirdparty/openssl/bn \

XosBn_INCLUDEPATH = \
$${XOS_BN_SRC} \

XosBn_LIBS = \
-L$${XOS_LIB}/libbn \
-lbn \

########################################################################
# mp
XOS_MP_SRC = \
$${XOS_SRC}/thirdparty/gnu/mp \

XosMp_INCLUDEPATH = \
$${XOS_MP_SRC} \

XosMp_LIBS = \
-L$${XOS_LIB}/libmp \
-lmp \
-L$${XOS_LIB}/libmpn \
-lmpn \
-L$${XOS_LIB}/libmpz \
-lmpz \

