static void show_warnings(void)
{
    if (g_warning_issued)
        gtk_widget_show(g_widget_warnings_area);
}
