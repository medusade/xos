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
///   File: iXosOptMain.mm
///
/// Author: $author$
///   Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
#include "xos/gui/cocoa/console/iXosOptMain.hh"

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Implentation: iXosOptMain
///
///       Author: $author$
///         Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
@implementation iXosOptMain
    - (iXosOptMain*)init {
        [super init];
        m_didUsage = false;
        return self;
    }
    - (int)Run:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        return err;
    }
    - (int)Main:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        m_didUsage = false;
        if (!(err = [self GetOptions:argc argv:argv env:env])) {
            if (!(m_didUsage)) {
                [self Run:argc argv:argv env:env];
            }
        }
        return err;
    }
    - (int)Usage:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        const char* arg = 0;
        const char** args = 0;
        const char* argstring = [self Arguments:args];
        const struct option* longopts = 0;
        const char* optstring = [self Options:longopts];

        printf
        ("Usage: %s%s%s%s\n", argv[0], 
         (optstring)?(" [options]"):(""),
         (argstring)?(" "):(""), (argstring)?(argstring):(""));

        if ((optstring) && (longopts))
        {
            printf("\nOptions:\n");

            while ((longopts->name))
            {
                const char* optarg =
                (XOS_MAIN_OPT_ARGUMENT_REQUIRED == longopts->has_arg)?(" arg"):
                ((XOS_MAIN_OPT_ARGUMENT_OPTIONAL == longopts->has_arg)?(" [arg]"):(""));
                const char* optusage = [self OptionUsage:optarg longopt:longopts];
                const char* optargSeparator = (optarg[0])?(" "):("");
                const char* optusageSeparator = "  ";

                printf
                (" -%c --%s%s%s%s%s\n",
                 longopts->val, longopts->name,
                 optargSeparator, optarg, optusageSeparator, optusage);
                longopts++;
            }
        }        
        if ((argstring) && (args))
        {
            printf("\nArguments:\n");

            while ((arg = (*args)))
            {
                printf(" %s\n", arg);
                args++;
            }
        }        
        m_didUsage = true;
        return err;
    }
    - (int)GetOptions:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        int longindex = 0;
        const struct option* longopts = 0;
        char optvaluename[2] = {0,0};
        const char* optname = optvaluename;
        const char* optstring;
        int optvalue;

        if ((optstring = [self Options:longopts]) && (longopts))
        while (0 <= (optvalue = getopt_long
               (argc, argv, optstring, longopts, &longindex)))
        {
            optvaluename[0] = optvalue;
            optname = (longindex)?(longopts[longindex].name):(optvaluename);

            if ((err = [self OnOption:optvalue optarg:optarg optname:optname 
                        optind:longindex argc:argc argv:argv env:env]))
                break;
        }
        return err;
    }
    - (int)OnOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        switch(optval) {
        case 'l':
            err = [self OnLoggingOption:optval optarg:optarg optname:optname 
                   optind:optind argc:argc argv:argv env:env];
            break;
        case 'h':
            err = [self Usage:argc argv:argv env:env];
            break;
        default:
            err = 1;
        }
        return err;
    }
    - (int)OnLoggingOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = xos::OnLoggingOption
        (optval, optarg, optname, optind, argc, argv, env);
        return err;
    }
    - (const char*)OptionUsage:(const char*&)optarg longopt:(const struct option*)longopt {
        const char* chars = "";
        switch(longopt->val) {
        case 'l':
            optarg = "{(a)all|(n)none|(f)fatal|(e)error|(w)waring|(i)info|(t)trace|(d)debug}";
            chars = "Logging levels";
            break;
        case 'h':
            chars = "Usage options";
            break;
        }
        return chars;
    }
    - (const char*)Options:(const struct option*&)longopts {
        static const char* chars = XOS_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    - (const char*)Arguments:(const char**&)args {
        args = 0;
        return 0;
    }
@end
#else // defined(OBJC)  
#endif // defined(OBJC)
        

