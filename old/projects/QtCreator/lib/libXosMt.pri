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
#   File: libXosMt.pri
#
# Author: $author$
#   Date: 7/29/2014
########################################################################

libXosMt_INCLUDEPATH += \

libXosMt_DEFINES += \

libXosMt_HEADERS += \
$${XOS_SRC}/xos/mt/os/Process.hpp \
$${XOS_SRC}/xos/mt/Process.hpp \
$${XOS_SRC}/xos/mt/os/Thread.hpp \
$${XOS_SRC}/xos/mt/Thread.hpp \
$${XOS_SRC}/xos/mt/os/Mutex.hpp \
$${XOS_SRC}/xos/mt/Mutex.hpp \
$${XOS_SRC}/xos/mt/os/Semaphore.hpp \
$${XOS_SRC}/xos/mt/Semaphore.hpp \
$${XOS_SRC}/xos/mt/os/Os.hpp \
$${XOS_SRC}/xos/mt/Acquirer.hpp \
$${XOS_SRC}/xos/mt/Locker.hpp \
$${XOS_SRC}/xos/mt/Waiter.hpp \
$${XOS_SRC}/xos/mt/Joiner.hpp \
$${XOS_SRC}/xos/mt/Runner.hpp \
$${XOS_SRC}/xos/mt/Run.hpp \

libXosMt_SOURCES += \
$${XOS_SRC}/xos/mt/os/Os.cpp \
$${XOS_SRC}/xos/mt/Acquirer.cpp \
$${XOS_SRC}/xos/mt/Locker.cpp \
$${XOS_SRC}/xos/mt/Waiter.cpp \
$${XOS_SRC}/xos/mt/Joiner.cpp \
$${XOS_SRC}/xos/mt/Runner.cpp \
$${XOS_SRC}/xos/mt/Run.cpp \

libXosMt_HEADERS += \
$${XOS_SRC}/xos/mt/Mutexes.hpp \
$${XOS_SRC}/xos/mt/os/Mutexes.hpp \

libXosMt_SOURCES += \
$${XOS_SRC}/xos/mt/Mutexes.cpp \

libXosMt_LIBS += \
-L$${XOS_LIB}/libXosMt \
-lXosMt \
