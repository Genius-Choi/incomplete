empty_trash_for_unmount_done (gboolean success,
                              gpointer user_data)
{
    UnmountData *data = user_data;
    do_unmount (data);
}
