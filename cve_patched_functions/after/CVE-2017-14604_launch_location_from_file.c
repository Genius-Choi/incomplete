launch_location_from_file (NautilusFile *file)
{
    LaunchLocation *location;
    location = g_new (LaunchLocation, 1);
    location->file = nautilus_file_ref (file);
    location->uri = nautilus_file_get_uri (file);

    return location;
}
