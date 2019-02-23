########################################################################
# Copyright (c) 1988-$year$ $organization$
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
#   Date: 3/24/2013
#
# Linux Gcc Makefile for Xde libXosX11 Shared Library
########################################################################

PKG = $(PWD)/../../../../../..

PRJ = projects/linux/Makefile/Gcc
SRC = src

include $(PKG)/$(PRJ)/Makedefines

#
# user ld flags
#
USRLDFLAGS = \

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
SLIBTARGET = libXosX11.$(SLIBEXT)

#
# Shared Library C sources
#
SLIB_C_SOURCES = \

#
# Shared Library C++ .cc sources
#
SLIB_CC_SOURCES = \

#
# Shared Library C++ .cxx sources
#
SLIB_CXX_SOURCES = \

#
# Shared Library C++ .cpp sources
#
SLIB_CPP_SOURCES = \
$(PKG)/$(SRC)/xos/gui/x11/Atom.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Attached.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Color.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Colormap.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Context.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Created.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Display.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Event.cpp \
$(PKG)/$(SRC)/xos/gui/x11/EventTarget.cpp \
$(PKG)/$(SRC)/xos/gui/opengl/x11/ImageRenderer.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Main.cpp \
$(PKG)/$(SRC)/xos/gui/x11/MainWindow.cpp \
$(PKG)/$(SRC)/xos/gui/x11/OpenGL.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Property.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Screen.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Window.cpp \
$(PKG)/$(SRC)/xos/gui/x11/WindowMain.cpp \
$(PKG)/$(SRC)/xos/gui/x11/Xlib.cpp \

#
# Shared Library Objective C .m sources
#
SLIB_M_SOURCES = \

#
# Shared Library Objective C++ .mm sources
#
SLIB_MM_SOURCES = \

#
# Shared Library libs
#
#LIBS = \
#-lsomelib
#
LIBS = \
-lXosCore \
-lGL \
-lGLU \
-lX11 \
-lXext \
-lexpat \
-ldl \
-lrt \

#
# Shared Library depends
#
#SLIBDEP = \
#$(PKG)/$(BLD)/libsomelib \
#
SLIBDEP = \

#
# Shared Library depend dirs
#
#SLIBDEP_DIRS = \
#../libsomelib
#
SLIBDEP_DIRS = \

include $(PKG)/$(PRJ)/Makerules

#
# Shared Library depend rules
#
#$(PKG)/$(BLD)/libsomelib.a:
#	@(echo Building libsomelib.a ...;\
#	  pushd ../libsomelib;\
#	  ((make) || (exit 1));\
#	  popd)
#
