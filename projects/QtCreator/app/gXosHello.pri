########################################################################
# Copyright (c) 1988-2016 $organization$
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
#   File: gXosHello.pri
#
# Author: $author$
#   Date: 4/28/2016
########################################################################

gXosHello_INCLUDEPATH += \
$${libXosCore_INCLUDEPATH} \

gXosHello_DEFINES += \
$${libXosCore_DEFINES} \

########################################################################
gXosHello_HEADERS += \
$${XOS_SRC}/xos/gui/glib/Object.hpp \
$${XOS_SRC}/xos/gui/glib/Boxed.hpp \
$${XOS_SRC}/xos/gui/glib/Glib.hpp \

gXosHello_SOURCES += \
$${XOS_SRC}/xos/gui/glib/Object.cpp \
$${XOS_SRC}/xos/gui/glib/Boxed.cpp \
$${XOS_SRC}/xos/gui/glib/Glib.cpp \

########################################################################
gXosHello_HEADERS += \
$${XOS_SRC}/xos/gui/gdk/Pixbuf.hpp \
$${XOS_SRC}/xos/gui/gdk/Gdk.hpp \

gXosHello_SOURCES += \
$${XOS_SRC}/xos/gui/gdk/Pixbuf.cpp \
$${XOS_SRC}/xos/gui/gdk/Gdk.cpp \

########################################################################
gXosHello_HEADERS += \
$${XOS_SRC}/xos/gui/gtk/application/WindowMain.hpp \
$${XOS_SRC}/xos/gui/gtk/application/Window.hpp \
$${XOS_SRC}/xos/gui/gtk/application/MainSignals.hpp \
$${XOS_SRC}/xos/gui/gtk/application/Main.hpp \
$${XOS_SRC}/xos/gui/gtk/Main.hpp \
$${XOS_SRC}/xos/gui/gtk/Widget.hpp \
$${XOS_SRC}/xos/gui/gtk/WidgetSignals.hpp \
$${XOS_SRC}/xos/gui/gtk/Gtk.hpp \

gXosHello_SOURCES += \
$${XOS_SRC}/xos/gui/gtk/application/WindowMain.cpp \
$${XOS_SRC}/xos/gui/gtk/application/Window.cpp \
$${XOS_SRC}/xos/gui/gtk/application/MainSignals.cpp \
$${XOS_SRC}/xos/gui/gtk/Widget.cpp \
$${XOS_SRC}/xos/gui/gtk/WidgetSignals.cpp \
$${XOS_SRC}/xos/gui/gtk/Gtk.cpp \

########################################################################
gXosHello_HEADERS += \
$${XOS_SRC}/xos/app/gui/gtk/hello/Main.hpp \
$${XOS_SRC}/xos/gui/Main.hpp \
$${XOS_SRC}/xos/os/Main.hpp \

gXosHello_SOURCES += \
$${XOS_SRC}/xos/app/gui/gtk/hello/Main.cpp \
$${XOS_SRC}/xos/os/Main_main.cpp \

########################################################################

gXosHello_LIBS += \
$${libXosCore_LIBS} \

