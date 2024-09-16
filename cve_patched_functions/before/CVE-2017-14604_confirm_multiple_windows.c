confirm_multiple_windows (GtkWindow *parent_window,
                          int        count,
                          gboolean   use_tabs)
{
    GtkDialog *dialog;
    char *prompt;
    char *detail;
    int response;

    if (count <= SILENT_WINDOW_OPEN_LIMIT)
    {
        return TRUE;
    }

    prompt = _("Are you sure you want to open all files?");
    if (use_tabs)
    {
        detail = g_strdup_printf (ngettext ("This will open %d separate tab.",
                                            "This will open %d separate tabs.", count), count);
    }
    else
    {
        detail = g_strdup_printf (ngettext ("This will open %d separate window.",
                                            "This will open %d separate windows.", count), count);
    }
    dialog = eel_show_yes_no_dialog (prompt, detail,
                                     _("_OK"), _("_Cancel"),
                                     parent_window);
    g_free (detail);

    response = gtk_dialog_run (dialog);
    gtk_widget_destroy (GTK_WIDGET (dialog));

    return response == GTK_RESPONSE_YES;
}
