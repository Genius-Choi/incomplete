static void on_bt_approve_toggle(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_widget_set_sensitive(g_btn_next, gtk_toggle_button_get_active(g_tb_approve_bt));
}
