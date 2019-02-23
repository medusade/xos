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
#   File: libXosX11.pro
#
# Author: $author$
#   Date: 7/1/2013
#
# QtCreator project for Static Library libXosX11
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

TARGET = XosX11

TEMPLATE = lib

CONFIG += staticlib

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

SOURCES += \
$${XOS_SRC}/xos/gui/x11/Atom.cpp \
$${XOS_SRC}/xos/gui/x11/Attached.cpp \
$${XOS_SRC}/xos/gui/x11/Color.cpp \
$${XOS_SRC}/xos/gui/x11/Colormap.cpp \
$${XOS_SRC}/xos/gui/x11/Context.cpp \
$${XOS_SRC}/xos/gui/x11/Created.cpp \
$${XOS_SRC}/xos/gui/x11/Display.cpp \
$${XOS_SRC}/xos/gui/x11/Event.cpp \
$${XOS_SRC}/xos/gui/x11/EventTarget.cpp \
$${XOS_SRC}/xos/gui/opengl/x11/ImageRenderer.cpp \
$${XOS_SRC}/xos/gui/x11/Main.cpp \
$${XOS_SRC}/xos/gui/x11/MainWindow.cpp \
$${XOS_SRC}/xos/gui/x11/OpenGL.cpp \
$${XOS_SRC}/xos/gui/x11/Property.cpp \
$${XOS_SRC}/xos/gui/x11/Screen.cpp \
$${XOS_SRC}/xos/gui/x11/Window.cpp \
$${XOS_SRC}/xos/gui/x11/WindowMain.cpp \
$${XOS_SRC}/xos/gui/x11/Xlib.cpp \

