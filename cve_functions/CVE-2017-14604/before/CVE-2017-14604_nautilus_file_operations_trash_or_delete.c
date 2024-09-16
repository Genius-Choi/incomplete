nautilus_file_operations_trash_or_delete (GList                  *files,
                                          GtkWindow              *parent_window,
                                          NautilusDeleteCallback  done_callback,
                                          gpointer                done_callback_data)
{
    trash_or_delete_internal (files, parent_window,
                              TRUE,
                              done_callback, done_callback_data);
}
