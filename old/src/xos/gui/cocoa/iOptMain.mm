///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: iOptMain.mm
///
/// Author: $author$
///   Date: 1/31/2014
///////////////////////////////////////////////////////////////////////

#include "xos/gui/cocoa/iOptMain.hh"

///////////////////////////////////////////////////////////////////////
/// Implentation: iOptMain
///////////////////////////////////////////////////////////////////////
@implementation iOptMain
    - (id)init {
        self = [super init];
        m_didUsage = false;
        return self;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    - (int)main:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        m_didUsage = false;
        XOS_LOG_TRACE("in...");
        if (!(err = [self getOptions:argc argv:argv env:env])) {
            if (!(m_didUsage)) {
                [super main:argc argv:argv env:env];
            }
        } else {
            XOS_LOG_TRACE("...error " << err << "on [getOptions]");
        }
        XOS_LOG_TRACE("...out");
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    - (int)usage:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        const char* arg = 0;
        const char** args = 0;
        const char* argstring = [self arguments:args];
        const struct option* longopts = 0;
        const char* optstring = [self options:longopts];

        printf
        ("Usage: %s%s%s%s\n", argv[0],
         (optstring)?(" [options]"):(""),
         (argstring)?(" "):(""), (argstring)?(argstring):(""));

        if ((optstring) && (longopts)) {
            printf("\nOptions:\n");

            while ((longopts->name)) {
                const char* optarg =
                (XOS_MAIN_OPT_ARGUMENT_REQUIRED == longopts->has_arg)?(" arg"):
                ((XOS_MAIN_OPT_ARGUMENT_OPTIONAL == longopts->has_arg)?(" [arg]"):(""));
                const char* optusage = [self optionUsage:optarg longopt:longopts];
                const char* optargSeparator = (optarg[0])?(" "):("");
                const char* optusageSeparator = "  ";

                printf
                (" -%c --%s%s%s%s%s\n",
                 longopts->val, longopts->name,
                 optargSeparator, optarg, optusageSeparator, optusage);
                longopts++;
            }
        }
        if ((argstring) && (args)) {
            printf("\nArguments:\n");

            while ((arg = (*args))) {
                printf(" %s\n", arg);
                args++;
            }
        }
        m_didUsage = true;
        return err;
    }
    - (int)getOptions:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        int longindex = 0;
        const struct option* longopts = 0;
        char optvaluename[2] = {0,0};
        const char* optname = optvaluename;
        const char* optstring;
        int optvalue;

        if ((optstring = [self options:longopts]) && (longopts))
        while (0 <= (optvalue = getopt_long
               (argc, argv, optstring, longopts, &longindex))) {
            optvaluename[0] = optvalue;
            optname = (longindex)?(longopts[longindex].name):(optvaluename);

            if ((err = [self onOption:optvalue optarg:optarg optname:optname
                        optind:longindex argc:argc argv:argv env:env])) {
                XOS_LOG_TRACE("...error " << err << " on [onOption]");
                break;
            }
        }
        return err;
    }
    - (int)onLoggingOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = xos::OnLoggingOption
        (optval, optarg, optname, optind, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    - (int)onOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        switch(optval) {
        case XOS_MAIN_LOGGING_OPTVAL_C:
            err = [self onLoggingOption:optval optarg:optarg optname:optname
                   optind:optind argc:argc argv:argv env:env];
            break;
        case XOS_MAIN_HELP_OPTVAL_C:
            err = [self usage:argc argv:argv env:env];
            break;
        default:
            err = 1;
        }
        return err;
    }
    - (const char*)optionUsage:(const char*&)optarg longopt:(const struct option*)longopt {
        const char* chars = "";
        switch(longopt->val) {
        case XOS_MAIN_LOGGING_OPTVAL_C:
            optarg = XOS_MAIN_LOGGING_OPTARG;
            break;
        case XOS_MAIN_HELP_OPTVAL_C:
            chars = XOS_MAIN_HELP_OPTUSE;
            break;
        }
        return chars;
    }
    - (const char*)options:(const struct option*&)longopts {
        static const char* chars = XOS_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    - (const char*)arguments:(const char**&)args {
        args = 0;
        return 0;
    }
@end
        

