launch_locations_from_file_list (GList *list)
{
    GList *new;

    new = NULL;
    while (list)
    {
        new = g_list_prepend (new,
                              launch_location_from_file (list->data));
        list = list->next;
    }
    new = g_list_reverse (new);
    return new;
}
