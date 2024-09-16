extract_job_on_error (AutoarExtractor *extractor,
                      GError          *error,
                      gpointer         user_data)
{
    ExtractJob *extract_job = user_data;
    GFile *source_file;
    gint response_id;

    source_file = autoar_extractor_get_source_file (extractor);

    if (IS_IO_ERROR (error, NOT_SUPPORTED))
    {
        handle_unsupported_compressed_file (extract_job->common.parent_window,
                                            source_file);

        return;
    }

    nautilus_progress_info_take_status (extract_job->common.progress,
                                        f (_("Error extracting “%B”"),
                                           source_file));

    response_id = run_warning ((CommonJob *) extract_job,
                               f (_("There was an error while extracting “%B”."),
                                  source_file),
                               g_strdup (error->message),
                               NULL,
                               FALSE,
                               CANCEL,
                               SKIP,
                               NULL);

    if (response_id == 0 || response_id == GTK_RESPONSE_DELETE_EVENT)
    {
        abort_job ((CommonJob *) extract_job);
    }
}
