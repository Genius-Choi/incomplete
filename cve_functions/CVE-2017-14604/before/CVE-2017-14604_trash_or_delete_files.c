trash_or_delete_files (GtkWindow   *parent_window,
                       const GList *files,
                       gboolean     delete_if_all_already_in_trash)
{
    GList *locations;
    const GList *node;

    locations = NULL;
    for (node = files; node != NULL; node = node->next)
    {
        locations = g_list_prepend (locations,
                                    nautilus_file_get_location ((NautilusFile *) node->data));
    }

    locations = g_list_reverse (locations);

    nautilus_file_operations_trash_or_delete (locations,
                                              parent_window,
                                              NULL, NULL);
    g_list_free_full (locations, g_object_unref);
}
