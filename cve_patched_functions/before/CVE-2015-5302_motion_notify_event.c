static gboolean motion_notify_event(GtkWidget *text_view, GdkEventMotion *event)
{
    gint x, y;

    gtk_text_view_window_to_buffer_coords(GTK_TEXT_VIEW(text_view),
                                          GTK_TEXT_WINDOW_WIDGET,
                                          event->x, event->y, &x, &y);

    set_cursor_if_appropriate(GTK_TEXT_VIEW(text_view), x, y);
    return FALSE;
}
