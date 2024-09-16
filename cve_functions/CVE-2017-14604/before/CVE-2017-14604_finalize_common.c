finalize_common (CommonJob *common)
{
    nautilus_progress_info_finish (common->progress);

    if (common->inhibit_cookie != 0)
    {
        gtk_application_uninhibit (GTK_APPLICATION (g_application_get_default ()),
                                   common->inhibit_cookie);
    }

    common->inhibit_cookie = 0;
    g_timer_destroy (common->time);

    if (common->parent_window)
    {
        g_object_remove_weak_pointer (G_OBJECT (common->parent_window),
                                      (gpointer *) &common->parent_window);
    }

    if (common->skip_files)
    {
        g_hash_table_destroy (common->skip_files);
    }
    if (common->skip_readdir_error)
    {
        g_hash_table_destroy (common->skip_readdir_error);
    }

    if (common->undo_info != NULL)
    {
        nautilus_file_undo_manager_set_action (common->undo_info);
        g_object_unref (common->undo_info);
    }

    g_object_unref (common->progress);
    g_object_unref (common->cancellable);
    g_free (common);
}
