should_get_mime_list (NautilusFile *file)
{
    return lacks_mime_list (file)
           && !file->details->loading_directory;
}
