lacks_mime_list (NautilusFile *file)
{
    return !file->details->mime_list_is_up_to_date;
}
