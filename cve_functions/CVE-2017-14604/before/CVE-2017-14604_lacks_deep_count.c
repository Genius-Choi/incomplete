lacks_deep_count (NautilusFile *file)
{
    return file->details->deep_counts_status != NAUTILUS_REQUEST_DONE;
}
