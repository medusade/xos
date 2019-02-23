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
#   File: libXosRsa.pri
#
# Author: $author$
#   Date: 4/23/2015
########################################################################

libXosRsa_INCLUDEPATH += \
$${Xos_INCLUDEPATH} \
$${bn_INCLUDEPATH} \
$${mp_INCLUDEPATH} \

libXosRsa_DEFINES += \
$${Xos_DEFINES} \

########################################################################
# bn
libXosRsa_bn_HEADERS += \
$${XOS_SRC}/xos/crypto/rsa/bn/PrivateKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/PublicKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/KeyGenerator.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/Number.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/random/Reader.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/random/prime/MillerRabin.hpp \
$${XOS_SRC}/xos/crypto/rsa/bn/random/prime/Generator.hpp \

libXosRsa_bn_SOURCES += \
$${XOS_SRC}/xos/crypto/rsa/bn/PrivateKey.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/PublicKey.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/KeyGenerator.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/Number.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/random/Reader.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/random/prime/MillerRabin.cpp \
$${XOS_SRC}/xos/crypto/rsa/bn/random/prime/Generator.cpp \

########################################################################
# mp
libXosRsa_mp_HEADERS += \
$${XOS_SRC}/xos/crypto/rsa/mp/PrivateKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/PublicKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/KeyGenerator.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/Number.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/random/Reader.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/random/prime/MillerRabin.hpp \
$${XOS_SRC}/xos/crypto/rsa/mp/random/prime/Generator.hpp \

libXosRsa_mp_SOURCES += \
$${XOS_SRC}/xos/crypto/rsa/mp/PrivateKey.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/PublicKey.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/KeyGenerator.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/Number.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/random/Reader.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/random/prime/MillerRabin.cpp \
$${XOS_SRC}/xos/crypto/rsa/mp/random/prime/Generator.cpp \

########################################################################

libXosRsa_HEADERS += \
$${libXosRsa_bn_HEADERS} \
$${libXosRsa_mp_HEADERS} \
$${XOS_SRC}/xos/crypto/rsa/random/prime/Generator.hpp \
$${XOS_SRC}/xos/crypto/rsa/random/prime/SmallPrimes.hpp \
$${XOS_SRC}/xos/crypto/rsa/random/Reader.hpp \
$${XOS_SRC}/xos/crypto/rsa/PrivateKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/PublicKey.hpp \
$${XOS_SRC}/xos/crypto/rsa/KeyReader.hpp \
$${XOS_SRC}/xos/crypto/random/Pseudo.hpp \
$${XOS_SRC}/xos/crypto/Reader.hpp \
$${XOS_SRC}/xos/crypto/Writer.hpp \

libXosRsa_SOURCES += \
$${libXosRsa_mp_SOURCES} \
$${XOS_SRC}/xos/crypto/rsa/random/prime/SmallPrimes.cpp \
$${XOS_SRC}/xos/crypto/rsa/KeyReader.cpp \
$${XOS_SRC}/xos/crypto/random/Pseudo.cpp \

libXosRsa_LIBS += \
-L$${XOS_LIB}/libXosRsa \
-lXosRsa \
-L$${XOS_LIB}/libbn \
-lbn \
-L$${XOS_LIB}/libmpz \
-lmpz \
-L$${XOS_LIB}/libmpn \
-lmpn \
-L$${XOS_LIB}/libmp \
-lmp \

