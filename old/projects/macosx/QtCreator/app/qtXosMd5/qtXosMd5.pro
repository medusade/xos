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
#   File: qtXosMd5.pro
#
# Author: $author$
#   Date: 7/28/2013
#
# QtCreator project for Executable qtXosMd5
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../lib/libXosCrypto.pri)

TARGET = qtXosMd5

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${libXosMxdeCrypto_INCLUDEPATH} \
${QTDIR}/include \

DEFINES += \
$${libXosCore_DEFINES} \

HEADERS += \
$${XOS_SRC}/app/gui/qt/crypto/hash/MainWindow.hpp \

SOURCES += \
$${XOS_SRC}/app/gui/qt/md5/Main.cpp \

libXosCrypto_LIBS += \
-L$${XOS_LIB}/libXosCrypto \

libXosCrypto_LIBS += \
-lXosCrypto \

LIBS += \
$${libXosCore_LIBS} \
$${libXosMxdeCrypto_LIBS} \

QT += opengl
