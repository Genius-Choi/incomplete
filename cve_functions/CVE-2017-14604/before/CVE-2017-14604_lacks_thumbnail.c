lacks_thumbnail (NautilusFile *file)
{
    return nautilus_file_should_show_thumbnail (file) &&
           file->details->thumbnail_path != NULL &&
           !file->details->thumbnail_is_up_to_date;
}
