copy_file_progress_callback (goffset  current_num_bytes,
                             goffset  total_num_bytes,
                             gpointer user_data)
{
    ProgressData *pdata;
    goffset new_size;

    pdata = user_data;

    new_size = current_num_bytes - pdata->last_size;

    if (new_size > 0)
    {
        pdata->transfer_info->num_bytes += new_size;
        pdata->last_size = current_num_bytes;
        report_copy_progress (pdata->job,
                              pdata->source_info,
                              pdata->transfer_info);
    }
}
