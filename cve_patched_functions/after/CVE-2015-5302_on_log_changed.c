static void on_log_changed(GtkTextBuffer *buffer, gpointer user_data)
{
    gtk_widget_show(GTK_WIDGET(g_exp_report_log));
}
