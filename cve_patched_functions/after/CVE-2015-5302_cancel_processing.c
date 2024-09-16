static void cancel_processing(GtkLabel *status_label, const char *message, int terminate_flags)
{
    gtk_label_set_text(status_label, message ? message : _("Processing was canceled"));
    terminate_event_chain(terminate_flags);
}
