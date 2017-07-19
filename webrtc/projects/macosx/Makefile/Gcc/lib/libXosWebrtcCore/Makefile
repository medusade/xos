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
# MacOSX Gcc Makefile for Xos libXosWebrtcCore Static Library
########################################################################

PKG = $(PWD)/../../../../../..

MAK = projects/Makefile/Gcc
PRJ = projects/macosx/Makefile/Gcc
SRC = src

include $(PKG)/$(PRJ)/Makedefines
include $(PKG)/$(PRJ)/Makedefines.webrtc
include $(PKG)/$(MAK)/lib/libXosCore/Makefile

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

#
# user includes
#
USRINCLUDES = \

#
# target
#
LIBTARGET = libXosWebrtcCore.$(LIBEXT)

#
# Static Library C sources
#
LIB_C_SOURCES = \

#
# Static Library C++ .cc sources
#
LIB_CC_SOURCES = \

#
# Static Library C++ .cxx sources
#
LIB_CXX_SOURCES = \

#
# Static Library C++ .cpp sources
#
LIB_CPP_SOURCES = \
$(_libXosCore_LIB_CPP_SOURCES) \

#
# Static Library Objective C .m sources
#
LIB_M_SOURCES = \

#
# Static Library Objective C++ .mm sources
#
LIB_MM_SOURCES = \

#
# Static Library depends
#
#LIBDEP = \
#$(PKG)/$(BLD)/libsomelib \
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

#
# Static Library depend rules
#
#$(PKG)/$(BLD)/libsomelib.a:
#	@(echo Building libsomelib.a ...;\
#	  pushd ../libsomelib;\
#	  ((make) || (exit 1));\
#	  popd)
#
