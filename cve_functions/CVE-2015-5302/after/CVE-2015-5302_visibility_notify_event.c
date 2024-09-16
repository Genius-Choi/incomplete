static gboolean visibility_notify_event(GtkWidget *text_view, GdkEventVisibility *event)
{
    gint wx, wy, bx, by;

    GdkWindow *win = gtk_text_view_get_window(GTK_TEXT_VIEW(text_view), GTK_TEXT_WINDOW_TEXT);
    GdkDeviceManager *device_manager = gdk_display_get_device_manager(gdk_window_get_display (win));
    GdkDevice *pointer = gdk_device_manager_get_client_pointer(device_manager);
    gdk_window_get_device_position(gtk_widget_get_window(text_view), pointer, &wx, &wy, NULL);

    gtk_text_view_window_to_buffer_coords(GTK_TEXT_VIEW(text_view),
                                          GTK_TEXT_WINDOW_WIDGET,
                                          wx, wy, &bx, &by);

    set_cursor_if_appropriate(GTK_TEXT_VIEW (text_view), bx, by);

    return FALSE;
}
