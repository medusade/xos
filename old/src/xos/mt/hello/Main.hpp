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
///   Date: 4/16/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_HELLO_MAIN_HPP
#define _XOS_MT_HELLO_MAIN_HPP

#include "xos/mt/base/hello/Main.hpp"
#include "xos/mt/os/Process.hpp"
#include "xos/mt/os/Thread.hpp"

#include <deque>
#include <sstream>

namespace xos {
namespace mt {
namespace hello {

typedef xos::mt::base::hello::MainImplement MainImplement;
typedef xos::mt::base::hello::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    typedef mt::os::Process Process;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Thread {
    public:
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        class _EXPORT_CLASS Runner: public mt::Run {
        public:
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            Runner(int argc, char **argv, char **env, const String& name, size_t iterations = 1)
            : m_argc(argc), m_argv(argv), m_env(env),
              m_name(name), m_iterations(iterations) {}

            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            virtual void operator()() {
                const char* hello = "Hello";
                const char* who = (optind < m_argc)?(m_argv[optind]):(0);
                for (size_t i = 0; i < m_iterations; ++i) {
                    XOS_LOG_INFO(m_name << "[" << i << "]" << hello << ((who)?(" "):("")) << ((who)?(who):("")));
                    usleep(200000);
                }
            }
            const String& Name() const { return m_name; }

            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
        protected:
            int m_argc;
            char** m_argv;
            char** m_env;
            String m_name;
            size_t m_iterations;
        };

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Thread(int argc, char **argv, char **env, const String& name, size_t iterations = 1)
        : m_runner(argc, argv, env, name, iterations), m_thread(m_runner) {}
        virtual ~Thread() {}

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        bool Destroy() { return m_thread.Destroy(); }
        const String& Name() const { return m_runner.Name(); }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Runner m_runner;
        mt::os::Thread m_thread;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ProcessesRun(int argc, char **argv, char **env) {
        const char* exe = (0 < argc)?(argv[0]):("XosMtHello");
        char* arg0 = (0 < argc)?(argv[0]):(0);
        char* arg1 = (optind < argc)?(argv[optind]):(0);
        char* args[] = {arg0, arg1, 0};
        char** envs = env;
        int* fdup = 0;
        int** pdup = 0;
        bool isDetached = false;
        size_t n = m_processes;
        int err = 0;

        if ((exe) && (args)) {
            if (2 > (n)) {
                try {
                    Process p(exe, args, envs, fdup, pdup, isDetached);
                } catch(const Creator::Exception& e) {
                    const char* eName = (Creator::FailedToCreate!=e)?("FailedToDestroy"):("FailedToCreate");
                    XOS_LOG_ERROR("...caught Creator::" << eName);
                }
            } else {
                std::deque<Process*> q;
                Process* p;

                for (size_t i = 0; i < n; ++i) {
                    try {
                        XOS_LOG_DEBUG("new Process(\"" << exe << "\",...)...");
                        if ((p = new Process(exe, args, envs, fdup, pdup, isDetached))) {
                            XOS_LOG_DEBUG("...new Process(\"" << exe << "\",...)");
                            q.push_back(p);
                        }
                    } catch(const Creator::Exception& e) {
                        const char* eName = (Creator::FailedToCreate!=e)?("FailedToDestroy"):("FailedToCreate");
                        XOS_LOG_ERROR("...caught Creator::" << eName);
                        break;
                    }
                }

                for (std::deque<Process*>::iterator i = q.end(); i != q.begin(); --i) {
                    if ((p = *(i-1))) {
                        try {
                            pid_t pid = p->AttachedTo();
                            XOS_LOG_DEBUG("deleteing process " << pid << "...");
                            delete p;
                            XOS_LOG_DEBUG("...deleted process " << pid << "");
                        } catch(const Creator::Exception& e) {
                            const char* eName = (Creator::FailedToCreate!=e)?("FailedToDestroy"):("FailedToCreate");
                            XOS_LOG_ERROR("...caught Creator::" << eName);
                        }
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ThreadsRun(int argc, char **argv, char **env) {
        size_t n = m_threads;
        std::deque<Thread*> q;
        Thread* t;

        for (size_t i = 0; i < n; ++i) {
            String name("Thread[");
            name.Append((unsigned)i);
            name.Append("]");
            XOS_LOG_DEBUG("creating \"" << name << "\"...");
            if ((t = new Thread(argc, argv, env, name, n))) {
                XOS_LOG_DEBUG("...created \"" << name << "\"");
                q.push_back(t);
            }
        }

        Thread::Runner m_runner(argc, argv, env, "Main", n);
        m_runner();

        for (std::deque<Thread*>::iterator i = q.end(); i != q.begin(); --i) {
            if ((t = *(i-1))) {
                String name(t->Name());
                XOS_LOG_DEBUG("destroying \"" << name << "\"...");
                if ((t->Destroy())) {
                    XOS_LOG_DEBUG("...destroyed \"" << name << "\"");
                }
                XOS_LOG_DEBUG("deleteing \"" << name << "\"...");
                delete t;
                XOS_LOG_DEBUG("...deleted \"" << name << "\"");
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace hello 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_HELLO_MAIN_HPP 
