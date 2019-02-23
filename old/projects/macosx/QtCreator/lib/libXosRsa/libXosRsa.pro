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
#   File: libXosRsa.pro
#
# Author: $author$
#   Date: 4/23/2015
########################################################################
include(../../../../QtCreator/Xos.pri)
include(../../../../QtCreator/bn.pri)
include(../../../../QtCreator/mp.pri)
include(../../../../QtCreator/lib/libXosRsa.pri)
include(../../Xos.pri)

TARGET = XosRsa
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
$${libXosRsa_INCLUDEPATH} \

DEFINES += \
$${libXosRsa_DEFINES} \

HEADERS += \
$${libXosRsa_HEADERS} \

SOURCES += \
$${libXosRsa_SOURCES} \

