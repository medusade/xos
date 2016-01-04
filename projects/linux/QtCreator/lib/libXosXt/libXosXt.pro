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
#   File: libXosXt.pro
#
# Author: $author$
#   Date: 7/2/2013
#
# QtCreator project for Static Library libXosXt
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)

TARGET = XosXt

TEMPLATE = lib

CONFIG += staticlib

INCLUDEPATH += \
$$(HOME)/build/Motif/include \
$$(HOME)/build/motif/include \
$${libXosCore_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \

SOURCES += \
$${XOS_SRC}/xos/gui/x11/xt/AppContext.cpp \
$${XOS_SRC}/xos/gui/x11/xt/ApplicationShell.cpp \
$${XOS_SRC}/xos/gui/x11/xt/Arg.cpp \
$${XOS_SRC}/xos/gui/x11/xt/ArgArray.cpp \
$${XOS_SRC}/xos/gui/x11/xt/ArgList.cpp \
$${XOS_SRC}/xos/gui/x11/xt/Callback.cpp \
$${XOS_SRC}/xos/gui/x11/xt/EventHandler.cpp \
$${XOS_SRC}/xos/gui/x11/Intrinsic.cpp \
$${XOS_SRC}/xos/gui/x11/xt/Main.cpp \
$${XOS_SRC}/xos/gui/x11/xm/MwmUtil.cpp \
$${XOS_SRC}/xos/gui/x11/xt/Object.cpp \
$${XOS_SRC}/xos/gui/x11/xt/RectObject.cpp \
$${XOS_SRC}/xos/gui/x11/xt/String.cpp \
$${XOS_SRC}/xos/gui/x11/StringDefs.cpp \
$${XOS_SRC}/xos/gui/x11/xt/Widget.cpp \
$${XOS_SRC}/xos/gui/x11/xt/WidgetClass.cpp \
$${XOS_SRC}/xos/gui/x11/xt/WindowObject.cpp \
$${XOS_SRC}/xos/gui/x11/xt/WMShell.cpp \

