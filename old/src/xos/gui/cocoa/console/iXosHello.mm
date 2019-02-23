///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: iXosHello.mm
///
/// Author: $author$
///   Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
#include "xos/gui/cocoa/console/iXosHello.hh"

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Implentation: iXosHello
///
///       Author: $author$
///         Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@implementation iXosHello
    - (int)Run:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;

        printf("Hello:");
        if (m_name) {
            printf("%s", m_name);
        } else {
        for (int arg=1; arg<argc; arg++)
            printf("%s%s", (arg<2)?(" "):(","), argv[arg]);
        }
        printf("\n");

        for (int e=0; env[e]; e++)
            printf("%s\n", env[e]);
        return err;
    }
    - (int)OnOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind 
               argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        switch(optval) {
        case 'n':
            m_name = optarg;
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
        case 'n':
            optarg = "name";
            chars = "Hello name";
            break;
        default:
            chars = [super OptionUsage:optarg longopt:longopt];
        }
        return chars;
    }
    - (const char*)Options:(const struct option*&)longopts {
        static const char* chars = "n:" XOS_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            {"name", XOS_MAIN_OPT_ARGUMENT_REQUIRED, 0, 'n'},\
            XOS_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    - (id)init {
        [super init];
        m_name = 0;
        return self;
    }
@end
@implementation iXosMain
    + (id<iXosMain>)Allocate {
	    return [[iXosHello alloc] init];
    }
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  
