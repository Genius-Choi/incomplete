count_file (GFileInfo  *info,
            CommonJob  *job,
            SourceInfo *source_info)
{
    source_info->num_files += 1;
    source_info->num_bytes += g_file_info_get_size (info);

    if (source_info->num_files_since_progress++ > 100)
    {
        report_preparing_count_progress (job, source_info);
        source_info->num_files_since_progress = 0;
    }
}
