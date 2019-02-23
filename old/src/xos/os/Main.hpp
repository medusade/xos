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
///   File: Main.hpp
///
/// Author: $author$
///   Date: Jul 29, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MAIN_HPP_
#define _XOS_MAIN_HPP_

#include "xos/os/MainBase.hpp"
#include "xos/os/MainOpt.hpp"
#include "xos/os/StreamLogger.hpp"

#if !defined(XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID)
#if defined(XOS_DEFAULT_LOGGING_LEVELS_ID)
#define XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID() \
    xos::Main::OnLoggingLevel(XOS_MAIN_2STRING(XOS_DEFAULT_LOGGING_LEVELS_ID))
#else // defined(XOS_DEFAULT_LOGGING_LEVELS_ID)
#define XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID()
#endif // defined(XOS_DEFAULT_LOGGING_LEVELS_ID)
#endif // !defined(XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID)

namespace xos {

typedef MainBaseImplement MainImplement;
typedef MainBase MainExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class EXPORT_CLASS Logger: public StreamLogger {
    public:
        typedef StreamLogger Extends;
        Logger
        (Stream* attachedTo = 0,
         Level::Enable levelEnabled = XOS_STREAMLOGGER_LEVELS_ENABLED)
        : Extends(attachedTo, levelEnabled),
          m_oldDefault(GetDefault()){
              SetDefault(this);
        }
        virtual ~Logger(){
            if ((GetDefault() == this))
                SetDefault(m_oldDefault);
        }
    protected:
        xos::Logger* m_oldDefault;
    };

    bool m_didUsage;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main():m_didUsage(false){}
    virtual ~Main(){}

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeMain
    (int argc, char**argv, char**env)
    {
        int err = GetOptions(argc, argv, env);
        return err;
    }
    virtual int AfterMain
    (int argc, char**argv, char**env)
    {
        int err = 0;
        return err;
    }
    virtual bool DidMain() const
    {   return DidUsage(); }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Usage
    (int argc, char**argv, char**env)
    {
        int err = 0;
        const char* arg = 0;
        const char** args = 0;
        const char* argstring = Arguments(args);
        const struct option* longopts = 0;
        const char* optstring = Options(longopts);

        OutFormatted
        ("Usage: %s%s%s%s\n", argv[0], 
         (optstring)?(" [options]"):(""),
         (argstring)?(" "):(""), (argstring)?(argstring):(""));

        if ((optstring) && (longopts))
        {
            OutFormatted("\nOptions:\n");

            while ((longopts->name))
            {
                const char* optarg =
                (MAIN_OPT_ARGUMENT_REQUIRED == longopts->has_arg)?(" arg"):
                ((MAIN_OPT_ARGUMENT_OPTIONAL == longopts->has_arg)?(" [arg]"):(""));
                const char* optusage = OptionUsage(optarg, longopts);
                const char* optargSeparator = (optarg[0])?(" "):("");
                const char* optusageSeparator = "  ";

                OutFormatted
                (" -%c --%s%s%s%s%s\n",
                 longopts->val, longopts->name,
                 optargSeparator, optarg, optusageSeparator, optusage);
                longopts++;
            }
        }        
        if ((argstring) && (args))
        {
            OutFormatted("\nArguments:\n");

            while ((arg = (*args)))
            {
                OutFormatted(" %s\n", arg);
                args++;
            }
        }        
        SetDidUsage(true);
        return err;
    }
    virtual bool SetDidUsage(bool isTrue=true)
    {   return m_didUsage = isTrue; }
    virtual bool DidUsage() const
    {   return m_didUsage; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetOptions
    (int argc, char**argv, char**env)
    {
        int err = 0;
        int longindex = 0;
        const struct option* longopts = 0;
        char optvaluename[2] = {0,0};
        const char* optname = optvaluename;
        const char* optstring;
        int optvalue;

        //printf("GetOptions\n");for (int a = 0; a < argc; a++)
        //printf("argv[%d] = \"%s\"\n", a, argv[a]);

        if ((optstring = Options(longopts)) && (longopts))
        while (0 <= (optvalue = getopt_long
               (argc, argv, optstring, longopts, &longindex)))
        {
            optvaluename[0] = optvalue;
            optname = (longindex)?(longopts[longindex].name):(optvaluename);

            //printf("optvalue = %d optname = \"%s\"\n", optvalue, optname);

            if ((err = OnOption
               (optvalue, optarg, optname, longindex, argc, argv, env)))
                break;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static int OnLoggingOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = xos::OnLoggingOption
        (optval, optarg, optname, optind, argc, argv, env);
        return err;
    }
    static int OnLoggingLevel(const char* optarg)
    {
        int err = xos::OnLoggingLevel(optarg);
        return err;
    }
    virtual int OnUsageOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = 0;
        err = Usage(argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = 0;
        switch(optval)
        {
        case XOS_MAIN_LOGGING_OPTVAL_C:
            err = OnLoggingOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;

        case XOS_MAIN_HELP_OPTVAL_C:
            err = OnUsageOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
            
        default:
            err = 1;
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt)
    {
        const char* chars = "";
        switch(longopt->val)
        {
        case XOS_MAIN_LOGGING_OPTVAL_C:
            optarg = XOS_MAIN_LOGGING_OPTARG;
            break;
        case XOS_MAIN_HELP_OPTVAL_C:
            chars = XOS_MAIN_HELP_OPTUSE;
            break;
        }
        return chars;
    }
    virtual const char* Options
    (const struct option*& longopts)
    {
        int err = 0;
        static const char* chars = XOS_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    virtual const char* Arguments(const char**& args) {
        args = 0;
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace xos

#endif // _XOS_MAIN_HPP_ 
