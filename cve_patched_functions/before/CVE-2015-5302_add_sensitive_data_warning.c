static void add_sensitive_data_warning(void)
{
    GtkBuilder *builder = make_builder();

    GtkWidget *sens_data_warn = GTK_WIDGET(gtk_builder_get_object(builder, SENSITIVE_DATA_WARN));
    GtkButton *sens_ticket_cb = GTK_BUTTON(gtk_builder_get_object(builder, PRIVATE_TICKET_CB));

    g_signal_connect(sens_ticket_cb, "toggled", G_CALLBACK(on_sensitive_ticket_clicked_cb), NULL);
    add_widget_to_warning_area(GTK_WIDGET(sens_data_warn));

    g_object_unref(builder);
}
