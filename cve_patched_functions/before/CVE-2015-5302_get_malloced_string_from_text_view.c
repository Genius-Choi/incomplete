static gchar *get_malloced_string_from_text_view(GtkTextView *tv)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(tv);
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    return gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
}
