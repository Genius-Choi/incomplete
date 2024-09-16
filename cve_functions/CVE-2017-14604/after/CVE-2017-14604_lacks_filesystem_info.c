lacks_filesystem_info (NautilusFile *file)
{
    return !file->details->filesystem_info_is_up_to_date;
}
