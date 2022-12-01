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
#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>

int platform_messagebox(const char *message, const char *caption, int buttons, int type)
{
    assert(gtk_init_check(NULL, NULL));
    GtkMessageType msg_type = GTK_MESSAGE_QUESTION;

    switch (type) {
        case MSGBOX_ERROR:
            msg_type = GTK_MESSAGE_ERROR;
            break;
        case MSGBOX_WARNING:
            msg_type = GTK_MESSAGE_WARNING;
            break;
        case MSGBOX_INFO:
            msg_type = GTK_MESSAGE_INFO;
            break;
        case MSGBOX_QUESTION: /* fallthrough */
        default:
            break;
    }

    GtkWidget *dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, msg_type, GTK_BUTTONS_NONE, "%s", caption);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "%s", message);

    switch (buttons) {
        case MSGBTN_ABORTRETRYIGNORE:
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Abort", GTK_RESPONSE_OK);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Retry", GTK_RESPONSE_HELP);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Ignore", GTK_RESPONSE_CANCEL);
            break;
        case MSGBTN_OK:
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_OK", GTK_RESPONSE_OK);
            break;
        case MSGBTN_OKCANCEL:
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_OK", GTK_RESPONSE_OK);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Cancel", GTK_RESPONSE_CANCEL);
            break;
        case MSGBTN_RETRYCANCEL:
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Retry", GTK_RESPONSE_HELP);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Cancel", GTK_RESPONSE_CANCEL);
            break;
        case MSGBTN_YESNO:
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Yes", GTK_RESPONSE_OK);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_No", GTK_RESPONSE_HELP);
            break;
        case MSGBTN_YESNOCANCEL:
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Yes", GTK_RESPONSE_OK);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_No", GTK_RESPONSE_HELP);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "_Cancel", GTK_RESPONSE_CANCEL);
            break;
        default:
            break;
    }

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    while (gtk_events_pending()) {
        gtk_main_iteration();
    }

    switch (result) {
        case GTK_RESPONSE_OK:
            switch (buttons) {
                case MSGBTN_ABORTRETRYIGNORE:
                    return MSGBOX_ABORT;
                case MSGBTN_OK: /* fallthrough */
                case MSGBTN_OKCANCEL:
                    return MSGBOX_OK;
                case MSGBTN_YESNO: /* fallthrough */
                case MSGBTN_YESNOCANCEL:
                    return MSGBOX_YES;
                default:
                    return MSGBOX_UNKNOWN;
            }
        case GTK_RESPONSE_CANCEL:
            switch (buttons) {
                case MSGBTN_ABORTRETRYIGNORE:
                    return MSGBOX_IGNORE;
                case MSGBTN_OKCANCEL: /* fallthrough */
                case MSGBTN_RETRYCANCEL: /* fallthrough */
                case MSGBTN_YESNOCANCEL:
                    return MSGBOX_CANCEL;
                default:
                    return MSGBOX_UNKNOWN;
            }
        case GTK_RESPONSE_HELP:
            switch (buttons) {
                case MSGBTN_ABORTRETRYIGNORE: /* fallthrough */
                case MSGBTN_RETRYCANCEL:
                    return MSGBOX_RETRY;
                case MSGBTN_YESNO: /* fallthrough */
                case MSGBTN_YESNOCANCEL:
                    return MSGBOX_NO;
                default:
                    return MSGBOX_UNKNOWN;
            }
        default:
            return MSGBOX_UNKNOWN;
    }
}
