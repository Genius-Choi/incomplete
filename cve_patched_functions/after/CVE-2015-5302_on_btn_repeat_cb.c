static void on_btn_repeat_cb(GtkButton *button)
{
    g_auto_event_list = g_list_prepend(g_auto_event_list, g_event_selected);
    g_event_selected = NULL;

    show_next_step_button();
    clear_warnings();

    const gint current_page_no = gtk_notebook_get_current_page(g_assistant);
    const int next_page_no = select_next_page_no(pages[PAGENO_SUMMARY].page_no, NULL);
    if (current_page_no == next_page_no)
        on_page_prepare(g_assistant, gtk_notebook_get_nth_page(g_assistant, next_page_no), NULL);
    else
        gtk_notebook_set_current_page(g_assistant, next_page_no);
}
