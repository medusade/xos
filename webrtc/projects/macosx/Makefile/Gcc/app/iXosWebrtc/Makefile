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
#   File: Makefile
#
# Author: $author$
#   Date: 3/7/2013
#
# MacOSX Gcc Makefile for Xos iXosWebrtc Executable
########################################################################

PKG = $(PWD)/../../../../../..

PRJ = projects/macosx/Makefile/Gcc
SRC = src

include $(PKG)/$(PRJ)/Makedefines
include $(PKG)/$(PRJ)/Makedefines.webrtc

#
# user ld flags
#
USRLDFLAGS = \
$(WEBRTC_ARCHFLAGS) \
-Wl,-framework,QTKit \
-Wl,-framework,QuartzCore \
-Wl,-framework,CoreFoundation \
-Wl,-framework,CoreVideo \
-Wl,-framework,CoreAudio \
-Wl,-framework,Cocoa \
-Wl,-framework,Carbon \
-Wl,-framework,AudioToolbox \
-Wl,-framework,ApplicationServices \
-Wl,-framework,OpenGL \

#
# user cc flags
#
USRFLAGS = \
$(WEBRTC_ARCHFLAGS) \

#
# user c++ flags
#
USRCXXFLAGS = \

#
# user defines
#
USRDEFINES = \
$(WEBRTC_DEFINES) \

#
# user includes
#
USRINCLUDES = \
$(WEBRTC_INCLUDES) \

#
# user libdirs
#
USRLIBDIRS = \
$(WEBRTC_LIBDIRS) \

#
# target
#
EXETARGET = iXosWebrtc

#
# Executable C sources
#
EXE_C_SOURCES = \

#
# Executable C++ .cc sources
#
EXE_CC_SOURCES = \

#
# Executable C++ .cxx sources
#
EXE_CXX_SOURCES = \

#
# Executable C++ .cpp sources
#
EXE_CPP_SOURCES = \

#
# Executable Objective C .m sources
#
EXE_M_SOURCES = \

#
# Executable Objective C++ .mm sources
#
EXE_MM_SOURCES = \
$(PKG)/$(SRC)/xos/gui/cocoa/console/iXosMain_main.mm \
$(PKG)/$(SRC)/xos/gui/cocoa/console/iXosMain.mm \
$(PKG)/$(SRC)/xos/gui/cocoa/console/iXosBaseMain.mm \
$(PKG)/$(SRC)/xos/gui/cocoa/console/iXosOptMain.mm \
$(PKG)/$(SRC)/xos/gui/cocoa/iXosWindowMain.mm \
$(PKG)/$(SRC)/xos/gui/opengl/cocoa/Context.mm \
$(PKG)/$(SRC)/xos/webrtc/client/cocoa/OpenGL.mm \
$(PKG)/$(SRC)/xos/webrtc/client/cocoa/iXosWebrtcMainView.mm \
$(PKG)/$(SRC)/xos/webrtc/client/cocoa/iXosWebrtcMainWindow.mm \
$(PKG)/$(SRC)/xos/webrtc/client/cocoa/iXosWebrtcMain.mm \
$(PKG)/$(SRC)/xos/webrtc/client/cocoa/PlugoutMain.mm \
$(PKG)/$(SRC)/xos/webrtc/client/console/PlugoutWindowPeer.mm \
$(PKG)/$(SRC)/xos/webrtc/client/console/Plugin.mm \
$(PKG)/$(SRC)/xos/webrtc/client/console/PluginPeerWindow.mm \
$(PKG)/$(SRC)/xos/webrtc/client/console/PluginWindowPeer.mm \
$(PKG)/$(SRC)/xos/webrtc/client/console/WindowPeer.mm \
$(PKG)/$(SRC)/xos/webrtc/client/Window.mm \

#$(PKG)/$(SRC)/xos/webrtc/client/macosx/console/PeerWindow.mm \
#$(PKG)/$(SRC)/xos/webrtc/client/macosx/SocketServer.mm \
#$(PKG)/$(SRC)/xos/webrtc/client/macosx/UIMessage.mm \
#$(PKG)/$(SRC)/xos/os/macosx/Thread.mm \

#
# Executable libs
#
#LIBS = \
#-lsomelib
#
LIBS = \
-lXosWebrtcClient \
-lXosWebrtcCore \
$(WEBRTC_LIBS) \

#
# Executable depends
#
#EXEDEP = \
#$(PKG)/$(BLD)/libsomelib \
#
EXEDEP = \

#
# Executable depend dirs
#
#EXEDEP_DIRS = \
#../libsomelib
#
EXEDEP_DIRS = \

include $(PKG)/$(PRJ)/Makerules

#
# Executable depend rules
#
#$(PKG)/$(BLD)/libsomelib.a:
#	@(echo Building libsomelib.a ...;\
#	  pushd ../libsomelib;\
#	  ((make) || (exit 1));\
#	  popd)
#
