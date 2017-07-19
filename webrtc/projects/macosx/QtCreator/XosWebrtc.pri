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
#   File: XosWebrtc.pri
#
# Author: $author$
#   Date: 7/16/2013
#
# QtCreator project include for XosWebrtc
########################################################################
WEBRTC_BUILD_TYPE = Debug

WEBRTC_REVISION_NUMBER = 1080

WEBRTC_VERSION = webrtc-trunk-r-$${WEBRTC_REVISION_NUMBER}
WEBRTC_ROOT = $${XOS_PRJ}/../webrtc/$${WEBRTC_VERSION}
WEBRTC_BLD = $${XOS_BLD}/../../../../../webrtc/$${WEBRTC_VERSION}
WEBRTC_BUILD = $${WEBRTC_BLD}/xcodebuild/$${WEBRTC_BUILD_TYPE}

WEBRTC_DEFINES = \
POSIX \
OSX \
CHROMIUM_BUILD \
WEBRTC_GEN_2_REVISION=1200 \
WEBRTC_REVISION=$${WEBRTC_REVISION_NUMBER} \

WEBRTC_INCLUDES = \
$${WEBRTC_ROOT} \
$${WEBRTC_ROOT}/src \
$${WEBRTC_ROOT}/third_party/libjingle/source \
$${WEBRTC_ROOT}/third_party_mods/libjingle/source \
$${WEBRTC_ROOT}/third_party/expat/files/lib \
$${WEBRTC_ROOT}../../gocast/webrtc_plugin/third_party_mods/webrtc/trunk/third_party/libjingle/source \

WEBRTC_LIBDIRS = \
-L$${WEBRTC_BUILD} \
-L$${WEBRTC_BUILD}/../../third_party/libsrtp

WEBRTC_1080_ARCH = i386

WEBRTC_1080_ARCHFLAGS = \
-arch $${WEBRTC_1080_ARCH} \

WEBRTC_1080_INTERNAL_LIBS_A = \
$${WEBRTC_BUILD}/libaec.a \
$${WEBRTC_BUILD}/libaecm.a \
$${WEBRTC_BUILD}/libagc.a \
$${WEBRTC_BUILD}/libapm_util.a \
$${WEBRTC_BUILD}/libaudio_coding_module.a \
$${WEBRTC_BUILD}/libaudio_conference_mixer.a \
$${WEBRTC_BUILD}/libaudio_device.a \
$${WEBRTC_BUILD}/libaudio_processing.a \
$${WEBRTC_BUILD}/libaudioproc_debug_proto.a \
$${WEBRTC_BUILD}/libaudioproc_unittest_proto.a \
$${WEBRTC_BUILD}/libCNG.a \
$${WEBRTC_BUILD}/libexpat.a \
$${WEBRTC_BUILD}/libG711.a \
$${WEBRTC_BUILD}/libG722.a \
$${WEBRTC_BUILD}/libgenperf_libs.a \
$${WEBRTC_BUILD}/libgmock.a \
$${WEBRTC_BUILD}/libgoogle-gflags.a \
$${WEBRTC_BUILD}/libgtest.a \
$${WEBRTC_BUILD}/libiLBC.a \
$${WEBRTC_BUILD}/libiSAC.a \
$${WEBRTC_BUILD}/libiSACFix.a \
$${WEBRTC_BUILD}/libjingle.a \
$${WEBRTC_BUILD}/libjingle_app.a \
$${WEBRTC_BUILD}/libjingle_p2p.a \
$${WEBRTC_BUILD}/libjpeg_turbo.a \
$${WEBRTC_BUILD}/libjsoncpp.a \
$${WEBRTC_BUILD}/libmedia_file.a \
$${WEBRTC_BUILD}/libNetEq.a \
$${WEBRTC_BUILD}/libNetEqTestTools.a \
$${WEBRTC_BUILD}/libns.a \
$${WEBRTC_BUILD}/libns_fix.a \
$${WEBRTC_BUILD}/libPCM16B.a \
$${WEBRTC_BUILD}/libprotobuf_full_do_not_use.a \
$${WEBRTC_BUILD}/libprotobuf_lite.a \
$${WEBRTC_BUILD}/libresampler.a \
$${WEBRTC_BUILD}/librtp_rtcp.a \
$${WEBRTC_BUILD}/libsignal_processing.a \
$${WEBRTC_BUILD}/libsystem_wrappers.a \
$${WEBRTC_BUILD}/libtest_framework.a \
$${WEBRTC_BUILD}/libtest_support.a \
$${WEBRTC_BUILD}/libtest_support_main.a \
$${WEBRTC_BUILD}/libudp_transport.a \
$${WEBRTC_BUILD}/libvad.a \
$${WEBRTC_BUILD}/libvideo_capture_module.a \
$${WEBRTC_BUILD}/libvideo_codecs_test_framework.a \
$${WEBRTC_BUILD}/libvideo_engine_core.a \
$${WEBRTC_BUILD}/libvideo_processing.a \
$${WEBRTC_BUILD}/libvideo_render_module.a \
$${WEBRTC_BUILD}/libvoice_engine_core.a \
$${WEBRTC_BUILD}/libvpx.a \
$${WEBRTC_BUILD}/libwebrtc_Debug.a \
$${WEBRTC_BUILD}/libwebrtc_i420.a \
$${WEBRTC_BUILD}/libwebrtc_jpeg.a \
$${WEBRTC_BUILD}/libwebrtc_utility.a \
$${WEBRTC_BUILD}/libwebrtc_video_coding.a \
$${WEBRTC_BUILD}/libwebrtc_vp8.a \
$${WEBRTC_BUILD}/libwebrtc_vplib.a \
$${WEBRTC_BUILD}/../../third_party/libsrtp/libsrtp.a \

WEBRTC_1080_INTERNAL_LIBS = \
-laec \
-laecm \
-lagc \
-lapm_util \
-laudio_coding_module \
-laudio_conference_mixer \
-laudio_device \
-laudio_processing \
-laudioproc_debug_proto \
-laudioproc_unittest_proto \
-lCNG \
-lexpat \
-lG711 \
-lG722 \
-lgenperf_libs \
-lgmock \
-lgoogle-gflags \
-lgtest \
-liLBC \
-liSAC \
-liSACFix \
-ljingle \
-ljingle_app \
-ljingle_p2p \
-ljpeg_turbo \
-ljsoncpp \
-lmedia_file \
-lNetEq \
-lNetEqTestTools \
-lns \
-lns_fix \
-lPCM16B \
-lprotobuf_full_do_not_use \
-lprotobuf_lite \
-lresampler \
-lrtp_rtcp \
-lsignal_processing \
-lsystem_wrappers \
-ltest_framework \
-ltest_support \

#-ltest_support_main \

WEBRTC_1080_INTERNAL_LIBS += \
-ludp_transport \
-lvad \
-lvideo_capture_module \
-lvideo_codecs_test_framework \
-lvideo_engine_core \
-lvideo_processing \
-lvideo_render_module \
-lvoice_engine_core \
-lvpx \
-lwebrtc_Debug \
-lwebrtc_i420 \
-lwebrtc_jpeg \
-lwebrtc_utility \
-lwebrtc_video_coding \
-lwebrtc_vp8 \
-lwebrtc_vplib \
-lsrtp \

WEBRTC_1080_EXTERNAL_LIBS = \

WEBRTC_LIBS = \
$${WEBRTC_1080_INTERNAL_LIBS} \
$${WEBRTC_1080_EXTERNAL_LIBS} \

WEBRTC_ARCHFLAGS = \
$${WEBRTC_1080_ARCHFLAGS} \

XosWebrtc_INCLUDEPATH += \
$${WEBRTC_INCLUDES} \

XosWebrtc_DEFINES += \
$${WEBRTC_DEFINES} \

XosWebrtc_LIBS += \
$${WEBRTC_ARCHFLAGS} \
$${WEBRTC_LIBDIRS} \
$${WEBRTC_LIBS} \

CONFIG -= x86_64 ppc64
CONFIG += x86
ARCHES -= x86_64
ARCHES += i386
