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
///   File: iCocoa.mm
///
/// Author: $author$
///   Date: 2/5/2014
///////////////////////////////////////////////////////////////////////
#include "xos/gui/cocoa/iCocoa.hh"
#include "xos/gui/cocoa/os/iCocoa.mm"

///////////////////////////////////////////////////////////////////////
/// Implentation: iLabel
///////////////////////////////////////////////////////////////////////
@implementation iLabel
    - (id)initWithFrame:(iRect)frame text:(const std::string&)text {
        const char* chars = 0;
        iString* string = 0;
        self = [super initWithFrame:frame];
        [self setBezeled:NO];
        [self setDrawsBackground:NO];
        [self setEditable:NO];
        [self setSelectable:NO];
        if ((chars = text.c_str())) {
            if ((string = [iString stringWithUTF8String:chars])) {
                [self setStringValue:string];
            }
        }
        return self;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iEdit
///////////////////////////////////////////////////////////////////////
@implementation iEdit
    - (id)initWithFrame:(iRect)frame {
        if (([super initWithFrame:frame])) {
            iCell* cell;
            if ((cell = [self cell])) {
                [cell setUsesSingleLineMode:YES];
                [cell setWraps:NO];
                [cell setScrollable:YES];
            }
        }
        return self;
    }
    - (void)setText:(const std::string&)text {
        const char* chars;
        if ((chars = text.c_str())) {
            iString* string;
            if ((string = [iString stringWithUTF8String:chars])) {
                [self setStringValue:string];
            }
        }
    }
    - (void)getText:(std::string&)text {
        iString* string;
        if ((string = [self stringValue])) {
            const char* chars;
            if ((chars = [string UTF8String])) {
                text.assign(chars);
            }
        }
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iText
///////////////////////////////////////////////////////////////////////
@implementation iText
    - (id)initWithFrame:(iRect)frame {
        self = [super initWithFrame:frame];
        [self setEditable:NO];
        [self setSelectable:YES];
        return self;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iButton
///////////////////////////////////////////////////////////////////////
@implementation iButton
- (id)initWithFrame:(iRect)frame
               text:(const std::string&)text
              target:(iObject*)target
              action:(SEL)action {
        iString* string = 0;
        const char* chars;
        if (([super initWithFrame:frame])) {
            [self setTarget:target];
            [self setAction:action];
            if ((chars = text.c_str())) {
                if ((string = [NSString stringWithUTF8String:chars])) {
                    [self setTitle:string];
                }
            }
        }
        return self;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iCheck
///////////////////////////////////////////////////////////////////////
@implementation iCheck
- (id)initWithFrame:(iRect)frame
               text:(const std::string&)text
              target:(iObject*)target
              action:(SEL)action {
        if (([super initWithFrame:frame text:text target:target action:action])) {
            [self setButtonType:iSwitchButton];
            [self setState:iOffState];
        }
        return self;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iRadio
///////////////////////////////////////////////////////////////////////
@implementation iRadio
- (id)initWithFrame:(iRect)frame
               text:(const std::string&)text
              target:(iObject*)target
              action:(SEL)action {
        if (([super initWithFrame:frame text:text target:target action:action])) {
            [self setButtonType:iRadioButton];
            [self setState:iOffState];
        }
        return self;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iPullDown
///////////////////////////////////////////////////////////////////////
@implementation iPullDown
- (id)initWithFrame:(iRect)frame
               text:(const std::string&)text
              target:(iObject*)target
              action:(SEL)action {
        iString* string = 0;
        const char* chars;
        if (([super initWithFrame:frame])) {
            [self setPullsDown:YES];
            [self setTarget:target];
            [self setAction:action];
            if ((chars = text.c_str())) {
                if ((string = [NSString stringWithUTF8String:chars])) {
                }
            }
        }
        return self;
}
- (void)addItemWithText:(const std::string&)text {
    iString* string = 0;
    const char* chars;
    if ((chars = text.c_str())) {
        if ((string = [NSString stringWithUTF8String:chars])) {
            [self addItemWithTitle:string];
        }
    }
}
- (void)getSelectedItemText:(std::string&)text {
    iMenuItem* menuItem;
    if ((menuItem = [self selectedItem])) {
        iString* string;
        if ((string = [menuItem title])) {
            const char* chars;
            if ((chars = [string UTF8String])) {
                text.assign(chars);
            }
        }
    }
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iProgress
///////////////////////////////////////////////////////////////////////
@implementation iProgress
    - (id)initWithFrame:(iRect)frame {
        if (([super initWithFrame:frame])) {
            [self setMinValue:0];
            [self setMaxValue:100];
            [self setDoubleValue:50];
            [self setStyle:iProgressIndicatorBarStyle];
            [self setIndeterminate:NO];
            [self setHidden:YES];
        }
        return self;
    }
    - (void)setValue:(size_t)value {
        [self setDoubleValue:value];
    }
    - (void)show {
        [self setHidden:NO];
        [self startAnimation:self];
    }
    - (void)hide {
        [self stopAnimation:self];
        [self setHidden:YES];
    }
@end
