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
///   File: MainBaseImplement.hpp
///
/// Author: $author$
///   Date: 1/8/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_MAINBASEIMPLEMENT_HPP
#define _XOS_BASE_MAINBASEIMPLEMENT_HPP

#include "xos/base/Base.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: MainBaseImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainBaseImplement: virtual public InterfaceBase {
public:
    typedef InterfaceBase Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env){ return 0; }
    virtual int BeforeRun(int argc, char** argv, char** env){ return 0; }
    virtual int AfterRun(int argc, char** argv, char** env){ return 0; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Main(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = BeforeRun(argc, argv, env))) {
            int err2 = 0;
            err = Run(argc, argv, env);
            if ((err2 = AfterRun(argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    virtual int BeforeMain(int argc, char** argv, char** env){ return 0; }
    virtual int AfterMain(int argc, char** argv, char** env) { return 0; }
    virtual bool DidMain() const { return false; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int operator()(int argc, char** argv, char** env)  {
        int err = 1;
        if (!(err = BeforeMain(argc, argv, env))) {
            if (!(DidMain())) {
                int err2 = 0;
                err = Main(argc, argv, env);
                if ((err2 = AfterMain(argc, argv, env))) {
                    if (!(err)) err = err2;
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutFormattedLn(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        if ((format)) {
            count = OutFormattedVLn(format, va);
        }
        va_end(va);
        return count;
    }
    virtual ssize_t OutFormattedVLn(const char* format, va_list va) {
        ssize_t count = OutFormattedV(format, va);
        if (0 <= (count)) {
            ssize_t amount;
            if (0 <= (amount = OutLn()))
                count += amount;
            else count = amount;
        }
        return count;
    }
    virtual ssize_t OutFormatted(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        if ((format)) {
            count = OutFormattedV(format, va);
        }
        va_end(va);
        return count;
    }
    virtual ssize_t OutFormattedV(const char* format, va_list va) {
        ssize_t count = 0;
        if ((format)) {
            count = vfprintf(StdOut(), format, va);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutLLn(const char* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = OutVLn(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t OutVLn(const char* what, va_list va) {
        ssize_t count = OutV(what, va);
        if (0 <= (count)) {
            ssize_t amount;
            if (0 <= (amount = OutLn()))
                count += amount;
            else count = amount;
        }
        return count;
    }
    virtual ssize_t OutL(const char* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = OutV(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t OutV(const char* what, va_list va) {
        ssize_t count = 0;
        ssize_t length = 0;
        for (count = 0; what; count += length) {
            if (0 > (length = Out(what))) {
                return count;
            }
            what = va_arg(va, const char*);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutLn(const char* out, ssize_t length = -1) {
        ssize_t count;
        if (0 <= (count = Out(out, length))) {
            const char* lineFeed;
            ssize_t amount;
            if ((lineFeed = LineFeed(amount))) {
                if (0 > (amount = Out(lineFeed, amount))) {
                    return amount;
                } else {
                    count += amount;
                }
            }
        }
        return count;
    }
    virtual ssize_t OutLn() {
        ssize_t count = 0;
        const char* lineFeed;
        ssize_t amount;
        if ((lineFeed = LineFeed(amount))) {
            if (0 > (amount = Out(lineFeed, amount))) {
                return amount;
            } else {
                count += amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Out(const char* out, ssize_t length = -1) {
        ssize_t count = Out(StdOut(), out, length);
        return count;
    }
    virtual ssize_t OutFlush() {
        ssize_t count = OutFlush(StdOut());
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ErrFormattedLn(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        if ((format)) {
            count = ErrFormattedVLn(format, va);
        }
        va_end(va);
        return count;
    }
    virtual ssize_t ErrFormattedVLn(const char* format, va_list va) {
        ssize_t count = ErrFormattedV(format, va);
        if (0 <= (count)) {
            ssize_t amount;
            if (0 <= (amount = ErrLn()))
                count += amount;
            else count = amount;
        }
        return count;
    }
    virtual ssize_t ErrFormatted(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        if ((format)) {
            count = ErrFormattedV(format, va);
        }
        va_end(va);
        return count;
    }
    virtual ssize_t ErrFormattedV(const char* format, va_list va) {
        ssize_t count = 0;
        if ((format)) {
            count = vfprintf(StdErr(), format, va);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ErrLLn(const char* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = ErrVLn(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ErrVLn(const char* what, va_list va) {
        ssize_t count = ErrV(what, va);
        if (0 <= (count)) {
            ssize_t amount;
            if (0 <= (amount = ErrLn()))
                count += amount;
            else count = amount;
        }
        return count;
    }
    virtual ssize_t ErrL(const char* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = ErrV(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ErrV(const char* what, va_list va) {
        ssize_t count = 0;
        ssize_t length = 0;
        for (count = 0; what; count += length) {
            if (0 > (length = Err(what))) {
                return count;
            }
            what = va_arg(va, const char*);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ErrLn(const char* out, ssize_t length = -1) {
        ssize_t count;
        if (0 <= (count = Err(out, length))) {
            const char* lineFeed;
            ssize_t amount;
            if ((lineFeed = LineFeed(amount))) {
                if (0 > (amount = Err(lineFeed, amount))) {
                    return amount;
                } else {
                    count += amount;
                }
            }
        }
        return count;
    }
    virtual ssize_t ErrLn() {
        ssize_t count = 0;
        const char* lineFeed;
        ssize_t amount;
        if ((lineFeed = LineFeed(amount))) {
            if (0 > (amount = Err(lineFeed, amount))) {
                return amount;
            } else {
                count += amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Err(const char* out, ssize_t length = -1) {
        ssize_t count = Out(StdErr(), out, length);
        return count;
    }
    virtual ssize_t ErrFlush() {
        ssize_t count = OutFlush(StdErr());
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t InFormatted(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        if ((format)) {
            count = InFormattedV(format, va);
        }
        va_end(va);
        return count;
    }
    virtual ssize_t InFormattedV(const char* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t In(char* in, size_t size) {
        ssize_t count = In(StdIn(), in, size);
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Out(FILE* f, const char* out, ssize_t length = -1) {
        ssize_t count = 0;
        if ((out) && (f)) {
            ssize_t written;
            if (0 <= (length)) {
                if (0 < (written = Write(out, sizeof(char), length, f)))
                    count += written;
            } else {
                for (; *out; ++out) {
                    if (0 < (written = Write(out, sizeof(char), 1, f)))
                        count += written;
                }
            }
        }
        return count;
    }
    virtual ssize_t OutFlush(FILE* f) {
        ssize_t count = 0;
        if ((f)) {
            fflush(f);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t In(FILE* f, char* in, size_t size) {
        ssize_t count = 0;
        if ((in) && (f)) {
            ssize_t read;
            if (0 < (size)) {
                if (0 < (read = Read(in, sizeof(char), size, f)))
                    count += read;
            }
        }
        return count;
    }
    virtual ssize_t InFill(FILE* f) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write
    (const void* buf, size_t size, size_t count, FILE* file) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t Read
    (void* buf, size_t size, size_t count, FILE* file) {
        ssize_t amount = 0;
        return amount;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void SetStdInIsBinary(bool isTrue = true) {
    }
    virtual bool StdInIsBinary() const {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* StdOut() const {
        return 0;
    }
    virtual FILE* StdErr() const {
        return 0;
    }
    virtual FILE* StdIn() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* LineFeed(ssize_t& length) const {
        static const char lineFeed[2] = {'\n', 0};
        length = 1;
        return lineFeed;
    }
    virtual const char* LineFeed() const {
        ssize_t length = 0;
        return LineFeed(length);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace xos 

#endif // _XOS_BASE_MAINBASEIMPLEMENT_HPP 
        

