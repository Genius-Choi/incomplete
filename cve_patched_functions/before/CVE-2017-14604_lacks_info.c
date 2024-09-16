lacks_info (NautilusFile *file)
{
    return !file->details->file_info_is_up_to_date
           && !file->details->is_gone;
}
