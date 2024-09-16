static void check_event_config(const char *event_name)
{
    GHashTable *errors = validate_event(event_name);
    if (errors != NULL)
    {
        g_hash_table_unref(errors);
        show_event_config_dialog(event_name, GTK_WINDOW(g_top_most_window));
    }
}
