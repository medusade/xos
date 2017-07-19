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
#   File: XosWebrtc.pri
#
# Author: $author$
#   Date: 8/8/2013
#
# QtCreator project include for XosWebrtc
########################################################################
WEBRTC_BUILD_TYPE = Debug

WEBRTC_REVISION_NUMBER = 1125

WEBRTC_VERSION = webrtc-trunk-r-$${WEBRTC_REVISION_NUMBER}
WEBRTC_ROOT = $${XOS_PRJ}/../thirdparty/webrtc/$${WEBRTC_VERSION}
WEBRTC_BLD = $${XOS_BLD}/../../../../thirdparty/webrtc/$${WEBRTC_VERSION}
WEBRTC_BUILD = $${WEBRTC_BLD}/out/$${WEBRTC_BUILD_TYPE}

WEBRTC_DEFINES = \
POSIX \
LINUX \
CHROMIUM_BUILD \
WEBRTC_GEN_2_REVISION=1200 \
WEBRTC_REVISION=$${WEBRTC_REVISION_NUMBER} \

WEBRTC_INCLUDES = \
$${WEBRTC_ROOT} \
$${WEBRTC_ROOT}/src \
$${WEBRTC_ROOT}/third_party/libjingle/source \
$${WEBRTC_ROOT}/third_party_mods/libjingle/source \
$${WEBRTC_ROOT}/third_party/expat/files/lib \

WEBRTC_LIBDIRS = \
-L$${WEBRTC_BUILD} \

WEBRTC_LIBS = \
-lWebRtc \

XosWebrtc_INCLUDEPATH += \
$${WEBRTC_INCLUDES} \

XosWebrtc_DEFINES += \
$${WEBRTC_DEFINES} \

XosWebrtc_LIBS += \
$${WEBRTC_LIBDIRS} \
$${WEBRTC_LIBS} \

