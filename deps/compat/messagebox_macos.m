/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Warpper around various platform windowing systems modal message boxes.
 *
 * @copyright Maverick is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            3 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "messagebox.h"
#include <AppKit/AppKit.h>
#include <Availability.h>

int platform_messagebox(const char *message, const char *caption, int buttons, int type)
{
    @autoreleasepool {

    NSWindow *key_window = [[NSApplication sharedApplication] keyWindow];
    NSAlert *alert = [[NSAlert alloc] init];

    switch (type) {
        case MSGBOX_ERROR:
#ifdef __MAC_10_12
            [alert setAlertStyle:NSAlertStyleCritical];
#else
            [alert setAlertStyle:NSCriticalAlertStyle];
#endif
            break;
        case MSGBOX_WARNING:
#ifdef __MAC_10_12
            [alert setAlertStyle:NSAlertStyleWarning];
#else
            [alert setAlertStyle:NSWarningAlertStyle];
#endif
            break;
        case MSGBOX_INFO:
#ifdef __MAC_10_12
            [alert setAlertStyle:NSAlertStyleInformational];
#else
            [alert setAlertStyle:NSInformationalAlertStyle];
#endif
            break;
        default:
            break;
    }

    switch (buttons) {
        case MSGBTN_ABORTRETRYIGNORE:
            [alert addButtonWithTitle:@"Ignore"];
            [alert addButtonWithTitle:@"Retry"];
            [alert addButtonWithTitle:@"Abort"];
            break;
        case MSGBTN_OK:
            [alert addButtonWithTitle:@"OK"];
            break;
        case MSGBTN_OKCANCEL:
            [alert addButtonWithTitle:@"Cancel"];
            [alert addButtonWithTitle:@"OK"];
            break;
        case MSGBTN_RETRYCANCEL:
            [alert addButtonWithTitle:@"Cancel"];
            [alert addButtonWithTitle:@"Retry"];
            break;
        case MSGBTN_YESNO:
            [alert addButtonWithTitle:@"No"];
            [alert addButtonWithTitle:@"Yes"];
            break;
        case MSGBTN_YESNOCANCEL:
            [alert addButtonWithTitle:@"Cancel"];
            [alert addButtonWithTitle:@"No"];
            [alert addButtonWithTitle:@"Yes"];
            break;
        default:
            break;
    }

    NSString *msg_string = [NSString stringWithUTF8String:message];
    NSString *cap_string = [NSString stringWithUTF8String:caption];
    [alert setMessageText:cap_string];
    [alert setInformativeText:msg_string];
    NSInteger button = [alert runModal];
    [key_window makeKeyAndOrderFront:nil];

    switch(button) {
        case NSAlertFirstButtonReturn:
            switch (buttons) {
                case MSGBTN_ABORTRETRYIGNORE:
                    return MSGBOX_IGNORE;
                case MSGBTN_OK:
                    return MSGBOX_OK;
                case MSGBTN_OKCANCEL:
                case MSGBTN_RETRYCANCEL: /* fallthrough */
                case MSGBTN_YESNOCANCEL: /* fallthrough */
                    return MSGBOX_CANCEL;
                case MSGBTN_YESNO:
                    return MSGBOX_NO;
                default:
                    return MSGBOX_UNKNOWN;
            }
        case NSAlertSecondButtonReturn:
            switch (buttons) {
                case MSGBTN_ABORTRETRYIGNORE:
                    return MSGBOX_RETRY;
                case MSGBTN_OKCANCEL:
                    return MSGBOX_OK;
                case MSGBTN_RETRYCANCEL:
                    return MSGBOX_RETRY;
                case MSGBTN_YESNO:
                    return MSGBOX_YES;
                case MSGBTN_YESNOCANCEL:
                    return MSGBOX_NO;
                default:
                    return MSGBOX_UNKNOWN;
            }
        case NSAlertThirdButtonReturn:
            switch (buttons) {
                case MSGBTN_ABORTRETRYIGNORE:
                    return MSGBOX_ABORT;
                case MSGBTN_YESNOCANCEL:
                    return MSGBOX_YES;
                default:
                    return MSGBOX_UNKNOWN;
            }
        default:
            return MSGBOX_UNKNOWN;
    }

    } /* @autoreleasepool */
}