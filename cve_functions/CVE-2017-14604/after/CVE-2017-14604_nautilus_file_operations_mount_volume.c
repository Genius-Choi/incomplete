nautilus_file_operations_mount_volume (GtkWindow *parent_window,
                                       GVolume   *volume)
{
    nautilus_file_operations_mount_volume_full (parent_window, volume,
                                                NULL, NULL);
}
