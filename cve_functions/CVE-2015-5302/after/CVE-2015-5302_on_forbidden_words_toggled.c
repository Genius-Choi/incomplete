static void on_forbidden_words_toggled(GtkToggleButton *btn, gpointer user_data)
{
    g_search_text = NULL;
    log_notice("nothing to search for, highlighting forbidden words instead");
    highlight_forbidden();
}
