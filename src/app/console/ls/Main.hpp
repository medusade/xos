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
///   Date: 10/30/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_CONSOLE_LS_MAIN_HPP
#define _XOS_APP_CONSOLE_LS_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/fs/os/Directory.hpp"
#include "xos/fs/os/Entry.hpp"
#include "xos/fs/Path.hpp"

namespace xos {
namespace app {
namespace console {
namespace ls {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;

class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    Main() {
    }
    virtual ~Main() {
    }

    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        fs::Path p;
        fs::os::Entry e;
        fs::os::Directory d;
        const char* a;

        if ((optind < (argc))) {
            if ((a = (argv[optind]))) {
                if ((p.Separate(a))) {
                    if ((e.Exists(a))) {
                        if ((e.GetType()) == fs::Entry::Directory) {
                            if ((d.Open(a))) {
                                for (fs::Entry* e = d.GetFirst(); e; e = d.GetNext()) {
                                    OnFileEntry(p, *e);
                                }
                                d.Close();
                            }
                        } else {
                            OnFileEntry(p, e);
                        }
                    } else {
                        ErrFormatted("%s: \"%s\" not found\n", argv[0], a);
                    }
                } else {
                     ErrFormatted("%s: \"%s\" is invalid path\n", argv[0], a);
                }
            }
        } else {
            Usage(argc, argv, env);
        }
        return err;
    }
    void OnFileEntry(const fs::Path& p, const fs::Entry& e) {
        fs::Entry::Time t = e.GetTimeModified();
        String pn(p.GetFileDirectory().Chars());
        fs::PathDirectoryAppender da(pn, e.GetName().Chars());
        OutFormatted
        ("%2.2d/%2.2d/%d %2.2d:%2.2d:%2.2d %s\n", 
         (int)(t.GetMonth()), (int)(t.GetDay()), (int)(t.GetYear()), 
         (int)(t.GetHour()), (int)(t.GetMinute()), (int)(t.GetSecond()), pn.Chars());
    }
};

} // namespace ls 
} // namespace console 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_CONSOLE_LS_MAIN_HPP 
