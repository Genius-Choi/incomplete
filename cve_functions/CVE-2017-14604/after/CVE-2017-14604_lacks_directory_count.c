lacks_directory_count (NautilusFile *file)
{
    return !file->details->directory_count_is_up_to_date
           && nautilus_file_should_show_directory_item_count (file);
}
