compress_job_on_error (AutoarCompressor *compressor,
                       GError           *error,
                       gpointer          user_data)
{
    CompressJob *compress_job = user_data;
    char *status;

    if (compress_job->total_files == 1)
    {
        status = f (_("Error compressing “%B” into “%B”"),
                    G_FILE (compress_job->source_files->data),
                    compress_job->output_file);
    }
    else
    {
        status = f (ngettext ("Error compressing %'d file into “%B”",
                              "Error compressing %'d files into “%B”",
                              compress_job->total_files),
                    compress_job->total_files,
                    compress_job->output_file);
    }

    nautilus_progress_info_take_status (compress_job->common.progress,
                                        status);

    run_error ((CommonJob *) compress_job,
               g_strdup (_("There was an error while compressing files.")),
               g_strdup (error->message),
               NULL,
               FALSE,
               CANCEL,
               NULL);

    abort_job ((CommonJob *) compress_job);
}
