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
///   File: iCocoa.hh
///
/// Author: $author$
///   Date: 2/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_ICOCOA_HH
#define _XOS_GUI_COCOA_ICOCOA_HH

#include "xos/gui/cocoa/os/iCocoa.hh"
#include <string>

///////////////////////////////////////////////////////////////////////
/// Interface: iLabel
///////////////////////////////////////////////////////////////////////
@interface iLabel: iTextField {
    }
    - (id)initWithFrame:(iRect)frame text:(const std::string&)text;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iEdit
///////////////////////////////////////////////////////////////////////
@interface iEdit: iTextField {
    }
    - (id)initWithFrame:(iRect)frame;
    - (void)setText:(const std::string&)text;
    - (void)getText:(std::string&)text;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iText
///////////////////////////////////////////////////////////////////////
@interface iText: iEdit {
    }
    - (id)initWithFrame:(iRect)frame;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iButton
///////////////////////////////////////////////////////////////////////
@interface iButton: iPushButton {
    }
    - (id)initWithFrame:(iRect)frame
                   text:(const std::string&)text
                  target:(iObject*)target
                  action:(SEL)action;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iCheck
///////////////////////////////////////////////////////////////////////
@interface iCheck: iButton {
    }
    - (id)initWithFrame:(iRect)frame
                   text:(const std::string&)text
                  target:(iObject*)target
                  action:(SEL)action;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iRadio
///////////////////////////////////////////////////////////////////////
@interface iRadio: iButton {
    }
    - (id)initWithFrame:(iRect)frame
                   text:(const std::string&)text
                  target:(iObject*)target
                  action:(SEL)action;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iSpin
///////////////////////////////////////////////////////////////////////
@interface iSpin: iStepper {
    }
    - (id)initWithFrame:(iRect)frame
                   text:(const std::string&)text
                  target:(iObject*)target
                  action:(SEL)action;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iCombo
///////////////////////////////////////////////////////////////////////
@interface iCombo: iComboBox {
    }
    - (id)initWithFrame:(iRect)frame
                   text:(const std::string&)text
                  target:(iObject*)target
                  action:(SEL)action;
    - (void)addItemWithText:(const std::string&)text;
    - (void)getSelectedItemText:(std::string&)text;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iPullDown
///////////////////////////////////////////////////////////////////////
@interface iPullDown: iPopUpButton {
    }
    - (id)initWithFrame:(iRect)frame
                   text:(const std::string&)text
                  target:(iObject*)target
                  action:(SEL)action;
    - (void)addItemWithText:(const std::string&)text;
    - (void)getSelectedItemText:(std::string&)text;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iProgress
///////////////////////////////////////////////////////////////////////
@interface iProgress: iProgressIndicator {
    }
    - (id)initWithFrame:(iRect)frame;
    - (void)setValue:(size_t)value;
    - (void)show;
    - (void)hide;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iLevel
///////////////////////////////////////////////////////////////////////
@interface iLevel: iLevelIndicator {
    }
    - (id)initWithFrame:(iRect)frame;
    - (void)setValue:(size_t)value;
    - (void)show;
    - (void)hide;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iGroup
///////////////////////////////////////////////////////////////////////
@interface iGroup: iBox {
    }
    - (id)initWithFrame:(iRect)frame;
@end

#endif // _XOS_GUI_COCOA_ICOCOA_HH
