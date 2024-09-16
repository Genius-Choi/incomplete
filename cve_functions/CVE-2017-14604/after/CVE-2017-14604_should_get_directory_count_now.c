should_get_directory_count_now (NautilusFile *file)
{
    return lacks_directory_count (file)
           && !file->details->loading_directory;
}
