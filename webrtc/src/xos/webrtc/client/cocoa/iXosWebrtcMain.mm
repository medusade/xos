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
///   File: iXosWebrtcMain.mm
///
/// Author: $author$
///   Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/client/cocoa/iXosWebrtcMain.hh"

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Implentation: iXosWebrtcMain
///
///       Author: $author$
///         Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
@implementation iXosWebrtcMain
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env {
        NSRect superRect = [[NSScreen mainScreen] visibleFrame];
        NSRect rect = NSMakeRect(superRect.origin.x, superRect.size.height, DEFAULT_IXOSWINDOWMAIN_WINWOW_WIDTH, DEFAULT_IXOSWINDOWMAIN_WINWOW_HEIGHT);
        NSUInteger style = NSTitledWindowMask| NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
        NSBackingStoreType backing = NSBackingStoreBuffered;
        iXosWebrtcMainWindow* window = 0;
        NSView* view = 0;

        if ((window = [[iXosWebrtcMainWindow alloc] initWithContentRect:rect styleMask:style backing:backing defer:NO])) {
            [window setTitle:@DEFAULT_IXOSWINDOWMAIN_WINWOW_TITLE];
            [window setDelegate:window];
            [window SetImage:&m_webrtcMain];
            [window SetImageFile:m_imageFile];
            if ((view = [window CreateMainView:argc argv:argv env:env])) {
                [window setContentView:view];
            }
        }
        return window;
    }
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        if (!(err = [super BeforeRun:argc argv:argv env:env])) {
            err = m_webrtcMain.BeforeRun(argc, argv, env);
        }
        return err;
    }
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        int err2 = 0;
        err = m_webrtcMain.AfterRun(argc, argv, env);
        if ((err2 = [super AfterRun:argc argv:argv env:env])) {
            err = (!err)?(err2):(err);
        }
        return err;
    }
    - (int)OnOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind 
               argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        switch(optval) {
        case 'f':
            m_imageFile = optarg;
            break;
        default:
            err = [super OnOption:optval optarg:optarg optname:optname optind:optind
                   argc:argc argv:argv env:env];
        }
        return err;
    }
    - (const char*)OptionUsage:(const char*&)optarg longopt:(const struct option*)longopt {
        const char* chars = "";
        switch(longopt->val) {
        case 'f':
            optarg = "filename";
            chars = "Image filename";
            break;
        default:
            chars = [super OptionUsage:optarg longopt:longopt];
        }
        return chars;
    }
    - (const char*)Options:(const struct option*&)longopts {
        static const char* chars = "f:" XOS_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            {"image-file", XOS_MAIN_OPT_ARGUMENT_REQUIRED, 0, 'f'},\
            XOS_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    - (id)init {
        [super init];
        m_imageFile = 0;
        return self;
    }
@end
///////////////////////////////////////////////////////////////////////
/// Implentation: iXosMain
///
///       Author: $author$
///         Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
@implementation iXosMain
+ (id<iXosMain>)Allocate {
    return [[iXosWebrtcMain alloc] init];
}
@end
#else // defined(OBJC)  
#endif // defined(OBJC)
