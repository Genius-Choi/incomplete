get_file_list_for_launch_locations (GList *locations)
{
    GList *files, *l;
    LaunchLocation *location;

    files = NULL;
    for (l = locations; l != NULL; l = l->next)
    {
        location = l->data;

        files = g_list_prepend (files,
                                nautilus_file_ref (location->file));
    }
    return g_list_reverse (files);
}
