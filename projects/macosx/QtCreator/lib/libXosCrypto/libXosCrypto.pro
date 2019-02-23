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
#   File: libXosCrypto.pro
#
# Author: $author$
#   Date: 7/28/2013
#
# QtCreator project for Static Library libXosCrypto
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../lib/libXosCrypto.pri)

TARGET = XosCrypto
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${libXosCrypto_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

HEADERS += \
$${XOS_SRC}/xos/base/Types.hpp \
$${XOS_SRC}/xos/crypto/Base.hpp \
$${XOS_SRC}/xos/crypto/hash/Base.hpp \
$${XOS_SRC}/xos/crypto/hash/Mac.hpp \
$${XOS_SRC}/xos/crypto/hash/Md5.hpp \
$${XOS_SRC}/xos/crypto/hash/Sha1.hpp \
$${XOS_SRC}/xos/crypto/hash/Sha256.hpp \
$${XOS_SRC}/xos/crypto/hash/Sha512.hpp \

SOURCES += \
$${XOS_SRC}/xos/base/Types.cpp \
$${XOS_SRC}/xos/crypto/hash/Base.cpp \
$${XOS_SRC}/xos/crypto/hash/Mac.cpp \
$${XOS_SRC}/xos/crypto/hash/Md5.cpp \
$${XOS_SRC}/xos/crypto/hash/Sha1.cpp \
$${XOS_SRC}/xos/crypto/hash/Sha256.cpp \
$${XOS_SRC}/xos/crypto/hash/Sha512.cpp \

########################################################################
# RSA

HEADERS += \
$${XOS_SRC}/xos/crypto/rsa/Key.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/Key.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/PublicKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/PrivateKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/bn_msb.h \
$${XOS_SRC}/xos/crypto/rsa/mp/Key.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/PublicKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/PrivateKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/mpz_msb.h \

SOURCES += \
$${XOS_SRC}/xos/crypto/rsa/bn/bn_Keys.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/mp_Keys.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/bn_msb.c \
$${XOS_SRC}/xos/crypto/rsa/mp/mpz_msb.c \
