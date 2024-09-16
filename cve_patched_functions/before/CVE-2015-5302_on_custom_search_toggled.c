static void on_custom_search_toggled(GtkToggleButton *btn, gpointer user_data)
{
    const gboolean custom_search = gtk_toggle_button_get_active(btn);
    gtk_widget_set_sensitive(GTK_WIDGET(g_search_entry_bt), custom_search);

    if (custom_search)
        highlight_search(g_search_entry_bt);
}
