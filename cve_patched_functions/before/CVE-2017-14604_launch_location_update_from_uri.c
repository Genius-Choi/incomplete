launch_location_update_from_uri (LaunchLocation *location,
                                 const char     *uri)
{
    nautilus_file_unref (location->file);
    g_free (location->uri);
    location->file = nautilus_file_get_by_uri (uri);
    location->uri = g_strdup (uri);
}
