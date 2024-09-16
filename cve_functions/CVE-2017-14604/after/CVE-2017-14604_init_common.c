init_common (gsize      job_size,
             GtkWindow *parent_window)
{
    CommonJob *common;
    GdkScreen *screen;

    common = g_malloc0 (job_size);

    if (parent_window)
    {
        common->parent_window = parent_window;
        g_object_add_weak_pointer (G_OBJECT (common->parent_window),
                                   (gpointer *) &common->parent_window);
    }
    common->progress = nautilus_progress_info_new ();
    common->cancellable = nautilus_progress_info_get_cancellable (common->progress);
    common->time = g_timer_new ();
    common->inhibit_cookie = 0;
    common->screen_num = 0;
    if (parent_window)
    {
        screen = gtk_widget_get_screen (GTK_WIDGET (parent_window));
        common->screen_num = gdk_screen_get_number (screen);
    }

    return common;
}
