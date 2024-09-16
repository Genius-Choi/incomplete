delete_cb (GtkDialog *dialog)
{
    gtk_dialog_response (dialog, GTK_RESPONSE_DELETE_EVENT);
    return TRUE;
}
