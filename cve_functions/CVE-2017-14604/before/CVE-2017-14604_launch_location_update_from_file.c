launch_location_update_from_file (LaunchLocation *location,
                                  NautilusFile   *file)
{
    nautilus_file_unref (location->file);
    g_free (location->uri);
    location->file = nautilus_file_ref (file);
    location->uri = nautilus_file_get_uri (file);
}
