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
#   File: medusaXosHttpd.pro
#
# Author: $author$
#   Date: 5/25/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../../QtCreator/app/medusaXosHttpd.pri)

TARGET = medusaXosHttpd

INCLUDEPATH += \
$${medusaXosHttpd_INCLUDEPATH} \

DEFINES += \
$${medusaXosHttpd_DEFINES} \

########################################################################
HEADERS += \
$${medusaXosHttpd_HEADERS} \

SOURCES += \
$${medusaXosHttpd_SOURCES} \

########################################################################
LIBS += \
$${medusaXosHttpd_LIBS} \
-lpthread \
-ldl \
