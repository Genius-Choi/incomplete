find_launch_location_for_file (GList        *list,
                               NautilusFile *file)
{
    LaunchLocation *location;
    GList *l;

    for (l = list; l != NULL; l = l->next)
    {
        location = l->data;

        if (location->file == file)
        {
            return location;
        }
    }
    return NULL;
}
