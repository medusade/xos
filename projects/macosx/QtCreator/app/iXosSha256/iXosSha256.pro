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
#   File: iXosSha256.pro
#
# Author: $author$
#   Date: 1/29/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../../QtCreator/lib/libXosCocoa.pri)

TARGET = iXosSha256

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${XosMxde_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

OBJECTIVE_HEADERS += \
$${XOS_SRC}/app/gui/crypto/hash/cocoa/iCryptoHashMain.hh \
$${libXosCocoa_OBJECTIVE_HEADERS} \

OBJECTIVE_SOURCES += \
$${XOS_SRC}/app/gui/crypto/hash/cocoa/iCryptoHashMain.mm \
$${XOS_SRC}/app/gui/crypto/hash/cocoa/sha256/Main.mm \
$${libXosCocoa_OBJECTIVE_SOURCES} \

HEADERS += \
$${XOS_SRC}/app/gui/crypto/hash/MainWindow.hpp \

SOURCES += \
$${XOS_SRC}/app/gui/crypto/hash/MainWindow.cpp \

LIBS += \
$${libXosCore_LIBS} \
$${libXosCrypto_LIBS} \
