########################################################################
# Copyright 2013, Google Inc.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote products
#     derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
# EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#   File: qtXosWebrtc.pro
#
# Author: $author$
#   Date: 7/16/2013
#
# QtCreator project for Executable qtXosWebrtc
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../QtCreator/XosWebrtc.pri)

libXosWebrtc_LIBS += \
-L$${XOS_LIB}/libXosWebrtcCore \
-L$${XOS_LIB}/libXosWebrtc \

libXosWebrtc_LIBS += \
-lXosWebrtcCore \
-lXosWebrtc \

TARGET = qtXosWebrtc

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${XosWebrtc_INCLUDEPATH} \
${QTDIR}/include \

DEFINES += \
$${XosWebrtc_DEFINES} \
$${libXosCore_DEFINES} \

SOURCES += \
$${XOS_SRC}/xos/gui/qt/WindowMain.cpp \
$${XOS_SRC}/xos/gui/opengl/Rectangle.cpp \

OBJECTIVE_SOURCES += \
$${XOS_SRC}/xos/webrtc/client/EventInterface.mm \
$${XOS_SRC}/xos/webrtc/client/ImageInterface.mm \
$${XOS_SRC}/xos/webrtc/client/firebreath/JavaScriptAPI.mm \
$${XOS_SRC}/xos/webrtc/client/console/PeerWindow.mm \
$${XOS_SRC}/xos/webrtc/client/console/Plugin.mm \
$${XOS_SRC}/xos/webrtc/client/PluginInterface.mm \
$${XOS_SRC}/xos/webrtc/client/console/PluginPeerWindow.mm \
$${XOS_SRC}/xos/webrtc/client/firebreath/PluginWindow.mm \
$${XOS_SRC}/xos/webrtc/client/console/PluginWindowPeer.mm \
$${XOS_SRC}/xos/webrtc/client/console/WindowPeer.mm \
$${XOS_SRC}/xos/webrtc/client/qt/Main.mm \
$${XOS_SRC}/xos/webrtc/client/qt/MainWindow.mm \
$${XOS_SRC}/xos/webrtc/client/qt/VideoRenderer.mm \
$${XOS_SRC}/xos/webrtc/client/qt/Widget.mm \
$${XOS_SRC}/xos/webrtc/client/Window.mm \

LIBS += \
$${libXosWebrtc_LIBS} \
$${XosWebrtc_LIBS} \
-framework QTKit \
-framework QuartzCore \
-framework CoreFoundation \
-framework CoreVideo \
-framework CoreAudio \
-framework Cocoa \
-framework Carbon \
-framework AudioToolbox \
-framework ApplicationServices \
-framework OpenGL \

xxHEADERS += \
$${XOS_SRC}/app/gui/qt/hello/Main.hpp \

xxSOURCES += \
$${XOS_SRC}/app/gui/qt/hello/Main.cpp \

xxLIBS += \
$${libXosWebrtc_LIBS} \
$${XosWebrtc_LIBS} \

QT += opengl
