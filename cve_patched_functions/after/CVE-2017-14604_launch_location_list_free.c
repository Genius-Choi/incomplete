launch_location_list_free (GList *list)
{
    g_list_foreach (list, (GFunc) launch_location_free, NULL);
    g_list_free (list);
}
