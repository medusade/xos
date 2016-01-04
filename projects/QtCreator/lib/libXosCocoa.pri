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
#   File: libXosCocoa.pri
#
# Author: $author$
#   Date: 1/27/2014
########################################################################

libXosCocoa_OBJECTIVE_HEADERS += \
$${XOS_SRC}/xos/gui/cocoa/console/iXosMain_main.hh \
$${XOS_SRC}/xos/gui/cocoa/console/iXosMain.hh \
$${XOS_SRC}/xos/gui/cocoa/console/iXosBaseMain.hh \
$${XOS_SRC}/xos/gui/cocoa/console/iXosOptMain.hh \
$${XOS_SRC}/xos/gui/cocoa/iXosWindowMain.hh \

libXosCocoa_OBJECTIVE_SOURCES += \
$${XOS_SRC}/xos/gui/cocoa/console/iXosMain_main.mm \
$${XOS_SRC}/xos/gui/cocoa/console/iXosMain.mm \
$${XOS_SRC}/xos/gui/cocoa/console/iXosBaseMain.mm \
$${XOS_SRC}/xos/gui/cocoa/console/iXosOptMain.mm \
$${XOS_SRC}/xos/gui/cocoa/iXosWindowMain.mm \

QMAKE_LFLAGS += \
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
