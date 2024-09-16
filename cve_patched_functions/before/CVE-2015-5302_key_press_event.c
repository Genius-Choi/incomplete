static gboolean key_press_event(GtkWidget *text_view, GdkEventKey *event)
{
    GtkTextIter iter;
    GtkTextBuffer *buffer;

    switch (event->keyval)
    {
        case GDK_KEY_Return:
        case GDK_KEY_KP_Enter:
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (text_view));
            gtk_text_buffer_get_iter_at_mark(buffer, &iter,
                    gtk_text_buffer_get_insert(buffer));
            open_browse_if_link(text_view, &iter);
            break;

        default:
            break;
    }

    return FALSE;
}
