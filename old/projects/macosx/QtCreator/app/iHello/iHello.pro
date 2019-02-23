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
#   File: iHello.pro
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../../QtCreator/lib/libXosCocoa.pri)

TARGET = iHello

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${XosMxde_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

OBJECTIVE_HEADERS += \
$${XOS_SRC}/xos/gui/cocoa/os/Os.hh \
$${XOS_SRC}/xos/gui/cocoa/os/LoggerStream.hh \
$${XOS_SRC}/xos/gui/cocoa/os/StreamLogger.hh \
$${XOS_SRC}/xos/gui/cocoa/os/iOsX.hh \
$${XOS_SRC}/xos/gui/cocoa/os/iCocoa.hh \
$${XOS_SRC}/xos/gui/cocoa/osx/LoggerStream.hh \
$${XOS_SRC}/xos/gui/cocoa/osx/StreamLogger.hh \
$${XOS_SRC}/xos/gui/cocoa/osx/iCocoa.hh \
$${XOS_SRC}/xos/gui/cocoa/iMain.hh \
$${XOS_SRC}/xos/gui/cocoa/iMain_main.hh \
$${XOS_SRC}/xos/gui/cocoa/iOptMain.hh \
$${XOS_SRC}/xos/gui/cocoa/iWindowMain.hh \
$${XOS_SRC}/app/gui/cocoa/hello/iHelloMain.hh \
$${libXosCocoa_OBJECTIVE_HEADERS} \

OBJECTIVE_SOURCES += \
$${XOS_SRC}/xos/gui/cocoa/os/Os.mm \
$${XOS_SRC}/xos/gui/cocoa/os/LoggerStream.mm \
$${XOS_SRC}/xos/gui/cocoa/os/StreamLogger.mm \
$${XOS_SRC}/xos/gui/cocoa/os/iOsX.mm \
$${XOS_SRC}/xos/gui/cocoa/os/iCocoa.mm \
$${XOS_SRC}/xos/gui/cocoa/iMain.mm \
$${XOS_SRC}/xos/gui/cocoa/iMain_main.mm \
$${XOS_SRC}/xos/gui/cocoa/iOptMain.mm \
$${XOS_SRC}/xos/gui/cocoa/iWindowMain.mm \
$${XOS_SRC}/app/gui/cocoa/hello/iHelloMain.mm \
$${XOS_SRC}/xos/gui/opengl/cocoa/Context.mm \
$${XOS_SRC}/xos/gui/opengl/cocoa/ImageRenderer.mm \

#$${libXosCocoa_OBJECTIVE_SOURCES} \

HEADERS += \

SOURCES += \

LIBS += \
$${libXosCore_LIBS} \

QT += opengl
