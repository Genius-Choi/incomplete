static void show_next_step_button()
{
    gtk_box_set_child_packing(g_box_buttons, g_btn_close, false, false, 5, GTK_PACK_START);

    gtk_widget_show(g_btn_next);
}
