launch_location_free (LaunchLocation *location)
{
    nautilus_file_unref (location->file);
    g_free (location->uri);
    g_free (location);
}
