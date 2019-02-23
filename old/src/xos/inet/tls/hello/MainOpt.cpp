///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: MainOpt.cpp
///
/// Author: $author$
///   Date: 4/22/2016
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_TLS_HELLO_MAIN_HPP)
#include "MainOpt.hpp"

namespace xos {
namespace tls {
namespace hello {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
#endif // !defined(_XOS_TLS_HELLO_MAIN_HPP)
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval) {
        case XOS_TLS_HELLO_CLIENT_OPTVAL_C:
            err = OnClientOption(optval, optarg, optname, optind, argc, argv, env);
            break;

        case XOS_TLS_HELLO_VERSION_OPTVAL_C:
            switch(tolower(optarg[0])) {
            case XOS_TLS_HELLO_VERSION_OPTARG_1_0_C:
                err = OnTls10Option(optval, optarg, optname, optind, argc, argv, env);
                break;

            case XOS_TLS_HELLO_VERSION_OPTARG_1_1_C:
                err = OnTls11Option(optval, optarg, optname, optind, argc, argv, env);
                break;

            case XOS_TLS_HELLO_VERSION_OPTARG_1_2_C:
                err = OnTls12Option(optval, optarg, optname, optind, argc, argv, env);
                break;

            case XOS_TLS_HELLO_VERSION_OPTARG_1_2_HB_C:
                err = OnTls12HeartbeatOption(optval, optarg, optname, optind, argc, argv, env);
                break;
            }
            break;

        case XOS_TLS_HELLO_HOST_OPTVAL_C:
            err = OnHostOption(optval, optarg, optname, optind, argc, argv, env);
            break;

        case XOS_TLS_HELLO_PORT_OPTVAL_C:
            err = OnPortOption(optval, optarg, optname, optind, argc, argv, env);
            break;

        case XOS_TLS_HELLO_FAMILY_OPTVAL_C:
            switch(tolower(optarg[0])) {
            case XOS_TLS_HELLO_FAMILY_OPTARG_IPV4_C:
                err = OnIpV4FamilyOption(optval, optarg, optname, optind, argc, argv, env);
                break;

            case XOS_TLS_HELLO_FAMILY_OPTARG_IPV6_C:
                err = OnIpV6FamilyOption(optval, optarg, optname, optind, argc, argv, env);
                break;

            case XOS_TLS_HELLO_FAMILY_OPTARG_LOCAL_C:
                err = OnLocalFamilyOption(optval, optarg, optname, optind, argc, argv, env);
                break;
            }
            break;
        default:
            err = Extends::OnOption(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val) {
        case XOS_TLS_HELLO_CLIENT_OPTVAL_C:
            optarg = XOS_TLS_HELLO_CLIENT_OPTARG;
            chars = XOS_TLS_HELLO_CLIENT_OPTUSE;
            break;

        case XOS_TLS_HELLO_HOST_OPTVAL_C:
            optarg = XOS_TLS_HELLO_HOST_OPTARG;
            chars = XOS_TLS_HELLO_HOST_OPTUSE;
            break;

        case XOS_TLS_HELLO_PORT_OPTVAL_C:
            optarg = XOS_TLS_HELLO_PORT_OPTARG;
            chars = XOS_TLS_HELLO_PORT_OPTUSE;
            break;

        case XOS_TLS_HELLO_FAMILY_OPTVAL_C:
            optarg = XOS_TLS_HELLO_FAMILY_OPTARG;
            chars = XOS_TLS_HELLO_FAMILY_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char* Options(const struct option*& longopts) {
        static const char* chars = XOS_TLS_HELLO_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_TLS_HELLO_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_TLS_HELLO_MAIN_HPP)
};
} // namespace hello 
} // namespace tls 
} // namespace xos 
#endif // !defined(_XOS_TLS_HELLO_MAIN_HPP)
