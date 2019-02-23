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
#   File: libXosMt.pro
#
# Author: $author$
#   Date: 7/29/2014
########################################################################
include(../../../../QtCreator/lib/libXosCore.pri)
include(../../../../QtCreator/lib/libXosMt.pri)

TARGET = XosMt
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \
$${libXosMt_INCLUDEPATH} \

DEFINES += \
$${libXosCore_DEFINES} \
$${libXosMt_DEFINES} \

HEADERS += \
$${libXosMt_HEADERS} \
$${XOS_SRC}/xos/mt/unix/Thread.hpp \
$${XOS_SRC}/xos/mt/unix/Mutex.hpp \
$${XOS_SRC}/xos/mt/unix/Semaphore.hpp \

SOURCES += \
$${libXosMt_SOURCES} \
$${XOS_SRC}/xos/mt/unix/Thread.cpp \
$${XOS_SRC}/xos/mt/unix/Mutex.cpp \
$${XOS_SRC}/xos/mt/unix/Semaphore.cpp \

