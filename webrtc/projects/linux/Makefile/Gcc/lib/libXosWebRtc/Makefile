########################################################################
# Copyright 2012, Google Inc.
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
#   Date: 10/21/2012
#
# Linux Gcc Makefile for Xos libXosWebRtc Static Library
########################################################################

PKG = $(PWD)/../../../../../..

MAK = projects/Makefile/Gcc
PRJ = projects/linux/Makefile/Gcc
SRC = src

include $(PKG)/$(PRJ)/Makedefines
include $(PKG)/$(PRJ)/Makedefines.webrtc
include $(PKG)/$(PRJ)/Makedefines.webrtcobjs
include $(PKG)/$(MAK)/lib/libXosCore/Makefile
include $(PKG)/$(MAK)/lib/libXosWebRtc/Makefile

#
# user ld flags
#
USRLDFLAGS = \
$(WEBRTC_LDFLAGS) \

#
# user c flags
#
USRCFLAGS = \
$(WEBRTC_CFLAGS) \

#
# user c++ flags
#
USRCXXFLAGS = \
$(WEBRTC_CXXFLAGS) \

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
# target
#
LIBTARGET = libXosWebRtc.$(LIBEXT)

#
# Static Library C sources
#
LIB_C_SOURCES = \

#
# Static Library C++ .cxx sources
#
LIB_CXX_SOURCES = \

#
# Static Library C++ .cpp sources
#
LIB_CPP_SOURCES = \
$(_libXosCore_SLIB_CPP_SOURCES) \
$(_libXosWebRtc_LIB_CPP_SOURCES) \
$(PKG)/$(SRC)/xos/webrtc/client/unix/Windows.cpp \
$(PKG)/$(SRC)/xos/webrtc/talk/base/unix/SocketServers.cpp \
$(PKG)/$(SRC)/xos/webrtc/client/unix/UIMessage.cpp \

#
# Static Library depends
#
#LIBDEP = \
#$(PKG)/$(BLD)/libsomelib.a \
#
LIBDEP = \

#
# Static Library depend dirs
#
#LIBDEP_DIRS = \
#../libsomelib
#
LIBDEP_DIRS = \

include $(PKG)/$(PRJ)/Makerules
include $(PKG)/$(PRJ)/Makerules.webrtcobjs

#
# Static Library depend rules
#
#$(PKG)/$(BLD)/libsomelib.a:
#	@(echo Building libsomelib.a ...;\
#	  pushd ../libsomelib;\
#	  ((make) || (exit 1));\
#	  popd)
#
