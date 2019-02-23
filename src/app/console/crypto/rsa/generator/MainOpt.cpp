///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   Date: 4/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAINOPT_CPP
#define _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAINOPT_CPP

#ifndef _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_HPP
#include "app/console/crypto/rsa/generator/MainOpt.hpp"

namespace xos {
namespace app {
namespace console {
namespace crypto {
namespace rsa {
namespace generator {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
#endif // ndef _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_HPP

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnGenerateOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            XOS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
            if (!(set_Generate(optarg))) {
                XOS_LOG_ERROR("...failed on set_Generate(\"" << optarg << "\")");
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnGeneratePrimeOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            XOS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
            if (!(set_GeneratePrime(optarg))) {
                XOS_LOG_ERROR("...failed on set_GeneratePrime(\"" << optarg << "\")");
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnBignumOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        set_Bignum(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnMpintOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        set_Mpint(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnRandomSeedOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            XOS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
            if (!(set_RandomSeed(optarg))) {
                XOS_LOG_ERROR("...failed on set_RandomSeed(\"" << optarg << "\")");
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATE_OPTVAL_C:
            err = OnGenerateOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATEPRIME_OPTVAL_C:
            err = OnGeneratePrimeOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_BIGNUM_OPTVAL_C:
            err = OnBignumOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_MPINT_OPTVAL_C:
            err = OnMpintOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_RANDOMSEED_OPTVAL_C:
            err = OnRandomSeedOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* OptionUsage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATE_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATE_OPTARG;
            chars = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATE_OPTUSE;
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATEPRIME_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATEPRIME_OPTARG;
            chars = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_GENERATEPRIME_OPTUSE;
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_BIGNUM_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_BIGNUM_OPTARG;
            chars = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_BIGNUM_OPTUSE;
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_MPINT_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_MPINT_OPTARG;
            chars = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_MPINT_OPTUSE;
            break;
        case XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_RANDOMSEED_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_RANDOMSEED_OPTARG;
            chars = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_RANDOMSEED_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* Options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

#ifndef _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_HPP
};

} // namespace generator 
} // namespace rsa 
} // namespace crypto 
} // namespace console 
} // namespace app 
} // namespace xos 
#endif // ndef _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_HPP

#endif // _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAINOPT_CPP 
