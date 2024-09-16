lacks_extension_info (NautilusFile *file)
{
    return file->details->pending_info_providers != NULL;
}
