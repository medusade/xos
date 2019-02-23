########################################################################
# Copyright (c) 1988-2015 $organization$
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
#   File: libXosCrypto.pri
#
# Author: $author$
#   Date: 4/24/2015
#
# QtCreator project include for Static Library libXosCrypto
########################################################################

########################################################################
# bn
XosBn_INCLUDEPATH += \
$${XOS_SRC}/thirdparty/openssl/bn \

XosBn_LIBS += \
-L$${XOS_LIB}/libbn \
-lbn \

########################################################################
# mp
XosMp_INCLUDEPATH += \
$${XOS_MXDE_SRC}/thirdparty/gnu/mp \

XosMp_LIBS += \
-L$${XOS_LIB}/libmp \
-L$${XOS_LIB}/libmpn \
-L$${XOS_LIB}/libmpz \
-lmp \
-lmpn \
-lmpz \

########################################################################
# gmp
XOS_GMP_VERSION = 5.1.3
XOS_GMP_SRC = $${XOS_PRJ}/../gmp/gmp-$${XOS_GMP_VERSION}
XOS_GMP_BLD = $${XOS_BLD}/../../../../../../../build/gmp-$${XOS_GMP_VERSION}
XOS_GMP_LIB = $${XOS_GMP_BLD}/lib

XosGmp_INCLUDEPATH += \
$${XOS_GMP_SRC} \

XosGmp_LIBS += \
-L$${XOS_GMP_LIB} \
-lgmp \

########################################################################

libXosCrypto_INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${XosBn_INCLUDEPATH} \
$${XosMp_INCLUDEPATH} \

libXosCrypto_DEFINES += \
$${libXosCore_DEFINES} \

########################################################################
# hashes
libXosCrypto_HEADERS += \
$${XOS_SRC}/xos/base/Types.hpp \
$${XOS_SRC}/xos/crypto/Base.hpp \
$${XOS_SRC}/xos/crypto/hash/Base.hpp \
$${XOS_SRC}/xos/crypto/hash/Mac.hpp \
$${XOS_SRC}/xos/crypto/hash/Md5.hpp \
$${XOS_SRC}/xos/crypto/hash/Sha1.hpp \
$${XOS_SRC}/xos/crypto/hash/Sha256.hpp \
$${XOS_SRC}/xos/crypto/hash/Sha512.hpp \

libXosCrypto_SOURCES += \
$${XOS_SRC}/xos/base/Types.cpp \
$${XOS_SRC}/xos/crypto/hash/Base.cpp \
$${XOS_SRC}/xos/crypto/hash/Mac.cpp \
$${XOS_SRC}/xos/crypto/hash/Md5.cpp \
$${XOS_SRC}/xos/crypto/hash/Sha1.cpp \
$${XOS_SRC}/xos/crypto/hash/Sha256.cpp \
$${XOS_SRC}/xos/crypto/hash/Sha512.cpp \

########################################################################
# rsa
libXosCrypto_HEADERS += \
$${XOS_SRC}/xos/crypto/rsa/Key.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/Key.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/PublicKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/PrivateKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/bn_msb.h \
$${XOS_SRC}/xos/crypto/rsa/mp/Key.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/PublicKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/PrivateKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/mpz_msb.h \

libXosCrypto_SOURCES += \
$${XOS_SRC}/xos/crypto/rsa/bn/bn_Keys.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/mp_Keys.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/bn_msb.c \
$${XOS_SRC}/xos/crypto/rsa/mp/mpz_msb.c \

########################################################################

libXosCrypto_LIBS += \
-L$${XOS_LIB}/libXosCrypto \
-lXosCrypto \
$${XosBn_LIBS} \
$${XosMp_LIBS} \


