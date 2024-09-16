show_unhandled_type_error (ActivateParametersInstall *parameters)
{
    GtkWidget *dialog;

    char *mime_type = nautilus_file_get_mime_type (parameters->file);
    char *error_message = get_application_no_mime_type_handler_message (parameters->file, parameters->uri);
    if (g_content_type_is_unknown (mime_type))
    {
        dialog = gtk_message_dialog_new (parameters->parent_window,
                                         GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_ERROR,
                                         0,
                                         "%s", error_message);
        gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
                                                  _("The file is of an unknown type"));
    }
    else
    {
        char *text;
        text = g_strdup_printf (_("There is no application installed for “%s” files"), g_content_type_get_description (mime_type));

        dialog = gtk_message_dialog_new (parameters->parent_window,
                                         GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_ERROR,
                                         0,
                                         "%s", error_message);
        gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
                                                  "%s", text);

        g_free (text);
    }

    gtk_dialog_add_button (GTK_DIALOG (dialog), _("_Select Application"), GTK_RESPONSE_ACCEPT);

    gtk_dialog_add_button (GTK_DIALOG (dialog), _("_OK"), GTK_RESPONSE_OK);

    gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_OK);

    g_object_set_data_full (G_OBJECT (dialog),
                            "mime-action:file",
                            nautilus_file_ref (parameters->file),
                            (GDestroyNotify) nautilus_file_unref);

    gtk_widget_show (GTK_WIDGET (dialog));

    g_signal_connect (dialog, "response",
                      G_CALLBACK (choose_program), parameters);

    g_free (error_message);
    g_free (mime_type);
}
