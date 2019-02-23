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
#   File: qtXosHello.pro
#
# Author: $author$
#   Date: 6/9/2013
#
# QtCreator project for Executable qtXosHello
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

TARGET = qtXosHello

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
${QTDIR}/include \

DEFINES += \
$${libXosCore_DEFINES} \

HEADERS += \
$${XOS_SRC}/app/gui/qt/hello/Main.hpp \

SOURCES += \
$${XOS_SRC}/app/gui/qt/hello/Main.cpp \

LIBS += \
$${libXosCore_LIBS} \

QT += opengl
