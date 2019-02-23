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
#   File: Makefile
#
# Author: $author$
#   Date: 3/7/2013
#
# MacOSX Gcc Makefile for Xos iXosHello Executable
########################################################################

PKG = $(PWD)/../../../../../..

PRJ = projects/macosx/Makefile/Gcc
SRC = src

include $(PKG)/$(PRJ)/Makedefines

#
# user ld flags
#
USRLDFLAGS = \
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
# user c flags
#
USRCFLAGS = \

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
# user libdirs
#
USRLIBDIRS = \

#
# target
#
EXETARGET = iXosHello

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
$(PKG)/$(SRC)/xos/gui/cocoa/iXosHello.mm \
$(PKG)/$(SRC)/xos/gui/opengl/cocoa/Context.mm \
$(PKG)/$(SRC)/xos/gui/opengl/cocoa/ImageRenderer.mm \
$(PKG)/$(SRC)/xos/webrtc/peerconnection/client/cocoa/OpenGL.mm \

#$(PKG)/$(SRC)/xos/gui/cocoa/console/iXosHello.mm \
#$(PKG)/$(SRC)/platform/windows/cocoa/Foundation/Foundation.mm \

#
# Executable libs
#
#LIBS = \
#-lsomelib
#
LIBS = \
-ldl \
-lpthread \
-lXosCore \

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

        

