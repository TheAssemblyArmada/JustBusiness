/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Warpper around various platform windowing systems modal message boxes.
 *
 * @copyright JustBusiness is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            3 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "messagebox.h"
#include <malloc.h>
#include <windows.h>

static wchar_t *to_utf16(const char *str)
{
    int len;
    wchar_t *ret;

    if (str == NULL) {
        return NULL;
    }

    len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

    if (len == 0) {
        return NULL;
    }

    ret = malloc(len * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, ret, len);

    return ret;
}

int platform_messagebox(const char *message, const char *caption, int buttons, int type)
{
    wchar_t *utf16_msg = to_utf16(message);
    wchar_t *utf16_cap = to_utf16(caption);
    UINT mbtype = MB_APPLMODAL | MB_SETFOREGROUND | MB_TASKMODAL;

    switch (buttons) {
        case MSGBTN_ABORTRETRYIGNORE:
            mbtype |= MB_ABORTRETRYIGNORE;
            break;
        case MSGBTN_OK:
            mbtype |= MB_OK;
            break;
        case MSGBTN_OKCANCEL:
            mbtype |= MB_OKCANCEL;
            break;
        case MSGBTN_RETRYCANCEL:
            mbtype |= MB_RETRYCANCEL;
            break;
        case MSGBTN_YESNO:
            mbtype |= MB_YESNO;
            break;
        case MSGBTN_YESNOCANCEL:
            mbtype |= MB_YESNOCANCEL;
            break;
        default:
            break;
    }

    switch (type) {
        case MSGBOX_ERROR:
            mbtype |= MB_ICONERROR;
            break;
        case MSGBOX_WARNING:
            mbtype |= MB_ICONWARNING;
            break;
        case MSGBOX_INFO:
            mbtype |= MB_ICONINFORMATION;
            break;
        case MSGBOX_QUESTION:
            mbtype |= MB_ICONQUESTION;
            break;
        default:
            break;
    }

    int result = MessageBoxW(GetActiveWindow(), utf16_msg, utf16_cap, mbtype);
    free(utf16_msg);
    free(utf16_cap);

    switch (result) {
        case IDYES:
            return MSGBOX_YES;
        case IDNO:
            return MSGBOX_NO;
        case IDOK:
            return MSGBOX_OK;
        case IDCANCEL:
            return MSGBOX_CANCEL;
        case IDCONTINUE:
            return MSGBOX_CONTINUE;
        case IDIGNORE:
            return MSGBOX_IGNORE;
        case IDRETRY:
            return MSGBOX_RETRY;
        case IDABORT:
            return MSGBOX_ABORT;
        default:
            return MSGBOX_UNKNOWN;
    }
}
