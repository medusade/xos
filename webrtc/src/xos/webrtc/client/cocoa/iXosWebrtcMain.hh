///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: iXosWebrtcMain.hh
///
/// Author: $author$
///   Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAIN_HH
#define _XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAIN_HH

#include "xos/webrtc/client/cocoa/iXosWebrtcMainWindow.hh"
#include "xos/webrtc/client/cocoa/iXosWebrtcMainView.hh"
#include "xos/webrtc/client/cocoa/PlugoutMain.hh"

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Interface: iXosWebrtcMain
///
///    Author: $author$
///      Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
@interface iXosWebrtcMain: iXosWindowMain {
    const char* m_imageFile;
    xos::webrtc::client::cocoa::PlugoutMain m_webrtcMain;
    }
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env;
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env;
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env;
    - (int)OnOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind 
               argc:(int)argc argv:(char**)argv env:(char**)env;
    - (const char*)OptionUsage:(const char*&)optarg longopt:(const struct option*)longopt;
    - (const char*)Options:(const struct option*&)longopts;
    - (id)init;
@end
#else // defined(OBJC)  
#endif // defined(OBJC)

#endif // _XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAIN_HH 
        

