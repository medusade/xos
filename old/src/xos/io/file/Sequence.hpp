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
///   File: Sequence.hpp
///
/// Author: $author$
///   Date: 4/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FILE_SEQUENCE_HPP
#define _XOS_IO_FILE_SEQUENCE_HPP

#include "xos/io/Sequence.hpp"
#include "xos/base/Logged.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace io {
namespace file {

typedef LoggedT<AttacherT<FILE*, int, 0, Locker> > SequenceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: SequenceT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = SequenceImplement>

class _EXPORT_CLASS SequenceT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Seek(ssize_t length, Whence whence = FromBegin) {
        FILE* file;
        if ((file = this->AttachedTo())) {
            int seekFrom = (whence != FromBegin)?((whence != FromEnd)?(SEEK_CUR):(SEEK_END)):(SEEK_SET);
            int err;
            if ((err = fseek(file, length, seekFrom))) {
                if ((this->Logging()))
                    XOS_LOG_ERROR("failed " << errno << " on fseek()");
            } else {
                if (0 > (length = ftell(file))) {
                    if ((this->Logging()))
                        XOS_LOG_ERROR("failed " << length << " on ftell()");
                } else {
                    return length;
                }
            }
        }
        return -1; }
    virtual ssize_t Tell() const {
        FILE* file;
        if ((file = this->AttachedTo())) {
            ssize_t length;
            if (0 > (length = ftell(file))) {
                if ((this->Logging()))
                    XOS_LOG_ERROR("failed " << length << " on ftell()");
            } else {
                return length;
            }
        }
        return -1; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef SequenceT<> Sequence;

} // namespace file
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_FILE_SEQUENCE_HPP 
