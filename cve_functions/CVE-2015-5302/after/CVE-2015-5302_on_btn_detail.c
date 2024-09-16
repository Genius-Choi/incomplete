static void on_btn_detail(GtkButton *button)
{
    GtkWidget *pdd = problem_details_dialog_new(g_cd, g_wnd_assistant);
    gtk_dialog_run(GTK_DIALOG(pdd));
}
