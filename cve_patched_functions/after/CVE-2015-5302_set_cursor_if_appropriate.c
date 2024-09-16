static void set_cursor_if_appropriate(GtkTextView *text_view,
                                      gint x,
                                      gint y)
{
    GSList *tags = NULL, *tagp = NULL;
    GtkTextIter iter;
    gboolean hovering = FALSE;

    gtk_text_view_get_iter_at_location(text_view, &iter, x, y);

    tags = gtk_text_iter_get_tags(&iter);
    for (tagp = tags; tagp != NULL; tagp = tagp->next)
    {
        GtkTextTag *tag = tagp->data;
        gpointer url = g_object_get_data(G_OBJECT (tag), "url");

        if (url != 0)
        {
            hovering = TRUE;
            break;
        }
    }

    if (hovering != hovering_over_link)
    {
        hovering_over_link = hovering;

        if (hovering_over_link)
            gdk_window_set_cursor(gtk_text_view_get_window(text_view, GTK_TEXT_WINDOW_TEXT), hand_cursor);
        else
            gdk_window_set_cursor(gtk_text_view_get_window(text_view, GTK_TEXT_WINDOW_TEXT), regular_cursor);
    }

    if (tags)
        g_slist_free (tags);
}
