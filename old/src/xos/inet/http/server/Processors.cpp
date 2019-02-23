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
///   File: Processors.cpp
///
/// Author: $author$
///   Date: 4/13/2014
///////////////////////////////////////////////////////////////////////
#include "xos/inet/http/server/Processors.hpp"

namespace xos {
namespace http {
namespace server {

typedef std::list<Processors::Processor*> ProcessorsList;
static ProcessorsList& processors() {
    static ProcessorsList processors;
    return processors;
}
///////////////////////////////////////////////////////////////////////
///  Class: Processors::Processor
///////////////////////////////////////////////////////////////////////
bool Processors::Processor::Add() {
    ProcessorsList& p = processors();
    p.push_back(this);
    return true;
}
bool Processors::Processor::Remove() {
    ProcessorsList& p = processors();
    ProcessorsList::iterator b = p.begin();
    ProcessorsList::iterator e = p.end();
    for (ProcessorsList::iterator i = b; i != e; ++i) {
        if ((*i) == this) {
            p.erase(i, i);
            break;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////
///  Class: Processors
///////////////////////////////////////////////////////////////////////
bool Processors::Process(Response& response, const Request& request) {
    bool processed = false;
    ProcessorsList& p = processors();
    ProcessorsList::iterator b = p.begin();
    ProcessorsList::iterator e = p.end();
    for (ProcessorsList::iterator i = b; i != e; ++i) {
        if ((processed = (*i)->Process(response, request))) {
            break;
        }
    }
    return processed;
}

} // namespace server 
} // namespace http 
} // namespace xos 
