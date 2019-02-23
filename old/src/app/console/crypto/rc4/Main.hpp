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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 5/20/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CONSOLE_CRYPTO_RC4_MAIN_HPP
#define _XOS_CONSOLE_CRYPTO_RC4_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/crypto/cipher/Aes.hpp"
#include "xos/crypto/cipher/Des.hpp"
#include "xos/crypto/cipher/Rc4.hpp"
#include "xos/io/file/Writer.hpp"
#include "xos/io/attached/Writer.hpp"
#include "xos/base/Types.hpp"

namespace xos {
namespace crypto {
namespace cipher {
namespace rc4 {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement,public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char **argv, char **env) {
        static unsigned char key [8*3]={
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
            0xf1,0xe0,0xd3,0xc2,0xb5,0xa4,0x97,0x86,
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
        };
        static unsigned char iv  [8*2]={
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef
        };
        static unsigned char plain[8*4]={
            0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x20,
            0x4E,0x6F,0x77,0x20,0x69,0x73,0x20,0x74,
            0x68,0x65,0x20,0x74,0x69,0x6D,0x65,0x20,
            0x66,0x6F,0x72,0x20,0x00,0x31,0x00,0x00
        };
        static unsigned char cipher[8*4]={
            0x38,0x2A,0xB1,0xB3,0xD5,0x33,0x6B,0x09,
            0x64,0xDE,0x64,0x01,0x32,0x4C,0x05,0x38,
            0x4B,0xBB,0x0A,0x3A,0x7B,0xF5,0xE5,0x0C,
            0x20,0xA7,0x80,0xD1,0x5E,0xC3,0x37,0xEF
        };
        int err = 0;
        unsigned char out[8*4];
        Aes aes;
        int unequal;

        UChars::Set(out, 0, sizeof(out));

        AttachedT<FILE*, int, 0, io::file::Writer> o(StdOut());

        if (0 < (aes.Initialize(key,sizeof(key),iv,sizeof(iv)))) {
            if (0 < (aes.Encrypt(out, sizeof(out), plain, sizeof(plain)))) {
                o.Write("encrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, cipher, sizeof(out));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(cipher, sizeof(cipher));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        Bytes::Copy(cipher, out, sizeof(out));
        if (0 < (aes.Initialize(key,sizeof(key),iv,sizeof(iv)))) {
            if (0 < (aes.Decrypt(out, sizeof(out), cipher, sizeof(cipher)))) {
                o.Write("decrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, plain, sizeof(plain));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(plain, sizeof(plain));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunDes3(int argc, char **argv, char **env) {
        static unsigned char key [8*3]={
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
            0xf1,0xe0,0xd3,0xc2,0xb5,0xa4,0x97,0x86,
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
        };
        static unsigned char iv  [8]={
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
        };
        static unsigned char plain[32]={
            0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x20,
            0x4E,0x6F,0x77,0x20,0x69,0x73,0x20,0x74,
            0x68,0x65,0x20,0x74,0x69,0x6D,0x65,0x20,
            0x66,0x6F,0x72,0x20,0x00,0x00,0x00,0x00
        };
        static unsigned char cipher[32]={
            0x3F,0xE3,0x01,0xC9,0x62,0xAC,0x01,0xD0,
            0x22,0x13,0x76,0x3C,0x1C,0xBD,0x4C,0xDC,
            0x79,0x96,0x57,0xC0,0x64,0xEC,0xF5,0xD4,
            0x1C,0x67,0x38,0x12,0xCF,0xDE,0x96,0x75
        };
        int err = 0;
        unsigned char out[32];
        Des3 des3;
        int unequal;

        UChars::Set(out, 0, sizeof(out));

        AttachedT<FILE*, int, 0, io::file::Writer> o(StdOut());

        if (0 < (des3.Initialize(key,sizeof(key),iv,sizeof(iv)))) {
            if (0 < (des3.Encrypt(out, sizeof(out), plain, sizeof(plain)))) {
                o.Write("encrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, cipher, sizeof(out));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(cipher, sizeof(cipher));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        if (0 < (des3.Initialize(key,sizeof(key),iv,sizeof(iv)))) {
            if (0 < (des3.Decrypt(out, sizeof(out), cipher, sizeof(cipher)))) {
                o.Write("decrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, plain, sizeof(plain));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(plain, sizeof(plain));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunDes(int argc, char **argv, char **env) {
        static unsigned char key [8]={
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef
        };
        static unsigned char iv  [8]={
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
        };
        static unsigned char plain[32]={
            0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x20,
            0x4E,0x6F,0x77,0x20,0x69,0x73,0x20,0x74,
            0x68,0x65,0x20,0x74,0x69,0x6D,0x65,0x20,
            0x66,0x6F,0x72,0x20,0x00,0x00,0x00,0x00
        };
        static unsigned char cipher[32]={
            0xcc,0xd1,0x73,0xff,0xab,0x20,0x39,0xf4,
            0xac,0xd8,0xae,0xfd,0xdf,0xd8,0xa1,0xeb,
            0x46,0x8e,0x91,0x15,0x78,0x88,0xba,0x68,
            0x1d,0x26,0x93,0x97,0xf7,0xfe,0x62,0xb4
        };
        int err = 0;
        unsigned char out[32];
        Des des;
        int unequal;

        UChars::Set(out, 0, sizeof(out));

        AttachedT<FILE*, int, 0, io::file::Writer> o(StdOut());

        if (0 < (des.Initialize(key,sizeof(key),iv,sizeof(iv)))) {
            if (0 < (des.Encrypt(out, sizeof(out), plain, sizeof(plain)))) {
                o.Write("encrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, cipher, sizeof(out));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(cipher, sizeof(cipher));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        if (0 < (des.Initialize(key,sizeof(key),iv,sizeof(iv)))) {
            if (0 < (des.Decrypt(out, sizeof(out), cipher, sizeof(cipher)))) {
                o.Write("decrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, plain, sizeof(plain));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(plain, sizeof(plain));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunRc4(int argc, char **argv, char **env) {
        static unsigned char key[]={
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef
        };
        static unsigned char plain[]={
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef
        };
        static unsigned char cipher[]={
            0x75,0xb7,0x87,0x80,0x99,0xe0,0xc5,0x96
        };
        int err = 0;
        unsigned char out[sizeof(cipher)];
        Rc4 rc4;
        int unequal;

        UChars::Set(out, 0, sizeof(out));

        AttachedT<FILE*, int, 0, io::file::Writer> o(StdOut());

        if (0 < (rc4.Initialize(key, sizeof(key)))) {

            if (0 < (rc4.Encrypt(out, sizeof(out), plain, sizeof(plain)))) {
                o.Write("encrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, cipher, sizeof(out));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(cipher, sizeof(cipher));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        if (0 < (rc4.Initialize(key, sizeof(key)))) {

            if (0 < (rc4.Decrypt(out, sizeof(out), cipher, sizeof(cipher)))) {
                o.Write("decrypt ");
                o.Writex(out, sizeof(out));
                unequal = UChars::Compare(out, plain, sizeof(plain));
                o.Write((unequal)?(" != "):(" == "));
                o.Writex(plain, sizeof(plain));
                o.WriteLn((unequal)?(" failed"):(" success"));
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace rc4 
} // namespace cipher 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CONSOLE_CRYPTO_RC4_MAIN_HPP 
