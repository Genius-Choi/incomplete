mime_db_changed_callback (GObject           *ignore,
                          NautilusDirectory *dir)
{
    NautilusFileAttributes attrs;

    g_assert (dir != NULL);
    g_assert (dir->details != NULL);

    attrs = NAUTILUS_FILE_ATTRIBUTE_INFO |
            NAUTILUS_FILE_ATTRIBUTE_LINK_INFO |
            NAUTILUS_FILE_ATTRIBUTE_DIRECTORY_ITEM_MIME_TYPES;

    nautilus_directory_force_reload_internal (dir, attrs);
}
