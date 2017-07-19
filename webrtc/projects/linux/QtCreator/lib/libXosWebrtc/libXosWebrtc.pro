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
#   File: libXosWebrtc.pro
#
# Author: $author$
#   Date: 8/8/2013
#
# QtCreator project for Static Library libXosWebrtc
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../QtCreator/XosWebrtc.pri)

TARGET = XosWebrtc

TEMPLATE = lib

CONFIG += staticlib

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${XosWebrtc_INCLUDEPATH} \

DEFINES += \
$${XosWebrtc_DEFINES} \
$${libXosCore_DEFINES} \

SOURCES += \
$${XOS_SRC}/xos/webrtc/client/Connection.cpp \
$${XOS_SRC}/xos/webrtc/client/ConnectionInterface.cpp \
$${XOS_SRC}/xos/webrtc/client/AudioVideo.cpp \
$${XOS_SRC}/xos/webrtc/client/Conductor.cpp \
$${XOS_SRC}/xos/webrtc/client/ConductorInterface.cpp \
$${XOS_SRC}/xos/webrtc/client/Options.cpp \
$${XOS_SRC}/xos/webrtc/client/PortServer.cpp \
$${XOS_SRC}/xos/webrtc/client/VideoCodec.cpp \
$${XOS_SRC}/xos/webrtc/client/ConnectorPair.cpp \
$${XOS_SRC}/xos/webrtc/client/Token.cpp \
$${XOS_SRC}/xos/webrtc/client/Trace.cpp \
$${XOS_SRC}/xos/webrtc/client/UserInterface.cpp \
$${XOS_SRC}/xos/webrtc/client/VideoRenderers.cpp \
$${XOS_SRC}/xos/webrtc/client/unix/Windows.cpp \
$${XOS_SRC}/xos/webrtc/client/unix/UIMessage.cpp \
$${XOS_SRC}/xos/webrtc/talk/base/unix/SocketServers.cpp \

