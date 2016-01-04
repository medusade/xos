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
#   File: iMd5.pro
#
# Author: $author$
#   Date: 2/5/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../../QtCreator/lib/libXosCocoa.pri)
include(../../lib/libXosCrypto.pri)

TARGET = iMd5

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

OBJECTIVE_HEADERS += \
$${XOS_SRC}/app/gui/cocoa/crypto/hash/MainWindow.hh \
$${XOS_SRC}/app/gui/cocoa/crypto/hash/iHash.hh \

OBJECTIVE_SOURCES += \
$${XOS_SRC}/app/gui/cocoa/crypto/hash/MainWindow.mm \
$${XOS_SRC}/app/gui/cocoa/crypto/hash/iHash.mm \
$${XOS_SRC}/app/gui/cocoa/crypto/hash/iMd5.mm \
$${XOS_SRC}/xos/gui/cocoa/iMain_main.mm \

HEADERS += \

SOURCES += \

LIBS += \
-L$${XOS_LIB}/libiCocoa \
-liCocoa \
$${libXosCore_LIBS} \
$${libXosCrypto_LIBS} \
