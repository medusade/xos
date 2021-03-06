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
#   File: libXosMxdeCrypto.pro
#
# Author: $author$
#   Date: 1/24/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

TARGET = XosMxdeCrypto
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${XosMxde_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

########################################################################

HEADERS += \
$${XOS_SRC}/xos/crypto/hash/mxde/Hash.hpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Md5.hpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Sha1.hpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Sha256.hpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Sha512.hpp \

SOURCES += \
$${XOS_SRC}/xos/crypto/hash/mxde/Hash.cpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Md5.cpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Sha1.cpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Sha256.cpp \
$${XOS_SRC}/xos/crypto/hash/mxde/Sha512.cpp \

