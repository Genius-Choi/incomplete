nautilus_file_operations_unmount_mount (GtkWindow *parent_window,
                                        GMount    *mount,
                                        gboolean   eject,
                                        gboolean   check_trash)
{
    nautilus_file_operations_unmount_mount_full (parent_window, mount, NULL, eject,
                                                 check_trash, NULL, NULL);
}
