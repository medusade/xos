########################################################################
# Copyright (c) 1988-2016 $organization$
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
#   File: gXosHello.pro
#
# Author: $author$
#   Date: 4/27/2016
#
# QtCreator project for Executable gXosHello
########################################################################
include(../../../../../build/QtCreator/gtk.pri)
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../../QtCreator/app/gXosHello.pri)

TARGET = gXosHello

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${build_gtk_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

########################################################################
HEADERS += \
$${gXosHello_HEADERS} \

SOURCES += \
$${gXosHello_SOURCES} \

########################################################################
LIBS += \
$${libXosCore_LIBS} \
$${build_gtk_LIBS} \
-lpthread \
-ldl \
-lrt \
