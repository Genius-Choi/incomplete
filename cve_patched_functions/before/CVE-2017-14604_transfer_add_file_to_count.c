transfer_add_file_to_count (GFile        *file,
                            CommonJob    *job,
                            TransferInfo *transfer_info)
{
    g_autoptr (GFileInfo) file_info = NULL;

    if (g_cancellable_is_cancelled (job->cancellable))
    {
        return;
    }

    file_info = g_file_query_info (file,
                                   G_FILE_ATTRIBUTE_STANDARD_SIZE,
                                   G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                   job->cancellable,
                                   NULL);

    transfer_info->num_files++;
    if (file_info != NULL)
    {
        transfer_info->num_bytes += g_file_info_get_size (file_info);
    }
}
