nautilus_file_operations_delete (GList                  *files,
                                 GtkWindow              *parent_window,
                                 NautilusDeleteCallback  done_callback,
                                 gpointer                done_callback_data)
{
    trash_or_delete_internal (files, parent_window,
                              FALSE,
                              done_callback, done_callback_data);
}
