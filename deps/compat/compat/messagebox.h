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
#ifndef COMPAT_MESSAGEBOX_H
#define COMPAT_MESSAGEBOX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MSGBTN_ABORTRETRYIGNORE,
    MSGBTN_OK,
    MSGBTN_OKCANCEL,
    MSGBTN_RETRYCANCEL,
    MSGBTN_YESNO,
    MSGBTN_YESNOCANCEL,
} MessageBoxButtons;

typedef enum
{
    MSGBOX_ERROR,
    MSGBOX_WARNING,
    MSGBOX_INFO,
    MSGBOX_QUESTION,
} MessageBoxType;

typedef enum
{
    MSGBOX_UNKNOWN = -1,
    MSGBOX_YES,
    MSGBOX_NO,
    MSGBOX_OK,
    MSGBOX_CANCEL,
    MSGBOX_CONTINUE,
    MSGBOX_IGNORE,
    MSGBOX_RETRY,
    MSGBOX_ABORT,
} MessageBoxResult;

/**
 * @brief Opens a modal message box.
 * @param message Message body for the message box.
 * @param caption Heading for the message box.
 * @param buttons Button layout from MessageBoxButtons.
 * @param type Type of message box from MessageBoxType.
 * @return A value from MessageBoxResult, MSGBOX_UNKNOWN if an error occurs.
 */
int platform_messagebox(const char *message, const char *caption, int buttons, int type);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* COMPAT_MESSAGEBOX_H */
