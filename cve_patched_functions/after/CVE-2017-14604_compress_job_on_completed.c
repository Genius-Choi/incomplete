compress_job_on_completed (AutoarCompressor *compressor,
                           gpointer          user_data)
{
    CompressJob *compress_job = user_data;
    g_autoptr (GFile) destination_directory = NULL;
    char *status;

    if (compress_job->total_files == 1)
    {
        status = f (_("Compressed “%B” into “%B”"),
                    G_FILE (compress_job->source_files->data),
                    compress_job->output_file);
    }
    else
    {
        status = f (ngettext ("Compressed %'d file into “%B”",
                              "Compressed %'d files into “%B”",
                              compress_job->total_files),
                    compress_job->total_files,
                    compress_job->output_file);
    }

    nautilus_progress_info_take_status (compress_job->common.progress,
                                        status);

    nautilus_file_changes_queue_file_added (compress_job->output_file);

    destination_directory = g_file_get_parent (compress_job->output_file);
    nautilus_progress_info_set_destination (compress_job->common.progress,
                                            destination_directory);
}
